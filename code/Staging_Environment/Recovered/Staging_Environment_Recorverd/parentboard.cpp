#include "parentboard.h"
#include "pb_productbacklog_implementation.h"
#include "pb_sprint_implemenation.h"
#include "ui_parentboard.h"
#include "mainwindow.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QDebug>
#include <QTableView>
#include "pb_confluence_implemenation.h"
#include "pb_productbacklog_implementation.h"
#include "pb_team_implemenation.h"
#include "pb_taskboard_implemenation.h"
#include "pb_productbacklog_implementation_extension.h"
#include "teammember_projectswindow.h"
#include "pb_calendar_implemenation.h"
#include "customcalendarwidget.h"

// Temp - Scalability
#include "QtGui/qevent.h"

parentboard* parentboard::instance = nullptr;


parentboard::parentboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::parentboard)
{
    ui->setupUi(this);
    setWindowTitle("Scrummy 1.0");
    isTeamTableActive = false;
    DatabaseManager database;
    QSqlDatabase databaseInstance = database.getDatabase();

    centerOnScreen();

    QLabel logoScrummy;
    QPixmap logo("qrc:/LogoScrummy.png");
    logoScrummy.setPixmap(logo);

    ui->edit_sprint_button->setVisible(false);
    // Bottom border of buttons
    ui->taskboardButton->setCheckable(true);
    ui->backlogButton->setCheckable(true);
    ui->sprintsButton->setCheckable(true);
    ui->teamButton->setCheckable(true);
    ui->confluenceButton->setCheckable(true);
    ui->calendarButton->setCheckable(true);
    ui->taskboardButton->setChecked(true);

    taskModel = new QStandardItemModel(this);
    taskModel->setColumnCount(2);
    ui->teamTable->reset();
    ui->teamTable->setColumnCount(4);
    ui->teamTable->setHorizontalHeaderLabels({"First name","Last name", "Email", "Role"});

    //Call the query here bro



    //ui->user_stories->setColumnCount(3); // Add a new column for priority
    //ui->user_stories->setHorizontalHeaderLabels({"Userstory", "Description", "Priority"}); // Set column headers
    //ui->issues->setColumnCount(3); // Add a new column for priority
    //ui->issues->setHorizontalHeaderLabels({"Issue", "Description", "Priority"}); // Set column headers

    //  PB_ProductBacklog ---------------------------------- Calls
    //  PB_ProductBacklog ---------------------------------- Calls
    parentboard *obj = this; // Create an instance of parentboard
    pb_team_implemenation *teamPagePtr = new pb_team_implemenation(obj, databaseInstance);
    pb_productbacklog_implementation *pbProductBacklogObj = new pb_productbacklog_implementation(obj);
    pb_productbacklog_implementation_Extension *pbProductBacklog_ExtensionObj = new pb_productbacklog_implementation_Extension(obj);
    pb_sprint_implemenation *pbSprintObj = new pb_sprint_implemenation(obj);
    pbProductBacklogObj->RetrieveAndDisplayBacklog();
    pbProductBacklogObj->Hide_CreateSection();

    connect(ui->backlogButton, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::RetrieveAndDisplayBacklog);
    connect(ui->button_userstory, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::Show_CreateSection);
    connect(ui->buttton_issue, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::Show_CreateSection);
    connect(ui->button_userstory, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::Show_CreateSection_UserStory);
    connect(ui->buttton_issue, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::Show_CreateSection_Tasks);
    //CREATE USERSTORY AND TASKS
    connect(ui->Button_CreateTask, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::onButtonIssueClicked);
    connect(ui->Button_CreateUserStory, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::on_createUserStory_clicked);
    //connect(ui->CreateSprint_SprintTab, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::on_createUserStory_clicked);
    connect(ui->user_stories, &QTableWidget::itemChanged, pbProductBacklogObj, &pb_productbacklog_implementation::onTableItemChanged);
    connect(ui->user_stories, &QTableWidget::itemChanged, pbProductBacklogObj, &pb_productbacklog_implementation::onUserStoryTableItemChanged);
    //Lambda Function to delete the tasks in the tables
    connect(ui->delete_item, &QPushButton::clicked, [this, pbProductBacklogObj]() {
        if (!ui->user_stories) {
            qDebug() << "User stories table not found";
            return;
        }
        int selectedRow = -1;
        QList<QTableWidgetItem*> selectedItems = ui->user_stories->selectedItems();
        if (!selectedItems.isEmpty()) {
            selectedRow = selectedItems.first()->row();
        }
        if (selectedRow == -1) {
            qDebug() << "No row selected";
            return;
        }
        QTableWidgetItem* item = ui->user_stories->item(selectedRow, 0); // 0 is the column for taskID
        if (item) {
            pbProductBacklogObj->onRowClicked(item);
            pbProductBacklogObj->RetrieveAndDisplayBacklog();
        } else {
            qDebug() << "Item is null";
            // Optionally, handle this case
        }

    });
    connect(ui->delete_item_UserStory, &QPushButton::clicked, [this, pbProductBacklog_ExtensionObj, pbProductBacklogObj]() {
        qDebug() << "Delete button clicked"; // Debug message
        if (!ui->user_stories) {
            qDebug() << "User stories table not found";
            return;
        }
        int selectedRow = -1;
        QList<QTableWidgetItem*> selectedItems = ui->user_stories->selectedItems();
        qDebug() << "Number of selected items: " << selectedItems.count(); // Debug message
        if (!selectedItems.isEmpty()) {
            selectedRow = selectedItems.first()->row();
        }
        if (selectedRow == -1) {
            qDebug() << "No row selected";
            return;
        }
        QTableWidgetItem* item = ui->user_stories->item(selectedRow, 0); // 0 is the column for storyID
        if (item) {
            int storyID = item->data(Qt::UserRole).toInt(); // Assuming the storyID is stored in the UserRole
            pbProductBacklog_ExtensionObj->deleteTaskFromDatabase(storyID); // Call the deleteUserStory function
             pbProductBacklogObj->RetrieveAndDisplayBacklog();
        } else {
            qDebug() << "Item is null";
            // Optionally, handle this case
        }
    });

    //  pb_productbacklog Implementation Calls ---End

    //  PB_Sprint  ---------------------------------- Calls
    //  PB_Sprint  ---------------------------------- Calls

    pb_sprint_implemenation *pbSprintBObj = new pb_sprint_implemenation(obj); //Accessing the pb_sprint_implementation class
    connect(ui->sprintsButton,&QPushButton::clicked,pbSprintBObj,&pb_sprint_implemenation::OBJECTS_VISIBLE_BOXES);
    connect(ui->sprintsButton,&QPushButton::clicked,pbSprintBObj,&pb_sprint_implemenation::RetrieveAndDisplayTask);
    connect(ui->sprintinfo_save_button, &QPushButton::clicked, pbSprintBObj, &pb_sprint_implemenation::UpdateSprintDetails);

    connect(ui->sprint_create_button, &QPushButton::clicked, pbSprintBObj, &pb_sprint_implemenation::OBJECTS_VISIBLE_on_create_sprint_clicked); //TO JUST MAKE THE CORRECT OBJECTS VISIBLE
    connect(ui->edit_sprint_button, &QPushButton::clicked, pbSprintBObj, &pb_sprint_implemenation::on_editsprint_sprint_clicked);
    //Create Task
    connect(ui->CreateSprint_SprintTab, &QPushButton::clicked, pbSprintObj, &pb_sprint_implemenation::on_createtask_sprint_clicked);
    connect(ui->delete_button,&QPushButton::clicked,pbSprintBObj,&pb_sprint_implemenation::onDeleteButtonClicked);
    // Connect the delete button click signal to the onDeleteButtonClicked() slot
    // connect(ui->delete_button, SIGNAL(clicked()), this, SLOT(onDeleteButtonClicked()));

    //  PB_Confluence  ---------------------------------- Calls
    //  PB_Confluence  ---------------------------------- Calls

    PB_Confluence_Implemenation *pbConfluenceBObj = new PB_Confluence_Implemenation(obj); //Accessing the pb_sprint_implementation class
    connect(ui->confluenceButton,&QPushButton::clicked,pbConfluenceBObj,&PB_Confluence_Implemenation::HideCreationSection);
    connect(ui->ButtonGroup_Confluence,&QPushButton::clicked,pbConfluenceBObj,&PB_Confluence_Implemenation::ShowCreateWindow);
    connect(ui->ButtonPage_Confluence,&QPushButton::clicked,pbConfluenceBObj,&PB_Confluence_Implemenation::ShowCreateWindow_Page);

    connect(ui->Button_Create_Confluence,&QPushButton::clicked,pbConfluenceBObj,&PB_Confluence_Implemenation::CreateGroupFunction);
    connect(ui->Button_CreatePage_Confluence,&QPushButton::clicked,pbConfluenceBObj,&PB_Confluence_Implemenation::CreatePageFunction);

    PB_Confluence_Implemenation* myConfluenceImplementation = new PB_Confluence_Implemenation(this);
    connect(ui->userTaskTreeWidget_2, &QTreeWidget::itemClicked, myConfluenceImplementation, &PB_Confluence_Implemenation::onTreeItemClicked);

    //  PB_Team  ---------------------------------- Calls
    //  PB_Team  ---------------------------------- Calls

    //connect(ui->button_inviteUser, &QPushButton::clicked, teamPagePtr, &pb_team_implemenation::ShowUserProperties);
    connect(ui->CreateUser_Button, &QPushButton::clicked, teamPagePtr, &pb_team_implemenation::on_createuser_clicked);
    connect(ui->teamButton, &QPushButton::clicked, teamPagePtr, &pb_team_implemenation::UserRetrieval);
    teamPagePtr->ShowUserProperties();
    connect(ui->RemoveUser_Button, &QPushButton::clicked, [this, teamPagePtr]() {
        if (!ui->teamTable) {
            qDebug() << "Team table not found";
            return;
        }
        int selectedRow = -1;
        QList<QTableWidgetItem*> selectedItems = ui->teamTable->selectedItems();
        if (!selectedItems.isEmpty()) {
            selectedRow = selectedItems.first()->row();
        }
        if (selectedRow == -1) {
            qDebug() << "No row selected";
            ui->TeamError_display->setText("No row selected.");
            return;
        }
        QTableWidgetItem* item = ui->teamTable->item(selectedRow, 0); // 0 is the column for taskID
        if (item) {
            ui->TeamError_display->setText("");
            teamPagePtr->RemoveUser(item);
        } else {
            qDebug() << "Item is null";
            ui->TeamError_display->setText("Please select a row to delete.");
            // Optionally, handle this case
        }

    });

    //Old Way
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(goBackToMainWindow()));
    connect(ui->button_userstory, SIGNAL(clicked()), this, SLOT(test()));

    //  PB_TaskBoard ---------------------------------- Calls
    //  PB_TaskBoard ---------------------------------- Calls
    pb_taskboard_implemenation *pbTaskboardBObj = new pb_taskboard_implemenation(obj);
    connect(ui->taskboardButton,&QPushButton::clicked,pbTaskboardBObj,&pb_taskboard_implemenation::pb_taskboard_Retrieval);

    // Show Task or UserStory creation
    connect(ui->editTaskButtonT, &QPushButton::clicked, pbTaskboardBObj, &pb_taskboard_implemenation::showEditTaskboard);


    // Create Task or UserStory
    connect(ui->Button_CreateTaskT, &QPushButton::clicked, pbTaskboardBObj, &pb_taskboard_implemenation::editTaskTaskboard);




    //  PB_Calendar ---------------------------------- Calls
    //  PB_Calendar ---------------------------------- Calls
    connect(ui->calendarButton, SIGNAL(clicked()), this, SLOT(on_calendarButton_clicked()));
    pb_calendar_implementation *pbcalendarObj = new pb_calendar_implementation(this); // Corrected class name
    connect(ui->calendarButton, &QPushButton::clicked, pbcalendarObj, &pb_calendar_implementation::Calendar_HideEventCreation);
    connect(ui->Button_SaveCalendar, &QPushButton::clicked, pbcalendarObj, &pb_calendar_implementation::onSaveButtonClicked);


}

void parentboard::UserSpecificView(int value){

    if(value == 3){
        ui->sprintsButton->setVisible(false);
        ui->backlogButton->setVisible(false);
        ui->teamButton->setVisible(false);
    }else{
    }
}


void parentboard::displayBacklogOnMaximized() {
    auto taskboardobj = std::make_unique<pb_taskboard_implemenation>(this);
    taskboardobj->pb_taskboard_Retrieval();
}

/*
void parentboard::displayBacklogOnMaximized() {
    parentboard *obj = this; // Create an instance of parentboard
    pb_productbacklog_implementation *pbProductBacklogObj = new pb_productbacklog_implementation(obj);
    pbProductBacklogObj->RetrieveAndDisplayBacklog();
}
*/

//------------------------------------------------------------------------------------------------------------------------------------------------
parentboard::~parentboard()
{
    delete ui;
}

//------------------------------------------------------------------------------------------------------------------------------------------------
//Top Bar Button's Functions
//------------------------------------------------------------------------------------------------------------------------------------------------

void parentboard::on_taskboardButton_clicked()
{
    ui->taskboardButton->setChecked(true);
    ui->backlogButton->setChecked(false);
    ui->teamButton->setChecked(false);
    ui->sprintsButton->setChecked(false);
    ui->confluenceButton->setChecked(false);
    ui->calendarButton->setChecked(false);
    ui->stackedWidget->setCurrentIndex(0);
    const int numOfRowsToAdd = 3;
}
void parentboard::on_Issue_selected(){

}
void parentboard::on_backlogButton_clicked()
{
    ui->backlogButton->setChecked(true);
    ui->taskboardButton->setChecked(false);
    ui->teamButton->setChecked(false);
    ui->sprintsButton->setChecked(false);
    ui->confluenceButton->setChecked(false);
    ui->calendarButton->setChecked(false);
    ui->stackedWidget->setCurrentIndex(1);
    const int numOfRowsToAdd = 3;
}
void parentboard::on_teamButton_clicked()
{
    ui->teamButton->setChecked(true);
    ui->backlogButton->setChecked(false);
    ui->taskboardButton->setChecked(false);
    ui->sprintsButton->setChecked(false);
    ui->confluenceButton->setChecked(false);
    ui->calendarButton->setChecked(false);
    ui->stackedWidget->setCurrentIndex(2);
}
void parentboard::on_sprintsButton_clicked()
{
    ui->sprintsButton->setChecked(true);
    ui->backlogButton->setChecked(false);
    ui->teamButton->setChecked(false);
    ui->taskboardButton->setChecked(false);
    ui->confluenceButton->setChecked(false);
    ui->calendarButton->setChecked(false);
    ui->stackedWidget->setCurrentIndex(3);
    const int numOfRowsToAdd = 3;
}
void parentboard::on_confluenceButton_clicked()
{
    ui->confluenceButton->setChecked(true);
    ui->backlogButton->setChecked(false);
    ui->teamButton->setChecked(false);
    ui->sprintsButton->setChecked(false);
    ui->taskboardButton->setChecked(false);
    ui->calendarButton->setChecked(false);
    ui->stackedWidget->setCurrentIndex(4);
}
void parentboard::on_calendarButton_clicked()
{
    ui->calendarButton->setChecked(true);
    ui->backlogButton->setChecked(false);
    ui->teamButton->setChecked(false);
    ui->sprintsButton->setChecked(false);
    ui->confluenceButton->setChecked(false);
    ui->taskboardButton->setChecked(false);
    ui->stackedWidget->setCurrentIndex(5);
}



void parentboard::goBackToMainWindow() {
    MainWindow* mainWindow = new MainWindow; // Create a new instance of the main window
    hide(); // Hide the registration window
    mainWindow->showMaximized(); // Show the main window
    setTeamTableBool(false);
    this->close();
    ui->~parentboard();
}

int parentboard::setProjectId(int id) {
    currentProjectId = id;
    qDebug() << "ProjectID in ParentBoard: " << currentProjectId;
    return currentProjectId;
}

int parentboard::getProjectId() const {
    return currentProjectId;
}

int parentboard::setUserRoleID(TeamMember_ProjectsWindow *tmWindow) {
    if (tmWindow) {
        userRoleID = tmWindow->getPassValueRole();
        qDebug() << "setUserRoleID: " << userRoleID;
        adjustUIForUserRole(userRoleID);
    }
    return userRoleID;
}

void parentboard::adjustUIForUserRole(int role) {
    // Assuming 1 is the role with full access
    if (role != 1) {
        ui->backlogButton->setVisible(false);
        ui->sprintsButton->setVisible(false);
        ui->teamButton->setVisible(false);
    } else {
        // Show all tabs for full access users
        ui->backlogButton->setVisible(true);
        ui->sprintsButton->setVisible(true);
        ui->teamButton->setVisible(true);
    }
}




//------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------
//Public Access to the Objects of the parentboard.ui components for the other classes
//------------------------------------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------Blacklog----------------------------------------------------
QTableWidget* parentboard::getUserStoriesTableView() {
    return ui->user_stories;
}
QPushButton* parentboard::getButton_CreateUserStory(){
    return ui->Button_CreateUserStory;
}
QPushButton* parentboard::getButton_CreateTask(){
    return ui->Button_CreateTask;
}
QLabel* parentboard::getCreate_Assignee(){
    return ui->CreateAssignee;
}
QLabel* parentboard::getCreate_Description(){
    return ui->CreateDescription;
}
QLabel* parentboard::getCreate_Header(){
    return ui->CreateHeader;
}
QLabel* parentboard::getCreate_Priority(){
    return ui->CreatePriority;
}
QLabel* parentboard::getCreate_Status(){
    return ui->CreateStatus;
}
QLabel* parentboard::getCreate_Title(){
    return ui->CreateTitle;
}
QComboBox* parentboard::getInputAssignee(){
    return ui->InputAssignee;
}
QTextEdit* parentboard::getInputDescription(){
    return ui->InputDescription;
}
QTextEdit* parentboard::getInputPriority(){
    return ui->InputPriority;
}
QTextEdit* parentboard::getInputStatus(){
    return ui->InputStatus;
}
QTextEdit* parentboard::getInputTitle(){
    return ui->InputTitle;
}
QTableWidget* parentboard::getTeamTableView(){
    return ui->teamTable;
}
void parentboard::setTeamTableBool(const bool val){
    ui->teamTable->clear();
    ui->teamTable->reset();
    ui->teamTable->setRowCount(0);
    int rowSize = ui->teamTable->rowCount();
    for(int i = 0; i < rowSize; i++){
        ui->teamTable->removeRow(i);
    }
    isTeamTableActive = val;
    ui->teamTable->setHorizontalHeaderLabels({"First name","Last name", "Email", "Role"});
}

QComboBox* parentboard::get_BL_SprintDropDown(){
    return ui->BL_SprintDropDown;

}
QLabel* parentboard::get_SelecteSprint(){
    return ui->SelecteSprint;
}
QGroupBox* parentboard::getCreationBox(){
    return ui->CreationBox;

}
QPushButton* parentboard::get_delete_item(){
    return ui->delete_item;
}


//------------------------------------------------------Sprint--------------------------------------------------------
QTableWidget* parentboard::getSprintTableView() {
    return ui->sprint_table;
}
QComboBox* parentboard::getSprint_Top_Down(){
    return ui->sprint_top_down;
}
QLabel* parentboard::getSprintDate(){
    return ui->sprint_date;
}
QLineEdit* parentboard::getFirstNameField(){
    return ui->input_email;
}
QGroupBox* parentboard::getSprintGroupBox() const {
    return ui->sprintGroupBox;
}

QLineEdit* parentboard::get_Input_SprintName(){
    return ui->Input_SprintName;
}
QDateEdit* parentboard::get_Input_StartDate(){
    return ui->Input_StartDate;
}
QDateEdit* parentboard::get_Input_EndDate(){
    return ui->Input_EndDate;
}
QPushButton* parentboard::get_Button_CreateSprint(){
    return ui->CreateSprint_SprintTab;
}


//Sprint_View_Box

QGroupBox* parentboard::get_Sprint_View_Box() {
    return ui->Sprint_View_Box;
}
QLineEdit* parentboard::get_Line_EditSprintEndDate() {
    return ui->Edit_Sprint_EndDate;
}
QLineEdit* parentboard::get_LineEdit_SprintName() {
    return ui->Edit_Sprint_Name;
}

QLineEdit* parentboard::get_LineEdit_SprintStartDate() {
    return ui->Edit_Sprint_StartDate;
}

QLabel* parentboard::get_Label_Sprint_EndDate() {
    return ui->Label_Sprint_EndDate;
}

QLabel* parentboard::get_Label_SprintStartDate() {
    return ui->Label_Sprint_StartDate;
}

QLabel* parentboard::get_Label_SprintTitle() {
    return ui->Label_Sprint_Title;
}

QLabel* parentboard::get_Label_TaskName() {
    return ui->Label_Task_TableName;
}

QTableWidget* parentboard::get_Table_SprintDetails() {
    return ui->SprintDetails_Table;
}

//Sprint Group Box
QGroupBox* parentboard::get_GroupBox_SprintGroup() {
    return ui->sprintGroupBox;
}

QPushButton* parentboard::get_Button_CreateSprintTab() {
    return ui->CreateSprint_SprintTab;
}

QDateEdit* parentboard::get_DateEdit_InputEndDate() {
    return ui->Input_EndDate;
}

QTextEdit* parentboard::get_TextEdit_InputSprintGoal() {
    return ui->Input_SprintGoal;
}

QLineEdit* parentboard::get_LineEdit_InputSprintName() {
    return ui->Input_SprintName;
}

QDateEdit* parentboard::get_DateEdit_InputStartDate() {
    return ui->Input_StartDate;
}

QLabel* parentboard::get_DateEdit_Text_EndDate() {
    return ui->Text_EndDate;
}
QLabel* parentboard::get_Label_TextName() {
    return ui->Text_Name;
}

QLabel* parentboard::get_Label_TextSprintGoal() {
    return ui->Text_SprintGoal;
}

QLabel* parentboard::get_Label_TextStartDate() {
    return ui->Text_StartDate;
}


QPushButton* parentboard::get_sprint_createtask_button(){
    return ui->sprintinfo_save_button;
}

//Team

QPushButton* parentboard::getCreateUserButton()
{
    return ui->CreateUser_Button;
}

QComboBox* parentboard::getComboBoxRole()
{
    return ui->comboBox_role;
}

QTextBrowser* parentboard::getTeamErrorDisplay()
{
    return ui->TeamError_display;
}
QLabel* parentboard::getDisplayFirstName()
{
    return ui->display_firstname;
}
QLabel* parentboard::getDisplayRole()
{
    return ui->display_role;
}
QLineEdit* parentboard::getInputEmail()
{
    return ui->input_email;
}


//Confluence

QTreeWidget* parentboard::getuserTaskTreeWidget_2(){
    return ui->userTaskTreeWidget_2;
}

QTextEdit* parentboard::get_InputTitle_2() {
    return ui->InputTitle_2;
}
QComboBox* parentboard::get_InputGroup_Confluence_Heading() {
    return ui->InputGroup_Confluence_Heading;
}
QLabel* parentboard::get_Confluence_NameText() {
    return ui->Confluence_NameText;
}
QLabel* parentboard::get_Confluence_HeadingText() {
    return ui->Confluence_HeadingText;
}
QLabel* parentboard::get_Confluence_GroupText() {
    return ui->Confluence_GroupText;
}
QGroupBox* parentboard::getCreationBox_Confluence() const {
    return ui->CreationBox_Confluence;
}

//BAR-BUTTONS
QPushButton* parentboard::get_ButtonGroup_Confluence(){
    return ui->ButtonGroup_Confluence;
}
QPushButton* parentboard::get_ButtonPage_Confluence(){
    return ui->ButtonPage_Confluence;
}

//LOWER-BUTTONS
QPushButton* parentboard::get_Button_CreatePage_Confluence(){
    return ui->Button_CreatePage_Confluence;
}
QPushButton* parentboard::get_Button_Create_Confluence() {
    return ui->Button_Create_Confluence;
}

QTreeWidget* parentboard::get_userTaskTreeWidget_2(){
    return ui->userTaskTreeWidget_2;
}

//Calendar

QPushButton* parentboard::get_Button_SaveCalendar(){
    return ui->Button_SaveCalendar;
}

QLabel* parentboard::get_CalendarDescription() {
    return ui->CalendarDescription;
}

QLabel* parentboard::get_CalendarHeading() {
    return ui->CalendarHeading;
}

QLabel* parentboard::get_CalendarTitle() {
    return ui->CalendarTitle;
}
QTextEdit* parentboard::get_Input_Calendar_Description(){
    return ui->Input_Calendar_Description;
}
QTextEdit* parentboard::get_Input_Calendar_Title(){
    return ui->Input_Calendar_Title;
}
QGroupBox* parentboard::get_Calendar_GroupBox(){
    return ui->groupBox;
}

CustomCalendarWidget* parentboard::get_CalendarWidget() {
    return static_cast<CustomCalendarWidget*>(ui->calendarWidget);
}
QPushButton* parentboard::get_Button_DeleteCalendar(){
    return ui->Button_DeleteCalendar;
}

// ----------------------------------------------------Taskboard----------------------------------------------------
QComboBox* parentboard::getSprintDropdown() const
{
    return ui->sprintDropdownT;
}
QVBoxLayout* parentboard::getScrollAreaLayout() const
{
    return scrollAreaLayout;
}
QTextEdit* parentboard::getTaskboardTextEdit() const {
    return taskboardTextEdit;
}
QTreeWidget* parentboard::getTaskTreeWidget() const {
    return ui->userTaskTreeWidgetT;
}
void parentboard::updateSprintDateLabel(const QString& newText)
{
    ui->labelDateT->setText(newText);
}


// Task Creation/Edit

// Buttons
QPushButton* parentboard::getButton_CreateTaskT(){
    return ui->Button_CreateTaskT;
}

// Labels
QLabel* parentboard::getCreate_AssigneeT(){
    return ui->CreateAssigneeT;
}
QLabel* parentboard::getCreate_DescriptionT(){
    return ui->CreateDescriptionT;
}
QLabel* parentboard::getCreate_StatusT(){
    return ui->CreateStatusT;
}
QLabel* parentboard::getCreate_TitleT(){
    return ui->CreateTitleT;
}
QLabel* parentboard::getCreate_HeaderT(){
    return ui->CreateHeaderT;
}

// Text
QComboBox* parentboard::getInputAssigneeT(){
    return ui->InputAssigneeT;
}
QTextEdit* parentboard::getInputDescriptionT(){
    return ui->InputDescriptionT;
}
QTextEdit* parentboard::getInputStatusT(){
    return ui->InputStatusT;
}
QTextEdit* parentboard::getInputTitleT(){
    return ui->InputTitleT;
}
QLabel* parentboard::get_SelectedSprintT(){
    return ui->SelectedSprintT;
}
QComboBox* parentboard::get_BL_SprintDropDownT(){
    return ui->BL_SprintDropDownT;
}

// Box
QGroupBox* parentboard::getCreationBoxT(){
    return ui->CreationBoxT;
}

// Edit
void parentboard::updateInputTitleT(const QString& data)
{
    ui->InputTitleT->append(data);
}
void parentboard::updateInputDescriptionT(const QString& data)
{
    ui->InputDescriptionT->append(data);
}
void parentboard::updateInputStatusT(const QString& data)
{
    ui->InputStatusT->append(data);
}
void parentboard::updateInputAssigneeT(int idUser)
{
    QComboBox* assigneeDropdownT = ui->InputAssigneeT;

    // Find the index of the item with the specified data
    int index = assigneeDropdownT->findData(QVariant(idUser));

    if (index != -2) {
        assigneeDropdownT->setCurrentIndex(index);
        qDebug() << "PARENTBOARD: TASKBOARD: assigneeDropdownT - idUser" << index;
    } else {
        qDebug() << "PARENTBOARD: TASKBOARD: assigneeDropdownT - idUser not found" << index;
    }
}

void parentboard::updateBL_SprintDropDownT(int idSprint)
{

    QComboBox* sprintDropdownT = ui->BL_SprintDropDownT;

    // Find the index of the item with the specified data
    int index = sprintDropdownT->findData(QVariant(idSprint));

    if (index != -1) {
        sprintDropdownT->setCurrentIndex(index);
        qDebug() << "PARENTBOARD: TASKBOARD: updateBL_SprintDropDownT - idSprint" << index;
    } else {
        qDebug() << "PARENTBOARD: TASKBOARD: updateBL_SprintDropDownT - idSprint not found" << index;
    }
}


// Centering Window
void parentboard::centerOnScreen()
{
    // Center the window on the screen
    QScreen *screenProject = QApplication::primaryScreen();
    QRect mainScreenGeometry = screenProject->availableGeometry();
    move(mainScreenGeometry.center() - rect().center());

    //qDebug() << "Centering on screen.";
}


//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------





