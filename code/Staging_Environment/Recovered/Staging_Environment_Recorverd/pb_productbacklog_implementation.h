#ifndef PB_PRODUCTBACKLOG_IMPLEMENTATION_H
#define PB_PRODUCTBACKLOG_IMPLEMENTATION_H
#include <QWidget>
#include <QStandardItemModel>
#include <QTableWidget> // Include QTableWidget header
#include "databasemanager.h"
#include "parentboard.h"
#include <QSqlRelationalTableModel>
#include <QMap>

struct TaskInfo {
    QString title;
    QString description;
    QString status;
    int assignee;
    int priority;
    int productBacklogID;
    int projectID;
    int taskID;
};

struct UserStoryDetails {
    QString title;
    QString description;
    QString status;
    int priority;
    int assignee;
    int storyID;
};


class pb_productbacklog_implementation: public QObject
{
    Q_OBJECT
    QSqlRelationalTableModel *model_a;

public:
    QMap<int, TaskInfo> taskMap; // Now a member variable

    QStandardItemModel *model; // Declare the model pointer
    pb_productbacklog_implementation(parentboard* parentBoardInstance);
    void addBacklog(const QString& type, const QString& taskName, const QString& description, int priority);
    void addTasks_backlog(const QString& type_pb ,const QString& taskName, const QString& description, int priority);

    // Function for retrieving User Stories from the database
    void UserStoryPBretrieval();

    // Function for adding User Stories to the table
    void UserStories_Added_In_Table(const QString& type_pb, const QString& storyName, const QString& description, const QString& status, int assignee, int priority, int storyID);

    // Function for handling changes to table items
    void onUserStoryTableItemChanged(QTableWidgetItem* item);

    // Function for updating User Stories in the database
    void updateUserStoryInDatabase(int storyID, const QString& title, const QString& description, const QString& status, int priority, int assignee);


public slots:
    void on_createissues_clicked();
    void on_createuserstories_backlog_clicked();
    void TaskPBretrieval();
    void clearUserStoriesTable();
    void RetrieveAndDisplayBacklog();
    void SendTasksToSprints();
    void on_userStoriesItemChanged(QTableWidgetItem* item);
    void Tasks_Added_In_Table(const QString& type_pb, const QString& taskName, const QString& description, const QString& status, int assignee, int priority, int taskID);
    void onTableItemChanged(QTableWidgetItem* item);
    void updateTaskInDatabase(int taskID, const QString& title, const QString& description, const QString& status, int assignee, int priority);

private:
    parentboard* parentBoard;
    QMap<int, UserStoryDetails> storyMap; // Assuming UserStoryDetails is a struct or class you've defined


};

#endif // PB_PRODUCTBACKLOG_IMPLEMENTATION_H
