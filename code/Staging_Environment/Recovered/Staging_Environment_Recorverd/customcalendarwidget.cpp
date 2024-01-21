#include "customcalendarwidget.h"
#include <QTextCharFormat>
#include <QKeyEvent>

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
    QTextCharFormat defaultFormat;
    this->setDateTextFormat(QDate(), defaultFormat);
}
void CustomCalendarWidget::keyPressEvent(QKeyEvent *event) {
    qDebug() << "Key pressed in calendar widget";
    if (event->key() == Qt::Key_Delete) {
        emit dateDeleted(this->selectedDate());
    } else {
        QCalendarWidget::keyPressEvent(event);
    }
}


void CustomCalendarWidget::adjustWidth(int newWidth) {
    setFixedWidth(newWidth);
}
