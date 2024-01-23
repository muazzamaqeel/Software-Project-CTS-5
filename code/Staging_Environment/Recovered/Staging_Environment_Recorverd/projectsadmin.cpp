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
    ui->project_table->setColumnCount(3);
    ui->project_table->setHorizontalHeaderLabels({"Project Name", "Project Description", "Project id"}); // Set column headers

    QFont font = ui->project_table->font();
    font.setPointSize(12); // Set the point size to 12, you can adjust this value
    ui->project_table->setFont(font);

    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(openMainWindowfromAdmin()));
    connect(ui->createProjectButton, SIGNAL(clicked()), this, SLOT(openProjectCreation1()));
    connect(ui->delete_project, SIGNAL(clicked()), this, SLOT(deleteProject()));
    RetrieveAndDisplayProjectBacklog();
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

    QString projectName = QInputDialog::getText(this, "Enter Project Name", "Project Name:");
    QString projectDescription = QInputDialog::getText(this, "Enter Project Description", "Project Description:");

    addProjectToDatabase(projectName, projectDescription);
    RetrieveAndDisplayProjectBacklog();
    qDebug() << "Project Name: " << projectName;
    qDebug() << "Project Description: " << projectDescription;
}





//--------------------------------------------------------------------------------------------------------------
void ProjectsAdmin::RetrieveAndDisplayProjectBacklog() {
    qDebug() << "Entered the Project-Admin class";

    clearProjectTable(); // Clears the table before adding new entries
    ProjectRetrieval(); // Retrieves tasks and adds them to the table
}


void ProjectsAdmin::clearProjectTable() {
    ui->project_table ->clearContents();
    ui->project_table->setRowCount(0);
}


void ProjectsAdmin:: ProjectRetrieval(){
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (dbobj.isOpen()) {
        QSqlQuery query(dbobj);
        query.prepare("SELECT ProjectName, Description, idProject FROM scrummy.Project");

        if (query.exec()) {
            qDebug() << "Project Retrieved Successfully!";

            while (query.next()) {
                qDebug() << "This is the current project ID:" << query.value(2).toInt();
                // Retrieve each value from the query result
                QString projectName = query.value(0).toString();
                QString description = query.value(1).toString();
                int projectId = query.value(2).toInt();


                 qDebug() << "Project Name:" << projectName << ", Description:" << description;

                // Now use the addBacklog function to add each retrieved row to the table
                addProject( projectName, description, projectId);
            }
        } else {
            qDebug() << "Failed to retrieve data: " << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - pb_productbacklog_implementation class! - Task";
    }
}
//-----------------------------------------------------------------------------------------------------------






void ProjectsAdmin::addProject(const QString& taskName, const QString& description, const int projectId) {

    // Adjust the column widths to take up the available space
    QHeaderView* header = ui->project_table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    //SQL Statements to add the project in the project table

    int row = ui->project_table->rowCount(); // Get the current row count
    ui->project_table->insertRow(row); // Insert a new row at the end

    QString idString = QString::number(projectId);
    QTableWidgetItem *nameItem = new QTableWidgetItem(taskName);
    QTableWidgetItem *descriptionItem = new QTableWidgetItem(description);
    QTableWidgetItem *projectIdItem = new QTableWidgetItem(idString);

    qDebug() << "This is the project id item:" << projectIdItem->text();
    ui->project_table->setItem(row, 0, nameItem); // Set task name in the first column
    ui->project_table->setItem(row, 1, descriptionItem); // Set description in the second column
    ui->project_table->setItem(row, 2, projectIdItem);
}

void ProjectsAdmin::deleteProject() {
    QItemSelectionModel *selectionModel = ui->project_table->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();

    // Iterate through selected rows in reverse order to avoid issues when removing rows
    for (int i = selectedRows.size() - 1; i >= 0; --i) {
        int row = selectedRows.at(i).row();
        int projectId = ui->project_table->item(row, 2)->text().toInt();

        // SQL Statement to delete the project from the database
        deleteProjectFromDatabase(projectId);

        ui->project_table->removeRow(row);
    }
}






//--------------------------------------------------------------------------------------------------------
void ProjectsAdmin::addProjectToDatabase(const QString& taskName, const QString& description) {
    int Adminstrate_idAdmin = 1;  // Modify this based on your requirements

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (dbobj.isOpen()) {
        // Start a transaction
        dbobj.transaction();

        // Insert into Project table
        QSqlQuery query(dbobj);
        query.prepare("INSERT INTO Project (ProjectName, Description, Adminstrate_idAdmin) "
                      "VALUES (:ProjectName, :Description, :Adminstrate_idAdmin)");
        query.bindValue(":ProjectName", taskName);
        query.bindValue(":Description", description);
        query.bindValue(":Adminstrate_idAdmin", Adminstrate_idAdmin);

        if (!query.exec()) {
            qDebug() << "Failed to insert data into Project table:" << query.lastError().text();
            dbobj.rollback(); // Rollback transaction on failure
            return;
        }

        // Get the last inserted id
        int lastId = query.lastInsertId().toInt();

        // Insert into ProductBacklog table
        query.prepare("INSERT INTO ProductBacklog (idProductBacklog, Name, Project_idProject) "
                      "VALUES (:idProductBacklog, :Name, :Project_idProject)");
        query.bindValue(":idProductBacklog", lastId);
        query.bindValue(":Name", taskName);
        query.bindValue(":Project_idProject", lastId);

        if (!query.exec()) {
            qDebug() << "Failed to insert data into ProductBacklog table:" << query.lastError().text();
            dbobj.rollback(); // Rollback transaction on failure
            return;
        }

        // Commit the transaction
        dbobj.commit();
        qDebug() << "Data inserted into Project and ProductBacklog tables successfully!";
    } else {
        qDebug() << "Connection Not Established - ProjectAdmin class!";
    }
}


void ProjectsAdmin::deleteProjectFromDatabase(const int& projectId) {
    // SQL Statement to delete a project from the database
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();
    if (dbobj.isOpen()) {
        QSqlQuery query(dbobj);
        query.prepare("DELETE FROM Project WHERE idProject = :ProjectId");
        query.bindValue(":ProjectId", projectId);

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


