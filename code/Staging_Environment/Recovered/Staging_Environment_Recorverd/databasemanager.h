#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QSqlDatabase>
#include <QString>

class DatabaseManager
{

private:
    QSqlDatabase db;
    QString dbHostname;
    QString dbName;
    QString dbUsername;
    QString dbPassword;

public:

    DatabaseManager();
    QSqlDatabase getDatabase() const;
    bool createBackup(const QString& backupFilePath);
    ~DatabaseManager();
    void closeConnection(const QString& connectionName);
    QSqlDatabase getDatabase(const QString& connectionName);
};

#endif // DATABASEMANAGER_H
