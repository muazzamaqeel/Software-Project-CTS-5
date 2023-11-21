#include "adminstrator.h"
#include "ui_adminstrator.h"

adminstrator::adminstrator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminstrator)
{
    ui->setupUi(this);
}

adminstrator::~adminstrator()
{
    delete ui;
}
