#include "adminstrator.h"
#include "ui_adminstrator.h"

adminstrator::adminstrator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminstrator)
{
    ui->setupUi(this);

    //connect(ui->adminlogin, SIGNAL(clicked()), this, SLOT(projectsSelection()));
}

//void projectsSelection()
//{
//    hide();
//    Settings* settingWindow = new Settings;
//    settingWindow -> showMaximized();
//    ui->~MainWindow();
//}

adminstrator::~adminstrator()
{
    delete ui;
}
