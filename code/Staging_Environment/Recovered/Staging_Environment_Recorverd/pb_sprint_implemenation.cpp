#include "pb_sprint_implemenation.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QDebug> // Include qDebug for debugging
#include <QTableView>

pb_sprint_implemenation::pb_sprint_implemenation(parentboard* parentBoardInstance)
{
    parentBoard = parentBoardInstance;
}


void pb_sprint_implemenation::on_createtask_sprint_clicked() {
    qDebug() << "Create task sprint button clicked.";

    QString taskName = QInputDialog::getText(nullptr, "Enter Task Name", "Task Name:");
    QString taskDescription = QInputDialog::getText(nullptr, "Enter Task Description", "Task Description:");

    addTask(taskName, taskDescription);

    qDebug() << "Task Name: " << taskName;
    qDebug() << "Task Description: " << taskDescription;
}


void pb_sprint_implemenation::addTask(const QString& taskName, const QString& description) {


    QTableWidget* sprint_table = parentBoard->getSprintTableView();

    if (sprint_table) {
        int IssuerowCount = sprint_table->rowCount(); // Get current row count
        sprint_table->insertRow(IssuerowCount); // Insert a new row at the end

        QTableWidgetItem* SprintnameItem = new QTableWidgetItem(taskName);
        QTableWidgetItem* SprintdescriptionItem = new QTableWidgetItem(description);

        sprint_table->setItem(IssuerowCount, 0, SprintnameItem); // Insert taskName in column 0
        sprint_table->setItem(IssuerowCount, 1, SprintdescriptionItem); // Insert description in column 1
    } else {
        qDebug() << "Table view not found or accessible.";
    }

}
