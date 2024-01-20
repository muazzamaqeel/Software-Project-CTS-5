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
    void retrieveEventDetails(const QDate &date);
    bool checkEventExists(const QDate &date);
    void clearCellHighlighting(const QDate &date);
    void onMonthChanged(int year, int month);
    void retrieveEventsForMonth(const QDate &startDate, const QDate &endDate);
    void onDeleteKeyPressed(const QDate &date);
    void onDeleteButtonClicked();
private:
    parentboard* parentBoard; // Reference to the parent board
    void paintCell(const QDate &date) const;
    QDate selectedDate;
};

#endif // PB_CALENDAR_IMPLEMENTATION_H
