#ifndef PB_PRODUCTBACKLOG_IMPLEMENTATION_EXTENSION_H
#define PB_PRODUCTBACKLOG_IMPLEMENTATION_EXTENSION_H
#include <QWidget>
#include <QStandardItemModel>
#include <QTableWidget>
#include "databasemanager.h"
#include "parentboard.h"
#include <QSqlRelationalTableModel>
#include <QMap>
class pb_productbacklog_implementation_Extension
{
public:
    pb_productbacklog_implementation_Extension(parentboard* parentBoardInstance);
    void deleteUserStory(int storyID);
    void Send_UserStory_ToSprint(int taskID, const QString& title, const QString& description, const QString& status, int priority, const QString& assigneeId, const QString& selectedSprint);
    void deleteTaskFromDatabase(int taskID);
private:
    parentboard* parentBoard; // Reference to the parent board

};

#endif // PB_PRODUCTBACKLOG_IMPLEMENTATION_EXTENSION_H
