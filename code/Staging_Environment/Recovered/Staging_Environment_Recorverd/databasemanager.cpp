#include "databasemanager.h"
#include <QDebug>
#include <QtSql/QSqlError>

DatabaseManager::DatabaseManager(const QString& hostName, const QString& dbName, const QString& userName, const QString& password) {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostName);
    db.setDatabaseName(dbName);
    db.setUserName(userName);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "Failed to open database connection:" << db.lastError().text();
    } else {
        qDebug() << "Connected to the database!";
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
