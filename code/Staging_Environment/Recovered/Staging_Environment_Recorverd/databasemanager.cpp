#include "databasemanager.h"
#include <QDebug>
#include <QtSql/QSqlError>
#include <QProcess>
#include <QDateTime>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>

DatabaseManager::DatabaseManager() {
    // Read the configuration file
    QFile configFile("config.json");
    if (configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(configFile.readAll(), &error);

        if (error.error == QJsonParseError::NoError) {
            QJsonObject config = doc.object();
            db = QSqlDatabase::addDatabase("QMYSQL");
            db.setHostName(config["db_hostname"].toString());
            db.setDatabaseName(config["db_name"].toString());
            db.setUserName(config["db_username"].toString());
            db.setPassword(config["db_password"].toString());
        } else {
            qDebug() << "Error parsing JSON config:" << error.errorString();
        }

        configFile.close();
    } else {
        qDebug() << "Failed to open config file:" << configFile.errorString();
    }

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
        qDebug() << "Database connection closed - Database Class.";
    }
}

bool DatabaseManager::createBackup(const QString& backupFilePath) {
    QString program = "C:\\Program Files\\MySQL\\MySQL Server 8.0\\bin\\mysqldump";

    QStringList arguments;
    arguments << "--host=" + db.hostName()
              << "--user=" + db.userName()
              << "--password=" + db.password()
              << db.databaseName();

    QProcess process;
    process.setStandardOutputFile(backupFilePath);

    process.start(program, arguments);
    if (!process.waitForStarted() || !process.waitForFinished()) {
        qDebug() << "Backup failed:" << process.errorString();
        return false;
    }

    qDebug() << "Backup created successfully at:" << backupFilePath;
    return true;
}

