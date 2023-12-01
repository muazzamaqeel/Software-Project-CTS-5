#include "projectsadmin.h"
#include "ui_projectsadmin.h"
#include "mainwindow.h"
#include "projectcreation.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QDebug> // Include qDebug for debugging
#include <QTableView>

ProjectsAdmin::ProjectsAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectsAdmin)
{
    ui->setupUi(this);

    // Set the table widget model to the taskModel
    ui->project_table->setColumnCount(2);
    ui->project_table->setHorizontalHeaderLabels({"Task Name", "Description"}); // Set column headers

    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(openMainWindowfromAdmin()));
    connect(ui->createProjectButton, SIGNAL(clicked()), this, SLOT(openProjectCreation1()));
    connect(ui->delete_project, SIGNAL(clicked()), this, SLOT(deleteProject()));

}

void ProjectsAdmin::openMainWindowfromAdmin()
{
    hide();
    MainWindow* mainWindow = new MainWindow;
    mainWindow->showMaximized();
}

void ProjectsAdmin::openProjectCreation()
{
    hide();
    ProjectCreation* projectCreation = new ProjectCreation;
    projectCreation->showMaximized();
}

void ProjectsAdmin::openProjectCreation1() {
    qDebug() << "Create task sprint button clicked.";

    QString taskName = QInputDialog::getText(this, "Enter Task Name", "Task Name:");
    QString taskDescription = QInputDialog::getText(this, "Enter Task Description", "Task Description:");

    addProject(taskName, taskDescription);

    qDebug() << "Task Name: " << taskName;
    qDebug() << "Task Description: " << taskDescription;
}


void ProjectsAdmin::addProject(const QString& taskName, const QString& description) {
    int row = ui->project_table->rowCount(); // Get the current row count
    ui->project_table->insertRow(row); // Insert a new row at the end

    QTableWidgetItem *nameItem = new QTableWidgetItem(taskName);
    QTableWidgetItem *descriptionItem = new QTableWidgetItem(description);

    ui->project_table->setItem(row, 0, nameItem); // Set task name in the first column
    ui->project_table->setItem(row, 1, descriptionItem); // Set description in the second column
}

void ProjectsAdmin::deleteProject() {
    QItemSelectionModel *selectionModel = ui->project_table->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();

    // Iterate through selected rows in reverse order to avoid issues when removing rows
    for (int i = selectedRows.size() - 1; i >= 0; --i) {
        int row = selectedRows.at(i).row();
        ui->project_table->removeRow(row);
    }
}


ProjectsAdmin::~ProjectsAdmin()
{
    delete ui;
}


