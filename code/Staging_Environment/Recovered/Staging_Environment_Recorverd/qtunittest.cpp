#include "qtunittest.h"
#include "databasemanager.h"
#include <QtTest/QTest>
#include "mainwindow.h"
//#include "adminstrator.h"
//#include "backlog.h"
//#include "calendar.h"
//#include "confluence.h"
//#include "issuecreation.h"
//#include "launchscreen.h"
//#include "parentboard.h"
//#include "projectcreation.h"
//#include "projectsadmin.h"
//#include "registration_window.h"
//#include "settings.h"
//#include "sprints.h"
//#include "taskboard.h"
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
    QVERIFY2(!mainWindow.isVisible(), "MainWindow should be hidden after opening issue window");

    //Test Credentials
    QLineEdit* InputUsername = mainWindow.getInput_Username();
    QLineEdit* InputPassword = mainWindow.getInput_Password();
    InputUsername->setText("aida");
    InputPassword->setText("aida");
    mainWindow.userEncryptedLogin();
}


//Implementation of the Tests of the adminstrator.cpp
void QTUnitTest::AdminstratorTest(){

}


//Implementation of the Tests of the backlog.cpp
void QTUnitTest::BacklogTest(){

}

//Implementation of the Tests of the calendar.cpp
void QTUnitTest::CalendarTest(){

}

//Implementation of the Tests of the confluence.cpp
void QTUnitTest::ConfluenceTest() {

}

//Implementation of the Tests of the issuecreation.cpp
void QTUnitTest::IssuecreationTest(){

}

//Implementation of the Tests of the launchscreen.cpp
void QTUnitTest::LaunchscreenTest(){

}

//Implementation of the Tests of the parentboard.cpp
void QTUnitTest::Parentboardtest(){

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

}


//Implementation of the Tests of the projectsadmin.cpp
void QTUnitTest::ProjectsadminTest(){

}


//Implementation of the Tests of the registration_window.cpp
void QTUnitTest::Registration_windowTest(){

}

//Implementation of the Tests of the settings.cpp
void QTUnitTest::SettingsTest(){

}


//Implementation of the Tests of the sprints.cpp
void QTUnitTest::SprintsTest(){

}

//Implementation of the Tests of the taskboard.cpp
void QTUnitTest::TaskboardTest(){

}
