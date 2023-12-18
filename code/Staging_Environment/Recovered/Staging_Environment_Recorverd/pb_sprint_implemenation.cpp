#include "pb_sprint_implemenation.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QDebug> // Include qDebug for debugging
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "qboxlayout.h"
#include "qheaderview.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "databasemanager.h"


pb_sprint_implemenation::pb_sprint_implemenation(parentboard* parentBoardInstance)
{
    parentBoard = parentBoardInstance;

    // Initialize the sprintGroupBox member variable
    sprintGroupBox = parentBoard->getSprintGroupBox();  // Assuming you have a function to get the QGroupBox pointer
    sprintGroupBox->setVisible(false);  // Set the initial visibility to false


}
void pb_sprint_implemenation::RetrieveAndDisplayTask() {
    clearTaskTable(); // Clears the table before adding new entries
    TaskSBretrieval(); // Retrieves tasks and adds them to the table

}

void pb_sprint_implemenation::clearTaskTable() {
    QTableWidget* sprint_table = parentBoard->getSprintTableView();
    sprint_table->clearContents();
    sprint_table->setRowCount(0);
}

void pb_sprint_implemenation::TaskSBretrieval() {

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (dbobj.isOpen()) {
        QSqlQuery query(dbobj);
        query.prepare("SELECT Title, Description FROM scrummy.TaskSB");

        if (query.exec()) {
            qDebug() << "Tasks Retrieved Successfully!";

            while (query.next()) {
                // Retrieve each value from the query result
                QString taskName = query.value(0).toString();
                QString description = query.value(1).toString();

                // Now use the addBacklog function to add each retrieved row to the table
                addTask( taskName, description); // Assuming type is "Task"
            }
        } else {
            qDebug() << "Failed to retrieve data: " << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - pb_productbacklog_implementation class! - Task";
    }
}

//Create-Sprint-Task-------------------------------------------------------------------------------
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

    // Adjust the column widths to take up the available space
    QHeaderView* header = sprint_table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);


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

//Create-Sprint--------------------------------------------------------------------------------------
void pb_sprint_implemenation::on_create_sprint_clicked() {

    qDebug() << "Create sprint button clicked.";


    sprintGroupBox->setVisible(true);
   // QString sprintName = QInputDialog::getText(nullptr, "Enter Sprint Name", "Sprint Name:");



}
void pb_sprint_implemenation::addSprintName (const QString& sprintName) {
    QComboBox* sprint_table_combobox = parentBoard->getSprint_Top_Down();
    sprint_table_combobox->addItem(sprintName);
}



//edit-Sprint--------------------------------------------------------------------------------------
void pb_sprint_implemenation::on_editsprint_sprint_clicked() {
    qDebug() << "Edit sprint button clicked.";

    QComboBox* sprint_top_down = parentBoard->getSprint_Top_Down();
    QTextBrowser* date = parentBoard->getSprintDate();

    // Get the selected sprint name from the dropdown
    QString selectedSprintName = sprint_top_down->currentText();
    QTextBrowser *selectedSprintDate = date;

    // Get the new sprint name
    QString newSprintName = QInputDialog::getText(nullptr, "Enter Sprint Name", "Sprint Name:", QLineEdit::Normal, selectedSprintName);

    // Check if the user canceled the input
    if (newSprintName.isEmpty()) {
        qDebug() << "Edit canceled. Sprint Name remains unchanged.";
        return;
    }

    // Get the new date
    QString newDate = QInputDialog::getText(nullptr, "Enter Sprint Date", "Sprint Date:", QLineEdit::Normal, selectedSprintDate->toPlainText());

    // Check if the user canceled the input for the date
    if (newDate.isEmpty()) {
        qDebug() << "Edit canceled. Sprint Date remains unchanged.";
        return;
    }

    // Update the existing sprint's name and date
    editSprint(selectedSprintName, newSprintName);
    selectedSprintDate->setText(newDate);

    qDebug() << "Sprint Name: " << newSprintName;
    qDebug() << "Sprint Date: " << newDate;
}

void pb_sprint_implemenation::editSprint(const QString& oldSprintName, const QString& newSprintName) {
    QComboBox* sprint_top_down = parentBoard->getSprint_Top_Down();
    // Update the dropdown menu with the new sprint name
    int index = sprint_top_down->findText(oldSprintName);
    if (index != -1) {
        sprint_top_down->setItemText(index, newSprintName);
    }

    //---------------------------------------------------------------------





}
