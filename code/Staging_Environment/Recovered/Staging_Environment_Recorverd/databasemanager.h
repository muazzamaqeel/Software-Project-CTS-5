#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QSqlDatabase>
#include <QString>

class DatabaseManager
{

private:
    QSqlDatabase db;

public:

    DatabaseManager(const QString& hostName, const QString& dbName, const QString& userName, const QString& password);
    QSqlDatabase getDatabase() const;
};

#endif // DATABASEMANAGER_H
