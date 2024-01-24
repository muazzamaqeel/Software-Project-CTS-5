#ifndef PARENTBOARD_H
#define PARENTBOARD_H

#include <QWidget>

namespace Ui {
class parentboard;
}

class parentboard : public QWidget
{
    Q_OBJECT
public slots:
    void goBackToMainWindow();

//public slots:
//    void openSettings();

//public slots:
//    void goBackToParentBoard();

public:
    explicit parentboard(QWidget *parent = nullptr);
    ~parentboard();

private slots:
    void on_taskboardButton_clicked();

    void on_backlogButton_clicked();

    void on_sprintsButton_clicked();

    void on_confluenceButton_clicked();

private:
    Ui::parentboard *ui;
};

#endif // PARENTBOARD_H

//Cosmin
