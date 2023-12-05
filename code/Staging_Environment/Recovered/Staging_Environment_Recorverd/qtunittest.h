#ifndef QTUNITTEST_H
#define QTUNITTEST_H
#include <QtTest/QTest>

class QTUnitTest:public QObject
{
public:
    QTUnitTest();
    Q_OBJECT;
private slots:
    void DatabaseCheck();
    void MainWindowTest();

};

#endif // QTUNITTEST_H
