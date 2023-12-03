#ifndef PARENTBOARD_H
#define PARENTBOARD_H
#include <QWidget>
#include <QStandardItemModel>
#include <QTableWidget> // Include QTableWidget header

namespace Ui {
class parentboard;
}

class parentboard : public QWidget
{
    Q_OBJECT

public:
    explicit parentboard(QWidget *parent = nullptr);
    ~parentboard();
    QWidget* getSomeWidget(); // Declare the function
    QTableWidget* getUserStoriesTableView();
    QTableWidget* getIssuesTableView();
    QTableWidget* getSprintTableView();
private slots:
    void on_taskboardButton_clicked();
    void on_teamButton_clicked();
    void on_backlogButton_clicked();
    void on_sprintsButton_clicked();
    void on_confluenceButton_clicked();
    void goBackToMainWindow();
    void confluence_class();
private:
    Ui::parentboard *ui;
    QStandardItemModel *taskModel;
};

#endif // PARENTBOARD_H
