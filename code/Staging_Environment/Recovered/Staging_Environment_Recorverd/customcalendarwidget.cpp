#include "customcalendarwidget.h"
#include <QTextCharFormat>
#include <QKeyEvent> // Correct this line

CustomCalendarWidget::CustomCalendarWidget(QWidget *parent) : QCalendarWidget(parent) {
    setFocusPolicy(Qt::StrongFocus);
}

void CustomCalendarWidget::highlightDate(const QDate &date, const QColor &color) {
    QTextCharFormat fmt;
    fmt.setBackground(color);

    setDateTextFormat(date, fmt);
}

void CustomCalendarWidget::clearHighlight(const QDate &date) {
    QTextCharFormat defaultFormat;
    setDateTextFormat(date, defaultFormat); // Reset to default format
}

void CustomCalendarWidget::clearAllHighlights() {
    // Clear highlights for all dates
    QTextCharFormat defaultFormat;
    this->setDateTextFormat(QDate(), defaultFormat); // Passing a null date clears all dates
}
void CustomCalendarWidget::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Key pressed in calendar widget";
    if (event->key() == Qt::Key_Delete) {
        emit dateDeleted(this->selectedDate()); // You should declare this signal
    } else {
        QCalendarWidget::keyPressEvent(event); // Call the base class method for other key events
    }
}


void CustomCalendarWidget::adjustWidth(int newWidth) {
    setFixedWidth(newWidth);
}
