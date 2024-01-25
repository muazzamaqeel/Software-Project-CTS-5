#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QSqlDatabase>
#include <QString>

class DatabaseManager
{

private:
    QSqlDatabase db;

public:

    DatabaseManager();
    QSqlDatabase getDatabase() const;

    ~DatabaseManager();
};

#endif // DATABASEMANAGER_H
