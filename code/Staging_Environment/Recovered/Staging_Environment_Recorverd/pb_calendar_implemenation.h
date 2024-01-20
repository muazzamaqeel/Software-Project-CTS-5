#ifndef PB_CALENDAR_IMPLEMENTATION_H
#define PB_CALENDAR_IMPLEMENTATION_H

#include "parentboard.h"
#include <QDate>

class pb_calendar_implementation : public QObject {
    Q_OBJECT

public:
    explicit pb_calendar_implementation(parentboard* parentBoardInstance);


public slots:
    void Calendar_HideEventCreation();
    void Calendar_ShowEventCreation();
    void onDateSelected();
    void onCreateTaskClicked();
private:
    parentboard* parentBoard; // Reference to the parent board
    void paintCell(const QDate &date) const;
    QDate selectedDate;
};

#endif // PB_CALENDAR_IMPLEMENTATION_H
