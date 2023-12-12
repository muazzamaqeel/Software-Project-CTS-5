#include "teammember_projectswindow.h"
#include "ui_teammember_projectswindow.h"
#include "databasemanager.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDialog>
#include "parentboard.h"

TeamMember_ProjectsWindow::TeamMember_ProjectsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeamMember_ProjectsWindow) {

    ui->setupUi(this);
    connect(ui->BackButton, SIGNAL(clicked()), this, SLOT(RetrieveAndDisplayUser_Project()));

    // Initialize table columns and headers
    ui->tm_project_table->setColumnCount(2);
    QStringList headers = {"Project Name", "Description"};
    ui->tm_project_table->setHorizontalHeaderLabels(headers);

    // Set the horizontal header to stretch the columns
    QHeaderView *header = ui->tm_project_table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    RetrieveAndDisplayUser_Project();

    connect(ui->tm_project_table, SIGNAL(itemClicked(QTableWidgetItem*)),
            this, SLOT(onProjectNameClicked(QTableWidgetItem*)));
}


TeamMember_ProjectsWindow::~TeamMember_ProjectsWindow() {
    delete ui;
}

void TeamMember_ProjectsWindow::RetrieveAndDisplayUser_Project() {
    Clear_User_Project();
    ProjectRetrieval();
}

void TeamMember_ProjectsWindow::Clear_User_Project() {
    ui->tm_project_table->clearContents();
    ui->tm_project_table->setRowCount(0);
}

void TeamMember_ProjectsWindow::ProjectRetrieval() {
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (dbobj.isOpen()) {
        QSqlQuery query(dbobj);
        // Adjust the query to include the idProject column
        query.prepare("SELECT idProject, ProjectName, Description FROM scrummy.Project");

        if (query.exec()) {
            while (query.next()) {
                int idProject = query.value(0).toInt(); // idProject is now the first column
                QString projectName = query.value(1).toString();
                QString description = query.value(2).toString();
                addProject(projectName, description, idProject);
            }
        } else {
            qDebug() << "Failed to retrieve data:" << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Database connection not established.";
    }
}

void TeamMember_ProjectsWindow::addProject(const QString& projectName, const QString& description, int idProject) {
    int row = ui->tm_project_table->rowCount();
    ui->tm_project_table->insertRow(row);

    QTableWidgetItem *nameItem = new QTableWidgetItem(projectName);
    nameItem->setData(Qt::UserRole, QVariant(idProject)); // Store the idProject

    QTableWidgetItem *descriptionItem = new QTableWidgetItem(description);

    ui->tm_project_table->setItem(row, 0, nameItem);
    ui->tm_project_table->setItem(row, 1, descriptionItem);
}



void TeamMember_ProjectsWindow::onProjectNameClicked(QTableWidgetItem *item) {
    if (item && item->column() == 0) {
        int idProject = item->data(Qt::UserRole).toInt();
        this->deleteLater();
        parentboard* parentboardwindow = parentboard::getInstance();
        parentboardwindow->setProjectId(idProject);
        parentboardwindow->showMaximized();
    }
}
