#ifndef PARENTBOARD_H
#define PARENTBOARD_H
#include "QtWidgets/qboxlayout.h"
#include "QTreeWidget"
#include "qcombobox.h"
#include "qgroupbox.h"
#include "qpushbutton.h"
#include "qtextbrowser.h"
#include <QWidget>
#include <QStandardItemModel>
#include <QTableWidget> // Include QTableWidget header
#include <QLineEdit>
#include <QLabel>
#include <QDateEdit>
#include "teammember_projectswindow.h"
#include "customcalendarwidget.h"


namespace Ui {
class parentboard;
}

class parentboard : public QMainWindow
{
    Q_OBJECT

public:
    bool isTeamTableActive;
    explicit parentboard(QWidget *parent = nullptr);
    ~parentboard();
    QWidget* getSomeWidget(); // Declare the function
    QTableWidget* getUserStoriesTableView();
    QTableWidget* getIssuesTableView();
    QComboBox* getSprint_Top_Down();
    QPushButton* on_create_sprint_clicked();
    QTableWidget* getSprintTableView();
    QTableWidget* getTeamTableView();
    void setTeamTableBool(const bool val);
    QTextBrowser *getSprintDate();
    QLineEdit *getFirstNameField();
    void displayBacklogOnMaximized();
    QGroupBox* getSprintGroupBox() const;
    //QComboBox* getSprintComboBox();


    QPushButton* getButton_Create();
    QTextBrowser* getCreate_Assignee();
    QTextBrowser* getCreate_Description();
    QTextBrowser* getCreate_Header();
    QTextBrowser* getCreate_Priority();
    QTextBrowser* getCreate_Status();
    QTextBrowser* getCreate_Title();

    QPushButton* getCreateUserButton();
    QTextBrowser* getDisplayFirstName();
    QTextBrowser* getDisplayRole();
    QLineEdit* getInputEmail();
    QComboBox* getComboBoxRole();
    QTextBrowser* getTeamErrorDisplay();

    QComboBox* getInputAssignee();
    QTextEdit* getInputDescription();
    QTextEdit* getInputPriority();
    QTextEdit* getInputStatus();
    QTextEdit* getInputTitle();
    QPushButton* getButton_CreateTask();
    QPushButton* getButton_CreateUserStory();
    QPushButton* get_delete_item();
    QComboBox* get_BL_SprintDropDown();
    QTextBrowser* get_SelecteSprint();

    QLineEdit* get_Input_SprintName();
    QDateEdit* get_Input_StartDate();
    QDateEdit* get_Input_EndDate();
    QPushButton* get_Button_CreateSprint();
    QGroupBox* getCreationBox();

    //Confluence
    QTextEdit* get_InputTitle_2();
    QComboBox* get_InputGroup_Confluence_Heading();
    QTextBrowser* get_Confluence_NameText();
    QTextBrowser* get_Confluence_HeadingText();
    QTextBrowser* get_Confluence_GroupText();
    QPushButton* get_Button_Create_Confluence();
    QTreeWidget* getuserTaskTreeWidget_2();
    QGroupBox* getCreationBox_Confluence() const;
    QPushButton* get_Button_CreatePage_Confluence();
    QPushButton* get_ButtonPage_Confluence();
    QPushButton* get_ButtonGroup_Confluence();
    QTreeWidget* get_userTaskTreeWidget_2();


    //Calendar
    QPushButton* get_Button_SaveCalendar();
    QLabel* get_CalendarDescription();
    QLabel* get_CalendarHeading();
    QLabel* get_CalendarTitle();
    QTextEdit* get_Input_Calendar_Description();
    QTextEdit* get_Input_Calendar_Title();
    QGroupBox* get_Calendar_GroupBox();
    CustomCalendarWidget* get_CalendarWidget();

    static parentboard* getInstance(QWidget *parent = nullptr) {
        if (instance == nullptr) {
            instance = new parentboard(parent);
        }
        return instance;
    }
    int setProjectId(int id);
    int getProjectId() const;
    int setUserRoleID(int RoleID);

    /// ------- Taskboard ---------
    QComboBox* getSprintDropdown() const;
    QVBoxLayout* getScrollAreaLayout() const;
    QTextEdit* getTaskboardTextEdit() const;
    QTreeWidget* getTaskTreeWidget() const;
    void updateSprintDateLabel(const QString& newText);

    // ------ Task Creation --------
    // Input
    QGroupBox* getCreationBoxT();
    QLabel* get_SelectedSprintT();
    QTextEdit* getInputTitleT();
    QTextEdit* getInputStatusT();
    QTextEdit* getInputDescriptionT();
    QComboBox* getInputAssigneeT();

    // Labels
    QLabel* getCreate_HeaderT();
    QLabel* getCreate_TitleT();
    QLabel* getCreate_StatusT();
    QLabel* getCreate_DescriptionT();
    QLabel* getCreate_AssigneeT();
    QComboBox* get_BL_SprintDropDownT();

    // Buttons
    QPushButton* getButton_CreateTaskT();

    // Update/Edit
    void updateInputStatusT(const QString& data);
    void updateInputTitleT(const QString& data);
    void updateInputDescriptionT(const QString& data);
    void updateInputAssigneeT(int data);
    void updateBL_SprintDropDownT(int data);


    //Sprint
    QGroupBox* get_Sprint_View_Box();
    QLineEdit* get_Line_EditSprintEndDate();
    QLineEdit* get_LineEdit_SprintName();
    QLineEdit* get_LineEdit_SprintStartDate();
    QLabel* get_Label_Sprint_EndDate();
    QLabel* get_Label_SprintStartDate();
    QLabel* get_Label_SprintTitle();
    QLabel* get_Label_TaskName();
    QTableWidget* get_Table_SprintDetails();
    QGroupBox* get_GroupBox_SprintGroup();
    QPushButton* get_Button_CreateSprintTab();
    QDateEdit* get_DateEdit_InputEndDate();
    QTextEdit* get_TextEdit_InputSprintGoal();
    QLineEdit* get_LineEdit_InputSprintName();
    QDateEdit* get_DateEdit_InputStartDate();
    QLabel* get_DateEdit_Text_EndDate();
    QLabel* get_Label_TextName();
    QLabel* get_Label_TextSprintGoal();
    QLabel* get_Label_TextStartDate();
    QPushButton* get_sprint_createtask_button();
    QPushButton* get_Button_DeleteCalendar();
    int setUserRoleID(TeamMember_ProjectsWindow *tmWindow);
    void adjustUIForUserRole(int role);

    // Add this setter method


private slots:
    void on_taskboardButton_clicked();
    void on_Issue_selected();
    void on_teamButton_clicked();
    void on_backlogButton_clicked();
    void on_sprintsButton_clicked();
    void on_confluenceButton_clicked();
    void goBackToMainWindow();
    void on_calendarButton_clicked();
    void centerOnScreen();


protected:
    // Resize
    // void resizeEvent(QResizeEvent *event) override;

    void on_meetingButton_clicked();
    void UserSpecificView(int value);
private:

    Ui::parentboard *ui;
    QStandardItemModel *taskModel;
    int currentProjectId;
    int userRoleID;
    static parentboard* instance;  // Static instance
    // Taskboard
    QVBoxLayout *scrollAreaLayout;
    QTextEdit* taskboardTextEdit;
    QTreeWidget* userTaskTreeWidget;

};

#endif // PARENTBOARD_H
