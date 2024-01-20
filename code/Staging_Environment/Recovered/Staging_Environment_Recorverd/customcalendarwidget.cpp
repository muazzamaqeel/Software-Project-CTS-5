#include "customcalendarwidget.h"
#include <QTextCharFormat>
CustomCalendarWidget::CustomCalendarWidget(QWidget *parent)
    : QCalendarWidget(parent) {
    // You can initialize default styles or other properties here if needed
}

void CustomCalendarWidget::highlightDate(const QDate &date, const QColor &color) {
    QTextCharFormat fmt;
    fmt.setBackground(color);

    setDateTextFormat(date, fmt);
}
