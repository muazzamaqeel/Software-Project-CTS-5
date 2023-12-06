#ifndef PB_PRODUCTBACKLOG_IMPLEMENTATION_H
#define PB_PRODUCTBACKLOG_IMPLEMENTATION_H
#include <QWidget>
#include <QStandardItemModel>
#include <QTableWidget> // Include QTableWidget header
#include "databasemanager.h"
#include "parentboard.h"


class pb_productbacklog_implementation: public QObject
{
    Q_OBJECT
public:

    QStandardItemModel *model; // Declare the model pointer
    pb_productbacklog_implementation(parentboard* parentBoardInstance);
    void addBacklog(const QString& type, const QString& taskName, const QString& description, int priority);
    void addTasks_backlog(const QString& type_pb ,const QString& taskName, const QString& description, int priority);



public slots:
    void on_createissues_clicked();
    void on_createuserstories_backlog_clicked();
    void UserStoryPBretrieval();
    void TaskPBretrieval();
    void clearUserStoriesTable();
    void RetrieveAndDisplayBacklog();
private:
    parentboard* parentBoard;



};

#endif // PB_PRODUCTBACKLOG_IMPLEMENTATION_H
