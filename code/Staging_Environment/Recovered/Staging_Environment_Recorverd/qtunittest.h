#ifndef QTUNITTEST_H
#define QTUNITTEST_H
#include <QtTest/QTest>
#include "parentboard.h"
class QTUnitTest:public QObject
{
public:
    QTUnitTest();
    Q_OBJECT;
    parentboard *parentboard;
//Decleration of the Functions that are in the qtunittest.cpp file
private slots:
    void DatabaseCheck();
    void MainWindowTest();


    void AdminstratorTest();

    void BacklogTest();
    void CalendarTest();
    void ConfluenceTest();
    void IssuecreationTest();
    void LaunchscreenTest();
    void Parentboardtest();
    void ProjectcreationTest();
    void ProjectsadminTest();
    void RegistrationTest();
    void SettingsTest();
    void SprintsTest();
    void TaskboardTest();
    void Teammember_projectswindowTest();
    void Pb_confluence_implementationTest();
    void Pb_productbacklog_implementationTest();
    void Pb_sprint_implemenationTest();
    void Pb_taskboard_implemenationTest();
    void Pb_team_implemenationTest();
    void PB_Confluence_HideCreationSection_Test();


};

#endif // QTUNITTEST_H
