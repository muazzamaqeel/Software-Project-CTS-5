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
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open config file:" << configFile.errorString();
        return;
    }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(configFile.readAll(), &error);
    configFile.close();

    if (error.error != QJsonParseError::NoError) {
        qDebug() << "Error parsing JSON config:" << error.errorString();
        return;
    }

    QJsonObject config = doc.object();
    dbHostname = config["db_hostname"].toString();
    dbName = config["db_name"].toString();
    dbUsername = config["db_username"].toString();
    dbPassword = config["db_password"].toString();
}


QSqlDatabase DatabaseManager::getDatabase() const {
    static QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    if (!db.isOpen()) {
        db.setHostName(dbHostname);
        db.setDatabaseName(dbName);
        db.setUserName(dbUsername);
        db.setPassword(dbPassword);
        if (!db.open()) {
            qDebug() << "Connection Not Established - Default Database:" << db.lastError().text();
        } else {
            qDebug() << "Connection Established - Default Database!";
        }
    }
    return db;
}

QSqlDatabase DatabaseManager::getDatabase(const QString& connectionName) {
    QString connName = connectionName;
    if (connName.isEmpty()) {
        connName = QUuid::createUuid().toString();
    }

    if (QSqlDatabase::contains(connName)) {
        return QSqlDatabase::database(connName);
    } else {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", connName);
        db.setHostName(dbHostname);
        db.setDatabaseName(dbName);
        db.setUserName(dbUsername);
        db.setPassword(dbPassword);

        if (!db.open()) {
            qDebug() << "Connection Not Established - Database Class:" << db.lastError().text();
        } else {
            qDebug() << "Connection Established - Database Class!";
        }
        return db;
    }
}

void DatabaseManager::closeConnection(const QString& connectionName) {
    QSqlDatabase db = QSqlDatabase::database(connectionName);
    if (db.isOpen()) {
        db.close();
    }
    QSqlDatabase::removeDatabase(connectionName);
    qDebug() << "Database connection '" << connectionName << "' closed - Database Class.";
}

DatabaseManager::~DatabaseManager() {
    // Destructor is now empty since we're not managing a persistent connection
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

