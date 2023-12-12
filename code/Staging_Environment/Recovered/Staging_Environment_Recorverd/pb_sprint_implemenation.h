#ifndef PB_SPRINT_IMPLEMENATION_H
#define PB_SPRINT_IMPLEMENATION_H
#include <QWidget>
#include <QStandardItemModel>
#include <QTableWidget> // Include QTableWidget header
#include "parentboard.h"
#include "qdatetimeedit.h"
#include "qgroupbox.h"



class pb_sprint_implemenation: public QObject
{
    Q_OBJECT
public:
    QStandardItemModel *model; // Declare the model pointer
    pb_sprint_implemenation(parentboard* parentBoardInstance);
    void on_createtask_sprint_clicked();
    void on_create_sprint_clicked();
    void addSprintName(const QString& sprintName);
    void addTask(const QString& taskName, const QString& description);
    void on_editsprint_sprint_clicked();
    void editSprint(const QString& oldSprintName, const QString& newSprintName);
    void RetrieveAndDisplayTask();
    void clearTaskTable();
    void TaskSBretrieval();
    void RetrieveAndDisplaySprints();
    void clearSprintTable();
    void SprintRetrieval();
private:
    parentboard* parentBoard;
    QGroupBox* sprintGroupBox;



};


#endif // PB_SPRINT_IMPLEMENATION_H
