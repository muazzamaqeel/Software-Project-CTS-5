#ifndef QTUNITTEST_H
#define QTUNITTEST_H
#include <QtTest/QTest>

class QTUnitTest:public QObject
{
public:
    QTUnitTest();
    Q_OBJECT;

//Decleration of the Functions that are in the qtunittest.cpp file
private slots:
    void DatabaseCheck();
    void MainWindowTest();
    void AdminstratorTest();


};

#endif // QTUNITTEST_H
