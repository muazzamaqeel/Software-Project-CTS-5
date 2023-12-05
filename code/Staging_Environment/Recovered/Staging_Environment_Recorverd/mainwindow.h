#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlineedit.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QLineEdit* getInput_Username();
    QLineEdit* getInput_Password();


private:
    Ui::MainWindow *ui;
    QString password;
    QString username;

public slots:
    void openIssueWindow();
    void userEncryptedLogin();

public slots:
    void openRegistrationWindow();

public slots:
    void closeApp();



//temporary - Cosmin
public slots:
    void adminLogin();

public slots:
    void openParentBoard();




private slots:
    void openSettings();


};
#endif // MAINWINDOW_H
