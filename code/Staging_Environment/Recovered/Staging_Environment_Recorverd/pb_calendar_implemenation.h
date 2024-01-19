#ifndef PB_CALENDAR_IMPLEMENATION_H
#define PB_CALENDAR_IMPLEMENATION_H
#include "parentboard.h"
class pb_calendar_implemenation: public QObject
{
    Q_OBJECT
public:
    pb_calendar_implemenation(parentboard* parentBoardInstance);
public slots:
    void Calendar_HideEventCreation();
    void Calendar_ShowEventCreation();

private:
    parentboard* parentBoard; // Reference to the parent board

};

#endif // PB_CALENDAR_IMPLEMENATION_H
