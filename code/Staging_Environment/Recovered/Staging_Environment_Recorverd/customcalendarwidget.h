#ifndef CUSTOMCALENDARWIDGET_H
#define CUSTOMCALENDARWIDGET_H

#include <QCalendarWidget>
#include <QKeyEvent>

class CustomCalendarWidget : public QCalendarWidget {
    Q_OBJECT

public:
    explicit CustomCalendarWidget(QWidget *parent = nullptr);
    void highlightDate(const QDate &date, const QColor &color);
    void clearHighlight(const QDate &date);
    void clearAllHighlights();

signals:
    void dateDeleted(const QDate &date); // Declare this signal

protected:
    void keyPressEvent(QKeyEvent *event) override;
public slots:
    void adjustWidth(int newWidth);
};

#endif // CUSTOMCALENDARWIDGET_H
