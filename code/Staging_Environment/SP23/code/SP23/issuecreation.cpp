#include "issuecreation.h"
#include "ui_issuecreation.h"
#include "mainwindow.h"
#include <QDebug>

IssueCreation::IssueCreation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IssueCreation)
{
    ui->setupUi(this);
}

IssueCreation::~IssueCreation()
{
    delete ui;
}

void IssueCreation::BackToMain()
{
    hide();
    MainWindow* mainWindow = new MainWindow;
    mainWindow->showMaximized();
    IssueCreation::~IssueCreation();
}
