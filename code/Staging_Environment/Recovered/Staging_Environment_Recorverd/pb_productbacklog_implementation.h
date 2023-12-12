#ifndef PB_PRODUCTBACKLOG_IMPLEMENTATION_H
#define PB_PRODUCTBACKLOG_IMPLEMENTATION_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableWidget>
#include "databasemanager.h"
#include "parentboard.h"
#include <QSqlRelationalTableModel>
#include <QMap>

// Struct for holding Task information
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

// Struct for holding User Story details
struct UserStoryDetails {
    QString title;
    QString description;
    QString status;
    int priority;
    int assignee;
    int storyID;
};

// Class for implementing Product Backlog functionality
class pb_productbacklog_implementation: public QObject {
    Q_OBJECT
    QSqlRelationalTableModel *model_a; // Model for SQL relational data

public:
    QMap<int, TaskInfo> taskMap; // Map for storing TaskInfo objects
    QStandardItemModel *model; // Standard item model for data
    DatabaseManager database;

    // Constructor
    pb_productbacklog_implementation(parentboard* parentBoardInstance);

    // Methods for managing tasks and user stories in the backlog
    void UserStoryPBretrieval();
    void UserStories_Added_In_Table(const QString& type_pb, const QString& storyName, const QString& description, const QString& status, int assignee, int priority, int storyID);
    void updateUserStoryInDatabase(int storyID, const QString& title, const QString& description, const QString& status, int priority, int assignee);
    void addTaskToBacklog(const QString& title, const QString& description, const QString& status, int priority, QString assignee);
    void onButtonIssueClicked();
    void Hide_CreateSection();
    void Show_CreateSection();
    void Show_CreateSection_UserStory();
    void Show_CreateSection_Tasks();

public slots:
    // Slot functions for handling UI events and data updates
    void onUserStoryTableItemChanged(QTableWidgetItem* item);
    void addUserStoryToBacklog(const QString& title, const QString& description, const QString& status, int priority, const QString& assignee);
    void on_createUserStory_clicked();
    void TaskPBretrieval();
    void clearUserStoriesTable();
    void RetrieveAndDisplayBacklog();
    void SendTasksToSprints();
    void Tasks_Added_In_Table(const QString& type_pb, const QString& taskName, const QString& description, const QString& status, int assignee, int priority, int taskID);
    void onTableItemChanged(QTableWidgetItem* item);
    void updateTaskInDatabase(int taskID, const QString& title, const QString& description, const QString& status, int assignee, int priority);

private:
    parentboard* parentBoard; // Reference to the parent board
    QMap<int, UserStoryDetails> storyMap; // Map for storing UserStoryDetails objects

    // Function to set up the table for the first time
    void setupTable(QTableWidget* table);

    // Function to insert task into the database
    bool insertTaskIntoDatabase(const QString& title, const QString& description, const QString& status, int priority, const QString& assignee, QSqlDatabase& dbobj);

    // Function to add a row to the table
    void addRowToTable(QTableWidget* table, const QString& title, const QString& description, const QString& status, int priority, const QString& assignee);

};

#endif // PB_PRODUCTBACKLOG_IMPLEMENTATION_H
