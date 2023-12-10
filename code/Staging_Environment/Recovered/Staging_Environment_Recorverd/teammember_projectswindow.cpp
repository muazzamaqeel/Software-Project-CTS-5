#include "teammember_projectswindow.h"
#include "ui_teammember_projectswindow.h"

TeamMember_ProjectsWindow::TeamMember_ProjectsWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TeamMember_ProjectsWindow)
{
    ui->setupUi(this);
}

TeamMember_ProjectsWindow::~TeamMember_ProjectsWindow()
{
    delete ui;
}
