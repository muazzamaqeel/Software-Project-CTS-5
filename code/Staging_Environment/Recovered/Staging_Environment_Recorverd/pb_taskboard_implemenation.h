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
    int getSelectedSprintId() const;

    QStandardItemModel *model;
    parentboard* parentBoard;
    QVBoxLayout* scrollAreaLayout;
    QStringList formattedDates;

    int selectedSprintId;

    QString startDate;
    QString endDate;

public slots:
    void updateLabels(int index);
    void pb_taskboard_Retrieval();
    void fetchSprintData();
    void generateUnassigned();
    void fetchSprintDates();
    void generateUserTaskTree();

};

#endif // PB_TASKBOARD_IMPLEMENATION_H
