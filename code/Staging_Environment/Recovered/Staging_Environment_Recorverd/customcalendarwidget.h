#ifndef CUSTOMCALENDARWIDGET_H
#define CUSTOMCALENDARWIDGET_H

#include <QCalendarWidget>

class CustomCalendarWidget : public QCalendarWidget {
    Q_OBJECT

public:
    explicit CustomCalendarWidget(QWidget *parent = nullptr);
    void highlightDate(const QDate &date, const QColor &color);
};

#endif // CUSTOMCALENDARWIDGET_H
