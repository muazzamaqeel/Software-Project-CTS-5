#ifndef PB_SPRINT_IMPLEMENATION_H
#define PB_SPRINT_IMPLEMENATION_H
#include <QWidget>
#include <QStandardItemModel>
#include <QTableWidget> // Include QTableWidget header
#include "parentboard.h"



class pb_sprint_implemenation: public QObject
{
    Q_OBJECT
public:
    QStandardItemModel *model; // Declare the model pointer
    pb_sprint_implemenation(parentboard* parentBoardInstance);
    void on_createtask_sprint_clicked();
    void addTask(const QString& taskName, const QString& description);
private:
    parentboard* parentBoard;

};


#endif // PB_SPRINT_IMPLEMENATION_H
