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
        query.prepare("SELECT ProjectName, Description FROM scrummy.Project");

        if (query.exec()) {
            while (query.next()) {
                QString taskName = query.value(0).toString();
                QString description = query.value(1).toString();
                addProject(taskName, description);
            }
        } else {
            qDebug() << "Failed to retrieve data:" << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Database connection not established.";
    }
}

void TeamMember_ProjectsWindow::addProject(const QString& taskName, const QString& description) {
    int row = ui->tm_project_table->rowCount();
    ui->tm_project_table->insertRow(row);

    QTableWidgetItem *nameItem = new QTableWidgetItem(taskName);
    QTableWidgetItem *descriptionItem = new QTableWidgetItem(description);

    ui->tm_project_table->setItem(row, 0, nameItem);
    ui->tm_project_table->setItem(row, 1, descriptionItem);
}


void TeamMember_ProjectsWindow::onProjectNameClicked(QTableWidgetItem *item) {
    if (item && item->column() == 0) { // Check if the clicked item is in the 'Project Name' column
        hide();

        parentboard* parentboardobj = new parentboard;
        parentboardobj->showMaximized();

        ui->~TeamMember_ProjectsWindow();
    }
}
