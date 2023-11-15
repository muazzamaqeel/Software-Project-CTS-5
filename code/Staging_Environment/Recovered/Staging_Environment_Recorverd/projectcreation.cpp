#include "projectcreation.h"
#include "ui_projectcreation.h"

ProjectCreation::ProjectCreation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProjectCreation)
{
    ui->setupUi(this);
}

ProjectCreation::~ProjectCreation()
{
    delete ui;
}
