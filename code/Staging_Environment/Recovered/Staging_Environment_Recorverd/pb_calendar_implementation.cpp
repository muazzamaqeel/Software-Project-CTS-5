#include "pb_calendar_implemenation.h"
#include <QPainter>
#include <QCalendarWidget>
#include "customcalendarwidget.h"
#include <QDate>
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>

pb_calendar_implementation::pb_calendar_implementation(parentboard* parentBoardInstance) {
    parentBoard = parentBoardInstance;
    connect(parentBoard->get_CalendarWidget(), &QCalendarWidget::selectionChanged,
            this, &pb_calendar_implementation::onDateSelected);


}

void pb_calendar_implementation::Calendar_HideEventCreation(){
    bool visibility = false;
    parentBoard->get_Button_SaveCalendar()->setVisible(visibility);
    parentBoard->get_CalendarDescription()->setVisible(visibility);
    parentBoard->get_CalendarHeading()->setVisible(visibility);
    parentBoard->get_CalendarTitle()->setVisible(visibility);
    parentBoard->get_Input_Calendar_Description()->setVisible(visibility);
    parentBoard->get_Input_Calendar_Title()->setVisible(visibility);
    parentBoard->get_Calendar_GroupBox()->setVisible(visibility);
}

void pb_calendar_implementation::Calendar_ShowEventCreation(){
    bool visibility = true;
    parentBoard->get_Button_SaveCalendar()->setVisible(visibility);
    parentBoard->get_CalendarDescription()->setVisible(visibility);
    parentBoard->get_CalendarHeading()->setVisible(visibility);
    parentBoard->get_CalendarTitle()->setVisible(visibility);
    parentBoard->get_Input_Calendar_Description()->setVisible(visibility);
    parentBoard->get_Input_Calendar_Title()->setVisible(visibility);
    parentBoard->get_Calendar_GroupBox()->setVisible(visibility);
}

void pb_calendar_implementation::onDateSelected() {
    selectedDate = parentBoard->get_CalendarWidget()->selectedDate();
    Calendar_ShowEventCreation();
}


void pb_calendar_implementation::paintCell(const QDate &date) const {
    CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
    if (calendarWidget) {
        calendarWidget->highlightDate(date, Qt::blue); // Highlighting a specific date
    }
}

void pb_calendar_implementation::onCreateTaskClicked() {
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (!dbobj.open()) {
        // Handle the error, the database connection is not open
        qDebug() << "Database connection error!";
        return;
    }

    int passedProjectID = parentBoard->getProjectId();
    QString eventDescription = parentBoard->get_Input_Calendar_Description()->toPlainText();
    QString eventTitle = parentBoard->get_Input_Calendar_Title()->toPlainText();

    QSqlQuery query(dbobj);
    query.prepare("INSERT INTO Calendar (date, eventTitle, eventDescription, Project_idProject) "
                  "VALUES (:date, :eventTitle, :eventDescription, :Project_idProject)");
    query.bindValue(":date", selectedDate.toString("yyyy-MM-dd")); // Assuming the format is YYYY-MM-DD
    query.bindValue(":eventTitle", eventTitle);
    query.bindValue(":eventDescription", eventDescription);
    query.bindValue(":Project_idProject", passedProjectID);

    if (!query.exec()) {
        // Handle the error, the query execution has failed
        qDebug() << "Insert query error: " << query.lastError().text();
    } else {
        qDebug() << "Event successfully inserted into the database.";
        // Optionally, refresh the calendar or perform any other necessary updates
    }

    // Highlight the date to indicate an event has been added
    paintCell(selectedDate);
}


