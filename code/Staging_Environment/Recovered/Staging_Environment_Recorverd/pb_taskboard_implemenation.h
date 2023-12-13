// pb_taskboard_implemenation.h
#ifndef PB_TASKBOARD_IMPLEMENATION_H
#define PB_TASKBOARD_IMPLEMENATION_H

#include <QObject>
#include <QStandardItemModel>
#include <QTreeWidget>
#include "parentboard.h"  // Include parentboard header

class pb_taskboard_implemenation : public QObject
{
    Q_OBJECT

public:
    explicit pb_taskboard_implemenation(parentboard* parentBoardInstance);
    ~pb_taskboard_implemenation();

private slots:
    void updateLabels(int index);

private:
    void fetchSprintData();
    void generateUserTaskTree();
    int getSelectedSprintId() const;

    QStandardItemModel *model;
    parentboard* parentBoard;
    QVBoxLayout* scrollAreaLayout;  // New member variable

    int selectedSprintId;
};

#endif // PB_TASKBOARD_IMPLEMENATION_H
