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



int main(int argc, char *argv[])
{

    /*
    QString dbHostName = "aws-dbtest.cjqugotdygrg.eu-central-1.rds.amazonaws.com";
    QString dbName = "scrummy";
    QString dbUserName = "admin";
    QString dbPassword = "sofproj23";

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(dbHostName);
    db.setDatabaseName(dbName);
    db.setUserName(dbUserName);
    db.setPassword(dbPassword);

    if (db.open()) {
        qDebug() << "Connected to the database!";
        std::cout << "Connected!" << std::endl; // Output "Hello, World!" and a newline

        // Perform database operations here
        // ...
        db.close(); // Close the connection when done
    } else {
        qDebug() << "Failed to connect. Error:" << db.lastError().text();
    }

    */

    QApplication app(argc, argv);
    //Creating an object of MainWindow to access its attributes
    MainWindow w;
    //registration_window rw;
    //rw.showMaximized();
    w.showMaximized();
    return app.exec();
}

