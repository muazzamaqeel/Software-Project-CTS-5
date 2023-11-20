#include "parentboard.h"
#include "ui_parentboard.h"
#include "mainwindow.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QDebug> // Include qDebug for debugging
#include <QTableView>

parentboard::parentboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::parentboard)
{
    ui->setupUi(this);

    taskModel = new QStandardItemModel(this);
    taskModel->setColumnCount(2);

    // Set the table widget model to the taskModel
    ui->sprint_table->setColumnCount(2);
    ui->sprint_table->setHorizontalHeaderLabels({"Task Name", "Description"}); // Set column headers

    // Set table for Userstories
    ui->user_stories->setColumnCount(2);
    ui->user_stories->setHorizontalHeaderLabels({"Userstory", "Description"}); // Set column headers

    // Set table for Userstories
    ui->issues->setColumnCount(2);
    ui->issues->setHorizontalHeaderLabels({"Issue", "Description"}); // Set column headers

    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(goBackToMainWindow()));
    connect(ui->create_task_button, SIGNAL(clicked()), this, SLOT(on_createtask_sprint_clicked()));
    connect(ui->button_userstory, SIGNAL(clicked()), this, SLOT(on_createuserstories_backlog_clicked()));
    connect(ui->buttton_issue, SIGNAL(clicked()), this, SLOT(on_createissues_clicked()));

}

parentboard::~parentboard()
{
    delete ui;
}

// Rest of your functions remain unchanged...

// Rest of your functions remain unchanged...



    void parentboard::on_taskboardButton_clicked()
    {
        ui->stackedWidget->setCurrentIndex(0);
        const int numOfRowsToAdd = 3; // Change this number as per your requirement
    }
    
   void parentboard::on_backlogButton_clicked()
    {
      ui->stackedWidget->setCurrentIndex(1);
       const int numOfRowsToAdd = 3; // Change this number as per your requirement
    }

    void parentboard::on_sprintsButton_clicked()
    {
            ui->stackedWidget->setCurrentIndex(2);

        // Example code to add 5 new rows to the table widget
        const int numOfRowsToAdd = 3; // Change this number as per your requirement

    }

    void parentboard::on_createtask_sprint_clicked() {
        qDebug() << "Create task sprint button clicked.";

        QString taskName = QInputDialog::getText(this, "Enter Task Name", "Task Name:");
        QString taskDescription = QInputDialog::getText(this, "Enter Task Description", "Task Description:");

        addTask(taskName, taskDescription);

        qDebug() << "Task Name: " << taskName;
        qDebug() << "Task Description: " << taskDescription;
    }


    void parentboard::addTask(const QString& taskName, const QString& description) {
        int row = ui->sprint_table->rowCount(); // Get the current row count
        ui->sprint_table->insertRow(row); // Insert a new row at the end

        QTableWidgetItem *nameItem = new QTableWidgetItem(taskName);
        QTableWidgetItem *descriptionItem = new QTableWidgetItem(description);

        ui->sprint_table->setItem(row, 0, nameItem); // Set task name in the first column
        ui->sprint_table->setItem(row, 1, descriptionItem); // Set description in the second column
    }


    void parentboard::on_createuserstories_backlog_clicked() {
        qDebug() << "Create task sprint button clicked.";

        QString taskName = QInputDialog::getText(this, "Enter Userstory", "Userstory:");
        QString taskDescription = QInputDialog::getText(this, "Enter Userstory", "Userstory Description:");

        addBacklog(taskName, taskDescription);

        qDebug() << "Userstory: " << taskName;
        qDebug() << "Userstory Description: " << taskDescription;
    }


    void parentboard::addBacklog(const QString& taskName, const QString& description) {
        int row = ui->user_stories->rowCount(); // Get the current row count
        ui->user_stories->insertRow(row); // Insert a new row at the end

        QTableWidgetItem *nameItem = new QTableWidgetItem(taskName);
        QTableWidgetItem *descriptionItem = new QTableWidgetItem(description);

        ui->user_stories->setItem(row, 0, nameItem); // Set task name in the first column
        ui->user_stories->setItem(row, 1, descriptionItem); // Set description in the second column
    }

    void parentboard::on_createissues_clicked() {
        qDebug() << "Create task sprint button clicked.";

        QString taskName = QInputDialog::getText(this, "Enter Issue", "Issue:");
        QString taskDescription = QInputDialog::getText(this, "Enter Issue Description", "Issue Description:");

        addIssues(taskName, taskDescription);

        qDebug() << "Issue: " << taskName;
        qDebug() << "Issue Description: " << taskDescription;
    }


    void parentboard::addIssues(const QString& taskName, const QString& description) {
        int row = ui->issues->rowCount(); // Get the current row count
        ui->issues->insertRow(row); // Insert a new row at the end

        QTableWidgetItem *nameItem = new QTableWidgetItem(taskName);
        QTableWidgetItem *descriptionItem = new QTableWidgetItem(description);

        ui->issues->setItem(row, 0, nameItem); // Set task name in the first column
        ui->issues->setItem(row, 1, descriptionItem); // Set description in the second column
    }

void parentboard::on_confluenceButton_clicked()
{
        ui->stackedWidget->setCurrentIndex(3);
}



void parentboard::goBackToMainWindow() {
        close();
        MainWindow* mainWindow = new MainWindow;
        mainWindow->showMaximized();
}


///Muazzam
///In order to open a window on top of another window
// Sprints *sprintsWindow = new Sprints(this); // Assuming Sprint is a QDialog or QWidget
// Set the sprint window as a modal to block interaction with parentboard window
// sprintsWindow->setWindowModality(Qt::WindowModal);
// Show the sprint window
//sprintsWindow->show();

///Cosmin

// Settings button might not make it to the other windows besides MainWindow
//void parentboard::openSettings()
//{

//        close();
//        Settings* settingWindow = new Settings;
//        settingWindow -> showMaximized();

//}

//void parentboard::goBackToParentBoard()
//{
//        hide(); // Hide the settings window
//        parentboard* parentBoard = new parentboard;
//        parentBoard->showMaximized();
//}

//to be replaced with the Projects window



