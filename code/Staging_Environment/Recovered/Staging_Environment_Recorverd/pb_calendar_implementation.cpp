#include "pb_calendar_implemenation.h"
#include <QPainter>
#include <QCalendarWidget>
#include "customcalendarwidget.h"
#include <QDate>
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QUuid>



pb_calendar_implementation::pb_calendar_implementation(parentboard* parentBoardInstance) {
    parentBoard = parentBoardInstance;
    connect(parentBoard->get_CalendarWidget(), &QCalendarWidget::selectionChanged,
            this, &pb_calendar_implementation::onDateSelected);
    connect(parentBoard->get_CalendarWidget(), &QCalendarWidget::currentPageChanged,
            this, &pb_calendar_implementation::onMonthChanged);



    // In the constructor:
    CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
    int newWidth = 1200;
    calendarWidget->adjustWidth(newWidth);
    if (calendarWidget) {
        connect(calendarWidget, &CustomCalendarWidget::dateDeleted,
                this, &pb_calendar_implementation::onDeleteKeyPressed);
    }
    connect(parentBoard->get_Button_DeleteCalendar(), &QPushButton::clicked,
            this, &pb_calendar_implementation::onDeleteButtonClicked);


    QPushButton* saveButton = parentBoard->get_Button_SaveCalendar();
    QPushButton* deleteButton = parentBoard->get_Button_DeleteCalendar();
    //QPushButton* calendarButton = parentBoard->getcalendarBu
    if (calendarWidget && saveButton && deleteButton) {
        // Assuming you want to increase the width by 100 pixels
        int newWidth = 1200;

        connect(saveButton, &QPushButton::clicked, [calendarWidget, newWidth]() {
            calendarWidget->adjustWidth(newWidth);
        });

        connect(deleteButton, &QPushButton::clicked, [calendarWidget, newWidth]() {
            calendarWidget->adjustWidth(newWidth);
        });

        Calendar_HideEventCreation();
    }
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
    CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
    int newWidth = 1200;
    calendarWidget->adjustWidth(newWidth);
    int year = parentBoard->get_CalendarWidget()->yearShown();
    int month = parentBoard->get_CalendarWidget()->monthShown();

    // Retrieve events for the current month
    onMonthChanged(year, month);}

void pb_calendar_implementation::Calendar_ShowEventCreation(){
    bool visibility = true;
    parentBoard->get_Button_SaveCalendar()->setVisible(visibility);
    parentBoard->get_CalendarDescription()->setVisible(visibility);
    parentBoard->get_CalendarHeading()->setVisible(visibility);
    parentBoard->get_CalendarTitle()->setVisible(visibility);
    parentBoard->get_Input_Calendar_Description()->setVisible(visibility);
    parentBoard->get_Input_Calendar_Title()->setVisible(visibility);
    parentBoard->get_Calendar_GroupBox()->setVisible(visibility);
    CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
    int newWidth = 700;
    calendarWidget->adjustWidth(newWidth);
}

void pb_calendar_implementation::onMonthChanged(int year, int month) {
    QDate startDate(year, month, 1);
    QDate endDate = startDate.addMonths(1).addDays(-1);
    cacheEventsForMonth(startDate, endDate);
}

void pb_calendar_implementation::retrieveEventsForMonth(const QDate &startDate, const QDate &endDate) {
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (!dbobj.open()) {
        qDebug() << "Database connection error!";
        return;
    }

    QSqlQuery query(dbobj);
    query.prepare("SELECT date, eventTitle, eventDescription FROM Calendar "
                  "WHERE date BETWEEN :startDate AND :endDate AND Project_idProject = :Project_idProject");
    query.bindValue(":startDate", startDate.toString("yyyy-MM-dd"));
    query.bindValue(":endDate", endDate.toString("yyyy-MM-dd"));
    query.bindValue(":Project_idProject", parentBoard->getProjectId());

    if (!query.exec()) {
        qDebug() << "Select query error: " << query.lastError().text();
        return;
    }

    CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
    if (calendarWidget) {
        calendarWidget->clearAllHighlights(); // You should implement this method
    }

    while (query.next()) {
        QDate date = query.value(0).toDate();
        QString eventTitle = query.value(1).toString();
        QString eventDescription = query.value(2).toString();
        if (calendarWidget) {
            calendarWidget->highlightDate(date, Qt::lightGray); // Use an appropriate color
        }
    }
}


void pb_calendar_implementation::onDateSelected() {
    QDate date = parentBoard->get_CalendarWidget()->selectedDate();
    Calendar_ShowEventCreation(); // Show event creation UI components

    if (eventsForMonth.contains(date)) {
        // Event exists, retrieve details from the cache
        EventDetails details = eventsForMonth.value(date);
        parentBoard->get_Input_Calendar_Title()->setPlainText(details.title);
        parentBoard->get_Input_Calendar_Description()->setPlainText(details.description);
    } else {
        // No event, clear the UI components
        parentBoard->get_Input_Calendar_Title()->setPlainText("");
        parentBoard->get_Input_Calendar_Description()->setPlainText("");
    }

    // Adjust the calendar widget width if needed
    CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
    if (calendarWidget) {
        int newWidth = 700;
        calendarWidget->adjustWidth(newWidth);
    }
}



bool pb_calendar_implementation::checkEventExists(const QDate &date) {
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();
    if (!dbobj.open()) {
        qDebug() << "Database connection error!";
        return false;
    }
    QSqlQuery query(dbobj);
    query.prepare("SELECT COUNT(*) FROM Calendar "
                  "WHERE date = :date AND Project_idProject = :Project_idProject");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":Project_idProject", parentBoard->getProjectId());
    if (!query.exec()) {
        qDebug() << "Select query error: " << query.lastError().text();
        return false;
    }
    if (query.next() && query.value(0).toInt() > 0) {
        return true;
    }
    return false;
}

void pb_calendar_implementation::clearCellHighlighting(const QDate &date) {
    CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
    if (calendarWidget) {
        // Clear any highlighting for the date
        calendarWidget->clearHighlight(date);
    }
}


void pb_calendar_implementation::retrieveEventDetails(const QDate &date) {
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (!dbobj.open()) {
        // Handle the error, the database connection is not open
        qDebug() << "Database connection error!";
        return;
    }

    QSqlQuery query(dbobj);
    query.prepare("SELECT eventTitle, eventDescription FROM Calendar "
                  "WHERE date = :date AND Project_idProject = :Project_idProject");
    query.bindValue(":date", date.toString("yyyy-MM-dd")); // Assuming the format is YYYY-MM-DD
    query.bindValue(":Project_idProject", parentBoard->getProjectId());

    if (!query.exec()) {
        // Handle the error, the query execution has failed
        qDebug() << "Select query error: " << query.lastError().text();
        return;
    }

    // Assuming there's at most one event per date in the database
    if (query.next()) {
        QString eventTitle = query.value(0).toString();
        QString eventDescription = query.value(1).toString();

        // Set the event details in the UI components
        parentBoard->get_Input_Calendar_Title()->setPlainText(eventTitle);
        parentBoard->get_Input_Calendar_Description()->setPlainText(eventDescription);
    } else {
        // Clear the fields if no event is found
        parentBoard->get_Input_Calendar_Title()->setPlainText("");
        parentBoard->get_Input_Calendar_Description()->setPlainText("");
    }
}


void pb_calendar_implementation::paintCell(const QDate &date) const {
    CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
    if (calendarWidget) {
        calendarWidget->highlightDate(date, Qt::lightGray); // Highlighting a specific date
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


    if(!eventDescription.isEmpty() && !eventTitle.isEmpty()){

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

    }else{
        QMessageBox::warning(parentBoard, "Fields Missing", "Please fill in both the event title and description.");
        return;
    }

    CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
    int newWidth = calendarWidget->width() + 400;
    calendarWidget->adjustWidth(newWidth);
    Calendar_HideEventCreation();

}

void pb_calendar_implementation::onDeleteKeyPressed(const QDate &date) {
    qDebug() << "Attempting to delete event on date:" << date;
    if (!checkEventExists(date)) {
        qDebug() << "No event to delete on this date";
        return; // No event to delete
    }

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (!dbobj.open()) {
        qDebug() << "Database connection error!";
        return;
    }

    QSqlQuery query(dbobj);
    query.prepare("DELETE FROM Calendar WHERE date = :date AND Project_idProject = :Project_idProject");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":Project_idProject", parentBoard->getProjectId());

    if (!query.exec()) {
        qDebug() << "Delete query error: " << query.lastError().text();
    } else {
        qDebug() << "Event successfully deleted from the database.";
        CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
        if (calendarWidget) {
            calendarWidget->clearHighlight(date); // Clear the highlight to reflect the deletion
        }
    }
}

void pb_calendar_implementation::onDeleteButtonClicked() {
    QDate date = parentBoard->get_CalendarWidget()->selectedDate();
    if (!checkEventExists(date)) {
        qDebug() << "No event to delete on this date";
        return; // No event to delete
    }
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (!dbobj.open()) {
        qDebug() << "Database connection error!";
        return;
    }
    QSqlQuery query(dbobj);
    query.prepare("DELETE FROM Calendar WHERE date = :date AND Project_idProject = :Project_idProject");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":Project_idProject", parentBoard->getProjectId());

    if (!query.exec()) {
        qDebug() << "Delete query error: " << query.lastError().text();
    } else {
        qDebug() << "Event successfully deleted from the database.";
        // Update the calendar display
        CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
        if (calendarWidget) {
            calendarWidget->clearHighlight(date);
        }
    }
    Calendar_HideEventCreation();
}


EventDetails pb_calendar_implementation::getEventForDate(const QDate &date) {
    return eventsForMonth.value(date, EventDetails());
}


void pb_calendar_implementation::cacheEventsForMonth(const QDate &startDate, const QDate &endDate) {
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (!dbobj.open()) {
        qDebug() << "Database connection error!";
        return;
    }

    QSqlQuery query(dbobj);
    query.prepare("SELECT date, eventTitle, eventDescription FROM Calendar "
                  "WHERE date BETWEEN :startDate AND :endDate AND Project_idProject = :Project_idProject");
    query.bindValue(":startDate", startDate.toString("yyyy-MM-dd"));
    query.bindValue(":endDate", endDate.toString("yyyy-MM-dd"));
    query.bindValue(":Project_idProject", parentBoard->getProjectId());

    if (!query.exec()) {
        qDebug() << "Select query error: " << query.lastError().text();
        return;
    }

    CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
    if (calendarWidget) {
        calendarWidget->clearAllHighlights(); // Clear existing highlights
    }

    eventsForMonth.clear(); // Clear any existing cached events

    while (query.next()) {
        QDate date = query.value(0).toDate();
        QString eventTitle = query.value(1).toString();
        QString eventDescription = query.value(2).toString();

        // Cache the events
        eventsForMonth[date] = EventDetails(eventTitle, eventDescription);

        // Highlight the date on the calendar
        if (calendarWidget) {
            calendarWidget->highlightDate(date, Qt::lightGray); // Use an appropriate color
        }
    }
}

void pb_calendar_implementation::onSaveButtonClicked() {
    QDate date = parentBoard->get_CalendarWidget()->selectedDate();
    QString eventTitle = parentBoard->get_Input_Calendar_Title()->toPlainText();
    QString eventDescription = parentBoard->get_Input_Calendar_Description()->toPlainText();

    // Check if the event title and description are not empty
    if (eventTitle.isEmpty() || eventDescription.isEmpty()) {
        QMessageBox::warning(parentBoard, "Incomplete Information", "Please provide both a title and a description for the event.");
        return;
    }

    DatabaseManager databaseManager;

    // When you need a database connection:
    QString uniqueConnName = QUuid::createUuid().toString();
    QSqlDatabase db = databaseManager.getDatabase(uniqueConnName);
    // ...perform database operations...

    // When done with the database operations:


    if (!db.open()) {
        qDebug() << "Database connection error!";
        return;
    }

    QSqlQuery query(db);
    // Check if the event already exists for the selected date
    if (checkEventExists(date)) {
        // Update the existing event
        query.prepare("UPDATE Calendar SET eventTitle = :eventTitle, eventDescription = :eventDescription "
                      "WHERE date = :date AND Project_idProject = :Project_idProject");
    } else {
        // Insert a new event
        query.prepare("INSERT INTO Calendar (date, eventTitle, eventDescription, Project_idProject) "
                      "VALUES (:date, :eventTitle, :eventDescription, :Project_idProject)");
    }
    query.bindValue(":date", date.toString("yyyy-MM-dd"));
    query.bindValue(":eventTitle", eventTitle);
    query.bindValue(":eventDescription", eventDescription);
    query.bindValue(":Project_idProject", parentBoard->getProjectId());

    if (!query.exec()) {
        qDebug() << "Database query error: " << query.lastError().text();
        QMessageBox::critical(parentBoard, "Database Error", "Failed to save the event details.");
    } else {
        qDebug() << "Event details successfully saved.";
        QMessageBox::information(parentBoard, "Success", "The event details have been saved successfully.");

        // Update the calendar view
        CustomCalendarWidget* calendarWidget = dynamic_cast<CustomCalendarWidget*>(parentBoard->get_CalendarWidget());
        if (calendarWidget) {
            QColor highlightColor = Qt::lightGray; // Choose an appropriate color
            calendarWidget->highlightDate(date, highlightColor);
            // Update the local cache if you are using one
            eventsForMonth[date] = EventDetails(eventTitle, eventDescription);
        }
    }
    databaseManager.closeConnection(uniqueConnName);

}
