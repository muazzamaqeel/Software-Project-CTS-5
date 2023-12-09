#include "qtunittest.h"
#include "databasemanager.h"
#include <QtTest/QTest>
#include "mainwindow.h"
//#include "adminstrator.h"



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


//Implementation of the Tests of the Adminstrator.cpp
void QTUnitTest::AdminstratorTest(){

}




