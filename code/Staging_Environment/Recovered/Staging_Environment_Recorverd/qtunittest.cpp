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
//#include "pb_productbacklog_implementation.h"
//#include "pb_sprint_implemenation.h"
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
             "CreationBox_Confluence should be hidden after HideCreationSection call");
    QVERIFY2(!parentBoardInstance.get_InputTitle_2()->isVisible(),
             "get_InputTitle_2 is still visible (Failed)");
    QVERIFY2(!parentBoardInstance.get_InputGroup_Confluence_Heading()->isVisible(),
             "get_InputGroup_Confluence_Heading should be hidden after HideCreationSection call");

}


//Ui.Component Visibilty - - - - - - - - - - - - - - - - - - Sprint - - - - - - - - - - - -
void QTUnitTest::PB_Sprint_OBJECTS_VISIBLE_BOXES(){

}


void QTUnitTest::PB_Sprint_OBJECTS_VISIBLE_on_create_sprint_clicked(){

}


void QTUnitTest::PB_Sprint_OBJECTS_VISIBLE_Additional_Details(){


}

//Ui.Component Visibilty - - - - - - - - - - - - - - - - - - Backlog - - - - - - - - - - - -
void QTUnitTest::Show_CreateSection_UserStory(){


}
void QTUnitTest::Hide_CreateSection(){


}
void QTUnitTest::Show_CreateSection(){


}

//Ui.Component Visibilty - - - - - - - - - - - - - - - - - - Calendar - - - - - - - - - - - -
void QTUnitTest::Calendar_ShowEventCreation(){

}
void QTUnitTest::Calendar_HideEventCreation(){

}





