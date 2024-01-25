#include "qtunittest.h"
#include "databasemanager.h"
#include <QtTest/QTest>
#include "mainwindow.h"
#include "adminstrator.h"
#include "backlog.h"
#include "calendar.h"
#include "confluence.h"
#include "issuecreation.h"
#include "launchscreen.h"
#include "parentboard.h"
#include "projectcreation.h"
#include "projectsadmin.h"
#include "registration_window.h"
#include "settings.h"
#include "sprints.h"
#include "taskboard.h"
#include "pb_confluence_implemenation.h"
#include "teammember_projectswindow.h"
//#include "pb_confluence_implemenation.h"
#include "pb_productbacklog_implementation.h"
#include "pb_sprint_implemenation.h"
#include "pb_calendar_implemenation.h"
//#include "pb_taskboard_implemenation.h"
//#include "pb_team_implemenation.h"



QTUnitTest::QTUnitTest(){}

void QTUnitTest::DatabaseCheck() {
    DatabaseManager dbManager;
    QVERIFY2(dbManager.getDatabase().isValid(), "Database connection failed to establish.");
}
void QTUnitTest::MainWindowTest() {

    //MainWindow Test
    MainWindow mainWindow;
    mainWindow.show();
    mainWindow.hide();
    QVERIFY2(!mainWindow.isVisible(), "MainWindow .ui test not passed");

    //Test Credentials
    QLineEdit* InputUsername = mainWindow.getInput_Username();
    QLineEdit* InputPassword = mainWindow.getInput_Password();
    InputUsername->setText("aida");
    InputPassword->setText("aida");
    mainWindow.userEncryptedLogin();
}


//Implementation of the Tests of the adminstrator.cpp
void QTUnitTest::AdminstratorTest(){

    adminstrator administratorWindow;
    administratorWindow.show();
    administratorWindow.hide();
    QVERIFY2(!administratorWindow.isVisible(), "adminstrator .ui test not passed");

}


//Implementation of the Tests of the backlog.cpp
void QTUnitTest::BacklogTest(){

    Backlog backlogWindow;
    backlogWindow.show();
    backlogWindow.hide();
    QVERIFY2(!backlogWindow.isVisible(), "backlog .ui test not passed");

}

//Implementation of the Tests of the calendar.cpp
void QTUnitTest::CalendarTest(){
    Calendar calendarWindow;
    calendarWindow.show();
    calendarWindow.hide();
    QVERIFY2(!calendarWindow.isVisible(), "calendar .ui test not passed");


}

//Implementation of the Tests of the confluence.cpp
void QTUnitTest::ConfluenceTest() {
    Confluence confluenceWindow;
    confluenceWindow.show();
    confluenceWindow.hide();
    QVERIFY2(!confluenceWindow.isVisible(), "confluence .ui test not passed");


}

//Implementation of the Tests of the issuecreation.cpp
void QTUnitTest::IssuecreationTest(){
    IssueCreation issueCreationWindow;
    issueCreationWindow.show();
    issueCreationWindow.hide();
    QVERIFY2(!issueCreationWindow.isVisible(), "issuecreation .ui test not passed");

}

//Implementation of the Tests of the launchscreen.cpp
void QTUnitTest::LaunchscreenTest(){
    LaunchScreen launchScreenWindow;
    launchScreenWindow.show();
    launchScreenWindow.hide();
    QVERIFY2(!launchScreenWindow.isVisible(), "launchScreenWindow .ui test not passed");

}

//Implementation of the Tests of the parentboard.cpp
void QTUnitTest::Parentboardtest(){
   class parentboard parenboardWindow;
    parenboardWindow.show();
    parenboardWindow.hide();
    QVERIFY2(!parenboardWindow.isVisible(), "parenboardWindow .ui test not passed");


}

//Implementation of the Tests of the pb_confluence_implementation.cpp
void QTUnitTest::Pb_confluence_implementationTest(){

}


//Implementation of the Tests of the pb_productbacklog_implementation.cpp
void QTUnitTest::Pb_productbacklog_implementationTest(){

}


//Implementation of the Tests of the pb_sprint_implementation.cpp
void QTUnitTest::Pb_sprint_implemenationTest(){

}

//Implementation of the Tests of the pb_taskboard_implementation.cpp
void QTUnitTest::Pb_taskboard_implemenationTest(){

}


//Implementation of the Tests of the pb_team_implementation.cpp
void QTUnitTest::Pb_team_implemenationTest(){

}


//Implementation of the Tests of the projectcreation.cpp
void QTUnitTest::ProjectcreationTest(){
    ProjectCreation projectCreationWindow;
    projectCreationWindow.show();
    projectCreationWindow.hide();
    QVERIFY2(!projectCreationWindow.isVisible(), "projectCreationWindow .ui test not passed");

}


//Implementation of the Tests of the projectsadmin.cpp
void QTUnitTest::ProjectsadminTest(){
    ProjectsAdmin projectsAdminWindow;
    projectsAdminWindow.show();
    projectsAdminWindow.hide();
    QVERIFY2(!projectsAdminWindow.isVisible(), "projectsAdminWindow .ui test not passed");

}


//Implementation of the Tests of the registration_window.cpp
void QTUnitTest::RegistrationTest(){
    registration_window registration_windowWindow; //change the name
    registration_windowWindow.show();
    registration_windowWindow.hide();
    QVERIFY2(!registration_windowWindow.isVisible(), "registration_windowWindow .ui test not passed");

}

//Implementation of the Tests of the settings.cpp
void QTUnitTest::SettingsTest(){
     Settings settingsWindow;
     settingsWindow.show();
     settingsWindow.hide();
     QVERIFY2(!settingsWindow.isVisible(), "settingsWindow .ui test not passed");


}


//Implementation of the Tests of the sprints.cpp
void QTUnitTest::SprintsTest(){
     Sprints sprintsWindow;
     sprintsWindow.show();
     sprintsWindow.hide();
     QVERIFY2(!sprintsWindow.isVisible(), "sprintsWindow .ui test not passed");


}

//Implementation of the Tests of the taskboard.cpp
void QTUnitTest::TaskboardTest(){
     TaskBoard taskBoardWindow;
     taskBoardWindow.show();
     taskBoardWindow.hide();
     QVERIFY2(!taskBoardWindow.isVisible(), "taskBoardWindow .ui test not passed");


}

void QTUnitTest::Teammember_projectswindowTest(){
     TeamMember_ProjectsWindow teamMember_ProjectsWindowWindow;//change the name
     teamMember_ProjectsWindowWindow.show();
     teamMember_ProjectsWindowWindow.hide();
     QVERIFY2(!teamMember_ProjectsWindowWindow.isVisible(), "teamMember_ProjectsWindowWindow .ui test not passed");

}

/**
 * @brief Test for the PB_Confluence_Implemenation class.
 *
 * This test verifies the functionality of the "HideCreationSection" method
 * in the PB_Confluence_Implemenation class. It checks whether the appropriate UI
 * elements are hidden after the method is called. The test relies on
 * the parentboard class for UI elements and checks their visibility status.
 *
 * @note This test uses the 'parentboard' class instance and checks the visibility
 * of 'CreationBox_Confluence' and 'CreationBox' UI elements.
 */
//Ui.Component Visibilty - - - - - - - - - - - - - - - - - - Confluence - - - - - - - - - - - -
void QTUnitTest::PB_Confluence_HideCreationSection_Test() {
    // Correct usage with 'class' keyword
    class parentboard parentBoardInstance;
    PB_Confluence_Implemenation confluenceImplementation(&parentBoardInstance);
    confluenceImplementation.HideCreationSection();
    QVERIFY2(!parentBoardInstance.getCreationBox_Confluence()->isVisible(),
             "CreationBox_Confluence is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_InputTitle_2()->isVisible(),
             "InputTitle_2 is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_InputGroup_Confluence_Heading()->isVisible(),
             "InputGroup_Confluence_Heading is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Confluence_NameText()->isVisible(),
             "Confluence_NameText is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Confluence_HeadingText()->isVisible(),
             "Confluence_HeadingText is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Confluence_GroupText()->isVisible(),
             "Confluence_GroupText is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Button_Create_Confluence()->isVisible(),
             "Button_Create_Confluence is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getuserTaskTreeWidget_2()->isVisible(),
             "userTaskTreeWidget_2 is still visible (Failed)");


}


//Ui.Component Visibilty - - - - - - - - - - - - - - - - - - Sprint - - - - - - - - - - - -
void QTUnitTest::PB_Sprint_OBJECTS_VISIBLE_BOXES(){


    class parentboard parentBoardInstance;
    pb_sprint_implemenation sprintImplementation(&parentBoardInstance);

    // Call the method to test
    sprintImplementation.OBJECTS_VISIBLE_BOXES();

    // Now verify each component is invisible
    QVERIFY2(!parentBoardInstance.getSprintDate()->isVisible(), "SprintDate is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getSprint_Top_Down()->isVisible(), "Sprint_Top_Down is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getSprintGroupBox()->isVisible(), "SprintGroupBox is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Line_EditSprintEndDate()->isVisible(), "Line_EditSprintEndDate is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Label_SprintTitle()->isVisible(), "Label_SprintTitle is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Label_TaskName()->isVisible(), "Label_TaskName is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Table_SprintDetails()->isVisible(), "Table_SprintDetails is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_GroupBox_SprintGroup()->isVisible(), "GroupBox_SprintGroup is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Button_CreateSprintTab()->isVisible(), "Button_CreateSprintTab is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_DateEdit_InputEndDate()->isVisible(), "DateEdit_InputEndDate is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_TextEdit_InputSprintGoal()->isVisible(), "TextEdit_InputSprintGoal is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_LineEdit_InputSprintName()->isVisible(), "LineEdit_InputSprintName is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_DateEdit_InputStartDate()->isVisible(), "DateEdit_InputStartDate is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_DateEdit_Text_EndDate()->isVisible(), "DateEdit_Text_EndDate is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Label_TextName()->isVisible(), "Label_TextName is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Label_TextSprintGoal()->isVisible(), "Label_TextSprintGoal is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Label_TextStartDate()->isVisible(), "Label_TextStartDate is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Sprint_View_Box()->isVisible(), "Sprint_View_Box is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_LineEdit_SprintName()->isVisible(), "LineEdit_SprintName is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_LineEdit_SprintStartDate()->isVisible(), "LineEdit_SprintStartDate is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Label_Sprint_EndDate()->isVisible(), "Label_Sprint_EndDate is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Label_SprintStartDate()->isVisible(), "Label_SprintStartDate is still visible (Failed)");

}


void QTUnitTest::PB_Sprint_OBJECTS_VISIBLE_on_create_sprint_clicked(){


    // Assuming you have a class 'parentboard' and an instance 'parentBoardInstance'
    class parentboard parentBoardInstance;
    pb_sprint_implemenation sprintImplementation(&parentBoardInstance);

    // Call the method to test
    sprintImplementation.OBJECTS_VISIBLE_on_create_sprint_clicked();

    // Verify that certain components are invisible
    QVERIFY2(!parentBoardInstance.get_Sprint_View_Box()->isVisible(), "Sprint_View_Box is still visible (Failed)");

    // Verify that certain components are visible
    QVERIFY2(parentBoardInstance.get_Button_CreateSprintTab()->isVisible(), "Button_CreateSprintTab is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_DateEdit_InputEndDate()->isVisible(), "DateEdit_InputEndDate is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_TextEdit_InputSprintGoal()->isVisible(), "TextEdit_InputSprintGoal is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_LineEdit_InputSprintName()->isVisible(), "LineEdit_InputSprintName is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_DateEdit_InputStartDate()->isVisible(), "DateEdit_InputStartDate is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_DateEdit_Text_EndDate()->isVisible(), "DateEdit_Text_EndDate is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_Label_TextName()->isVisible(), "Label_TextName is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_Label_TextSprintGoal()->isVisible(), "Label_TextSprintGoal is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_Label_TextStartDate()->isVisible(), "Label_TextStartDate is not visible (Failed)");



}


void QTUnitTest::PB_Sprint_OBJECTS_VISIBLE_Additional_Details(){
    // Assuming you have a class 'parentboard' and an instance 'parentBoardInstance'
    class parentboard parentBoardInstance;
    pb_sprint_implemenation sprintImplementation(&parentBoardInstance);

    // Call the method to test
    sprintImplementation.OBJECTS_VISIBLE_Additional_Details();

    // Verify that certain components are invisible
    QVERIFY2(!parentBoardInstance.get_GroupBox_SprintGroup()->isVisible(), "GroupBox_SprintGroup is still visible (Failed)");

    // Verify that certain components are visible
    QVERIFY2(parentBoardInstance.get_Label_SprintTitle()->isVisible(), "Label_SprintTitle is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_Table_SprintDetails()->isVisible(), "Table_SprintDetails is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_Label_TaskName()->isVisible(), "Label_TaskName is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_Sprint_View_Box()->isVisible(), "Sprint_View_Box is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_LineEdit_SprintName()->isVisible(), "LineEdit_SprintName is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_LineEdit_SprintStartDate()->isVisible(), "LineEdit_SprintStartDate is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_Label_Sprint_EndDate()->isVisible(), "Label_Sprint_EndDate is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_Label_SprintStartDate()->isVisible(), "Label_SprintStartDate is not visible (Failed)");

}

//Ui.Component Visibilty - - - - - - - - - - - - - - - - - - Backlog - - - - - - - - - - - -
void QTUnitTest::Show_CreateSection_UserStory(){

    class parentboard parentBoardInstance;
    pb_productbacklog_implementation backlogImplementation(&parentBoardInstance);

    // Call the method to test
    backlogImplementation.Show_CreateSection_UserStory();

    // Verify the visibility of components
    QVERIFY2(parentBoardInstance.getButton_CreateUserStory()->isVisible(), "Button_CreateUserStory is not visible (Failed)");
    QVERIFY2(!parentBoardInstance.getButton_CreateTask()->isVisible(), "Button_CreateTask is still visible (Failed)");

    QVERIFY2(!parentBoardInstance.get_BL_SprintDropDown()->isVisible(), "BL_SprintDropDown is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_SelecteSprint()->isVisible(), "SelecteSprint is still visible (Failed)");

    // Verify properties of the Create_Header label
    QLabel* Create_Header = parentBoardInstance.getCreate_Header();
    QVERIFY2(Create_Header->alignment() == Qt::AlignCenter, "Create_Header alignment is not center (Failed)");
    QVERIFY2(Create_Header->text() == "Create User Story", "Create_Header text is not 'Create User Story' (Failed)");
}
void QTUnitTest::Hide_CreateSection(){

    class parentboard parentBoardInstance;
    pb_productbacklog_implementation backlogImplementation(&parentBoardInstance);

    // Call the method to test
    backlogImplementation.Hide_CreateSection();

    // Verify that each component is invisible
    QVERIFY2(!parentBoardInstance.getCreate_Assignee()->isVisible(), "Create_Assignee is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getCreate_Description()->isVisible(), "Create_Description is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getCreate_Header()->isVisible(), "Create_Header is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getCreate_Priority()->isVisible(), "Create_Priority is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getCreate_Status()->isVisible(), "Create_Status is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getCreate_Title()->isVisible(), "Create_Title is still visible (Failed)");

    QVERIFY2(!parentBoardInstance.getInputAssignee()->isVisible(), "InputAssignee is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getInputDescription()->isVisible(), "InputDescription is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getInputPriority()->isVisible(), "InputPriority is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getInputStatus()->isVisible(), "InputStatus is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getInputTitle()->isVisible(), "InputTitle is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getButton_CreateUserStory()->isVisible(), "Button_CreateUserStory is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.getButton_CreateTask()->isVisible(), "Button_CreateTask is still visible (Failed)");

    QVERIFY2(!parentBoardInstance.get_BL_SprintDropDown()->isVisible(), "BL_SprintDropDown is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_SelecteSprint()->isVisible(), "SelecteSprint is still visible (Failed)");
}
void QTUnitTest::Show_CreateSection(){
    class parentboard parentBoardInstance;
    pb_productbacklog_implementation backlogImplementation(&parentBoardInstance);

    // Call the method to test
    backlogImplementation.Show_CreateSection_UserStory();  // Using Show_CreateSection_UserStory for testing, as per the provided details

    // Verify the visibility of components
    QVERIFY2(parentBoardInstance.getButton_CreateUserStory()->isVisible(), "Button_CreateUserStory is not visible (Failed)");
    QVERIFY2(!parentBoardInstance.getButton_CreateTask()->isVisible(), "Button_CreateTask is still visible (Failed)");

    QVERIFY2(!parentBoardInstance.get_BL_SprintDropDown()->isVisible(), "BL_SprintDropDown is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_SelecteSprint()->isVisible(), "SelecteSprint is still visible (Failed)");

    // Verify properties of the Create_Header label
    QLabel* Create_Header = parentBoardInstance.getCreate_Header();
    QVERIFY2(Create_Header->alignment() == Qt::AlignCenter, "Create_Header alignment is not center (Failed)");
    QVERIFY2(Create_Header->text() == "Create User Story", "Create_Header text is not 'Create User Story' (Failed)");

}

//Ui.Component Visibilty - - - - - - - - - - - - - - - - - - Calendar - - - - - - - - - - - -
void QTUnitTest::Calendar_ShowEventCreation(){

    class parentboard parentBoardInstance;
    pb_calendar_implementation calendarImplementation(&parentBoardInstance);

    // Call the method to test
    calendarImplementation.Calendar_ShowEventCreation();

    // Verify that each component is visible
    QVERIFY2(parentBoardInstance.get_CalendarDescription()->isVisible(), "CalendarDescription is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_CalendarHeading()->isVisible(), "CalendarHeading is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_CalendarTitle()->isVisible(), "CalendarTitle is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_Input_Calendar_Description()->isVisible(), "Input_Calendar_Description is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_Input_Calendar_Title()->isVisible(), "Input_Calendar_Title is not visible (Failed)");
    QVERIFY2(parentBoardInstance.get_Calendar_GroupBox()->isVisible(), "Calendar_GroupBox is not visible (Failed)");


}
void QTUnitTest::Calendar_HideEventCreation(){

    class parentboard parentBoardInstance;
    pb_calendar_implementation calendarImplementation(&parentBoardInstance);

    // Call the method to test
    calendarImplementation.Calendar_HideEventCreation();

    // Verify that each component is invisible
    QVERIFY2(!parentBoardInstance.get_Button_SaveCalendar()->isVisible(), "Button_SaveCalendar is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_CalendarDescription()->isVisible(), "CalendarDescription is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_CalendarHeading()->isVisible(), "CalendarHeading is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_CalendarTitle()->isVisible(), "CalendarTitle is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Input_Calendar_Description()->isVisible(), "Input_Calendar_Description is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Input_Calendar_Title()->isVisible(), "Input_Calendar_Title is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_Calendar_GroupBox()->isVisible(), "Calendar_GroupBox is still visible (Failed)");


}





