#ifndef ISSUECREATION_H
#define ISSUECREATION_H

#include <QMainWindow>

namespace Ui {
class IssueCreation;
}

class IssueCreation : public QMainWindow
{
    Q_OBJECT

public slots:
    void BackToMain(); // Corrected function name

public:
    explicit IssueCreation(QWidget *parent = nullptr);
    ~IssueCreation();

private:
    Ui::IssueCreation *ui;
};

#endif // ISSUECREATION_H
