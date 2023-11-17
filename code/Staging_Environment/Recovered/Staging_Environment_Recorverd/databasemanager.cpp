#include "databasemanager.h"
#include <QDebug>
#include <QtSql/QSqlError>

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("aws-dbtest.cjqugotdygrg.eu-central-1.rds.amazonaws.com");
    db.setDatabaseName("scrummy");
    db.setUserName("admin");
    db.setPassword("sofproj23");

    if (!db.open()) {
        qDebug() << "Connection Not Established - Database Class:" << db.lastError().text();
    } else {
        qDebug() << "Connection Established - Database Class!";
    }
}
QSqlDatabase DatabaseManager::getDatabase() const {
    return db;
}

DatabaseManager::~DatabaseManager(){
    if (db.isOpen()) {
        db.close();
        qDebug() << "Database connection closed.";
    }
}
