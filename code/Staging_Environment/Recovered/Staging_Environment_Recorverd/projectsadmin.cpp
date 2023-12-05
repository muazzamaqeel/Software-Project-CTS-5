#include "projectsadmin.h"
#include "ui_projectsadmin.h"
#include "mainwindow.h"
#include "projectcreation.h"
#include "databasemanager.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QDebug> // Include qDebug for debugging
#include <QTableView>
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <iostream>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>


ProjectsAdmin::ProjectsAdmin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProjectsAdmin)
{
    ui->setupUi(this);

    // Set the table widget model to the taskModel
    ui->project_table->setColumnCount(2);
    ui->project_table->setHorizontalHeaderLabels({"Task Name", "Description"}); // Set column headers

    QFont font = ui->project_table->font();
    font.setPointSize(12); // Set the point size to 12, you can adjust this value
    ui->project_table->setFont(font);

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

    //SQL Statements to add the project in the project table
    int Adminstrate_idAdmin = 1;

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (dbobj.isOpen()) {
        QSqlQuery query(dbobj);
        query.prepare("INSERT INTO Project (ProjectName, Description, Adminstrate_idAdmin) "
                      "VALUES (:ProjectName, :Description, :Adminstrate_idAdmin)");
        query.bindValue(":ProjectName", taskName);
        query.bindValue(":Description", description);
        query.bindValue(":Adminstrate_idAdmin", Adminstrate_idAdmin); // using hashed password


        if (query.exec()) {
            qDebug() << "Data inserted into User table successfully!";
        } else {
            qDebug() << "Failed to insert data into User table:" << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - Registration class!";

    }



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
        QString projectName = ui->project_table->item(row, 0)->text();

        // SQL Statement to delete the project from the database
        deleteProjectFromDatabase(projectName);

        ui->project_table->removeRow(row);
    }
}

void ProjectsAdmin::deleteProjectFromDatabase(const QString& projectName) {
    // SQL Statement to delete a project from the database
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();
    if (dbobj.isOpen()) {
        QSqlQuery query(dbobj);
        query.prepare("DELETE FROM Project WHERE ProjectName = :ProjectName");
        query.bindValue(":ProjectName", projectName);

        if (query.exec()) {
            qDebug() << "Project deleted successfully!";
        } else {
            qDebug() << "Failed to delete project:" << query.lastError().text();
        }

        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - Registration class!";
    }
}


ProjectsAdmin::~ProjectsAdmin()
{
    delete ui;
}


