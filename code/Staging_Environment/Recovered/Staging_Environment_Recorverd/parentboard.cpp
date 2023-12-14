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

parentboard* parentboard::instance = nullptr;


parentboard::parentboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::parentboard),
    scrollAreaLayout(new QVBoxLayout(this))
{
    ui->setupUi(this);


    taskModel = new QStandardItemModel(this);
    taskModel->setColumnCount(2);
    ui->sprint_table->setColumnCount(2);
    ui->sprint_table->setHorizontalHeaderLabels({"Task Name", "Description"}); // Set column headers
    ui->user_stories->setColumnCount(3); // Add a new column for priority
    ui->user_stories->setHorizontalHeaderLabels({"Userstory", "Description", "Priority"}); // Set column headers
//    ui->issues->setColumnCount(3); // Add a new column for priority
//    ui->issues->setHorizontalHeaderLabels({"Issue", "Description", "Priority"}); // Set column headers


//  pb_productbacklog Implementation Calls
    parentboard *obj = this; // Create an instance of parentboard
    pb_team_implemenation *teamPagePtr = new pb_team_implemenation(obj);
    pb_productbacklog_implementation *pbProductBacklogObj = new pb_productbacklog_implementation(obj);
    pbProductBacklogObj->Hide_CreateSection();
    connect(ui->backlogButton, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::RetrieveAndDisplayBacklog);

    connect(ui->button_userstory, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::Show_CreateSection);
    connect(ui->buttton_issue, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::Show_CreateSection);

    connect(ui->button_userstory, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::Show_CreateSection_UserStory);
    connect(ui->buttton_issue, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::Show_CreateSection_Tasks);

    //CREATE USERSTORY AND TASKS
    connect(ui->Button_CreateTask, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::onButtonIssueClicked);
    connect(ui->Button_CreateUserStory, &QPushButton::clicked, pbProductBacklogObj, &pb_productbacklog_implementation::on_createUserStory_clicked);


    connect(ui->user_stories, &QTableWidget::itemChanged, pbProductBacklogObj, &pb_productbacklog_implementation::onTableItemChanged);
    connect(ui->user_stories, &QTableWidget::itemChanged, pbProductBacklogObj, &pb_productbacklog_implementation::onUserStoryTableItemChanged);



//  pb_sprint Implementation Calls
    pb_sprint_implemenation *pbSprintBObj = new pb_sprint_implemenation(obj); //Accessing the pb_sprint_implementation class
    connect(ui->sprint_createtask_button, &QPushButton::clicked, pbSprintBObj, &pb_sprint_implemenation::on_createtask_sprint_clicked);
    connect(ui->sprint_create_button, &QPushButton::clicked, pbSprintBObj, &pb_sprint_implemenation::on_create_sprint_clicked);
    connect(ui->edit_sprint_button, &QPushButton::clicked, pbSprintBObj, &pb_sprint_implemenation::on_editsprint_sprint_clicked);
    connect(ui->sprintsButton,&QPushButton::clicked,pbSprintBObj,&pb_sprint_implemenation::RetrieveAndDisplayTask);



//  pb_team Implementation Calls
    connect(ui->CreateUser_Button, &QPushButton::clicked, teamPagePtr, &pb_team_implemenation::on_createuser_clicked);

    //Old Way
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(goBackToMainWindow()));
    connect(ui->button_userstory, SIGNAL(clicked()), this, SLOT(test()));
    connect(ui->confluence_backbutton, SIGNAL(clicked()), this, SLOT(confluence_class()));

    // Taskboard
    pb_taskboard_implemenation *pbTaskboardBObj = new pb_taskboard_implemenation(obj);
}
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
    ui->stackedWidget->setCurrentIndex(0);
    const int numOfRowsToAdd = 3;
}
void parentboard::on_Issue_selected(){

}
void parentboard::on_backlogButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    const int numOfRowsToAdd = 3;
}
void parentboard::on_teamButton_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
}
void parentboard::on_sprintsButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    const int numOfRowsToAdd = 3;
}
void parentboard::on_confluenceButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
void parentboard::confluence_class(){
    PB_Confluence_Implemenation confluence_class_obj;
    confluence_class_obj.backbutton();
}
void parentboard::goBackToMainWindow() {
    MainWindow* mainWindow = new MainWindow; // Create a new instance of the main window
    hide(); // Hide the registration window
    mainWindow->showMaximized(); // Show the main window
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
//------------------------------------------------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------------------------------------------------
//Public Access to the Objects of the parentboard.ui components for the other classes
//------------------------------------------------------------------------------------------------------------------------------------------------
//Blacklog
QTableWidget* parentboard::getUserStoriesTableView() {
    return ui->user_stories;
}
//
QPushButton* parentboard::getButton_CreateUserStory(){
    return ui->Button_CreateUserStory;
}
QPushButton* parentboard::getButton_CreateTask(){
    return ui->Button_CreateTask;
}
QTextBrowser* parentboard::getCreate_Assignee(){
    return ui->CreateAssignee;
}
QTextBrowser* parentboard::getCreate_Description(){
    return ui->CreateDescription;
}
QTextBrowser* parentboard::getCreate_Header(){
    return ui->CreateHeader;
}
QTextBrowser* parentboard::getCreate_Priority(){
    return ui->CreatePriority;
}
QTextBrowser* parentboard::getCreate_Status(){
    return ui->CreateStatus;
}
QTextBrowser* parentboard::getCreate_Title(){
    return ui->CreateTitle;
}
QTextEdit* parentboard::getInputAssignee(){
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







//Sprint
QTableWidget* parentboard::getSprintTableView() {
    return ui->sprint_table;
}
QComboBox* parentboard::getSprint_Top_Down(){
    return ui->sprint_top_down;
}
QTextBrowser* parentboard::getSprintDate(){
    return ui->sprint_date;
}
QLineEdit* parentboard::getFirstNameField(){
    return ui->input_firstname;
}
QGroupBox* parentboard::getSprintGroupBox() const {
    return ui->sprintGroupBox;  // Replace "yourGroupBoxName" with the actual name of your group box
}
//Confluence
QWidget* parentboard::getSomeWidget() {
    return ui->confluence_backbutton;
}




// Taskboard
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
    return ui->userTaskTreeWidget;
}
void parentboard::updateSprintDateLabel(const QString& newText)
{
    ui->labelDateT->setText(newText);
}






//------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------



