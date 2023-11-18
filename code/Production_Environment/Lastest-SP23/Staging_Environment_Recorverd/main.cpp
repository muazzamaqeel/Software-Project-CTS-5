#include "mainwindow.h"
//#include "registration_window.h"
#include <QApplication>
#include <QPixmap>
#include "mainwindow.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <iostream>
#include <QtSql/QSqlError>
#include <QtTest/QTest>
//#include "qtunittest.h"
// Remove this line if it's causing issues or make sure the moc file is generated correctly
//#include "testqstring.moc"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow w;
    w.showMaximized();


    // Test Object
    //QTUnitTest testObject;
    //QTest::qExec(&testObject, argc, argv);
    return app.exec();
}
