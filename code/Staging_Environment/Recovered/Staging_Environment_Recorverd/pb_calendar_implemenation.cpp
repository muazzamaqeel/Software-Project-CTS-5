#include "pb_calendar_implemenation.h"

pb_calendar_implemenation::pb_calendar_implemenation(parentboard* parentBoardInstance) {
    parentBoard = parentBoardInstance;

}


void pb_calendar_implemenation::Calendar_HideEventCreation(){
    parentBoard->get_Button_SaveCalendar()->setVisible(false);
    parentBoard->get_CalendarDescription()->setVisible(false);
    parentBoard->get_CalendarHeading()->setVisible(false);
    parentBoard->get_CalendarTitle()->setVisible(false);
    parentBoard->get_Input_Calendar_Description()->setVisible(false);
    parentBoard->get_Input_Calendar_Title()->setVisible(false);
    parentBoard->get_Calendar_GroupBox()->setVisible(false);
}

void pb_calendar_implemenation::Calendar_ShowEventCreation(){
    parentBoard->get_Button_SaveCalendar()->setVisible(true);
    parentBoard->get_CalendarDescription()->setVisible(true);
    parentBoard->get_CalendarHeading()->setVisible(true);
    parentBoard->get_CalendarTitle()->setVisible(true);
    parentBoard->get_Input_Calendar_Description()->setVisible(true);
    parentBoard->get_Input_Calendar_Title()->setVisible(true);
    parentBoard->get_Calendar_GroupBox()->setVisible(true);
}
