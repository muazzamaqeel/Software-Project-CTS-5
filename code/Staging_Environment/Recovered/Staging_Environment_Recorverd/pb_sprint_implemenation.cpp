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
        query.prepare("SELECT StartDate, EndDate,Title from Sprint");

        if (query.exec()) {
            qDebug() << "Sprint Retrieved Successfully!";

            while (query.next()) {
                // Retrieve each value from the query result
                QString StartDate = query.value(0).toString();
                QString EndDate = query.value(1).toString();
                QString Title = query.value(2).toString();


                // Now use the addBacklog function to add each retrieved row to the table
                addSprint( StartDate, EndDate,Title); // Assuming type is "Task"
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
    QLineEdit* Input_SprintName = parentBoard->get_Input_SprintName();
    QDateEdit* Input_StartDate = parentBoard->get_Input_StartDate();
    QDateEdit* Input_EndDate = parentBoard->get_Input_EndDate();
    int PassedProjectID = parentBoard->getProjectId();

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (!dbobj.isOpen()) {
        qDebug() << "Connection Not Established - pb_productbacklog_implementation!";
        return;
    }

    // Start a transaction
    dbobj.transaction();

    // Insert into Sprint table
    QSqlQuery query(dbobj);
    query.prepare("INSERT INTO Sprint(Title, StartDate, EndDate, Project_idProject) "
                  "VALUES (:title, :StartDate, :EndDate, :Project_idProject)");
    query.bindValue(":title", Input_SprintName->text());
    query.bindValue(":StartDate", Input_StartDate->date());
    query.bindValue(":EndDate", Input_EndDate->date());
    query.bindValue(":Project_idProject", PassedProjectID);

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        dbobj.rollback(); // Rollback transaction on failure
        return;
    }

    // Get the last inserted id for Sprint
    int lastSprintId = query.lastInsertId().toInt();

    // Insert into SprintBacklog table
    query.prepare("INSERT INTO SprintBacklog (idSprintBacklog, Priority, Status, Sprint_idSprint, Sprint_Project_idProject) "
                  "VALUES (:idSprintBacklog, :Priority, :Status, :Sprint_idSprint, :Sprint_Project_idProject)");
    query.bindValue(":idSprintBacklog", lastSprintId);
    query.bindValue(":Priority", "N/A");
    query.bindValue(":Status", Input_SprintName->text());
    query.bindValue(":Sprint_idSprint", lastSprintId);
    query.bindValue(":Sprint_Project_idProject", PassedProjectID);

    if (!query.exec()) {
        qDebug() << "Failed to insert data into SprintBacklog table:" << query.lastError().text();
        dbobj.rollback(); // Rollback transaction on failure
        return;
    }

    // Commit the transaction
    dbobj.commit();
    qDebug() << "Data inserted into Sprint and SprintBacklog tables successfully!";

}


void pb_sprint_implemenation::addSprint(const QString& StartDate, const QString& EndDate,const QString& Title) {
    QTableWidget* sprint_table = parentBoard->getSprintTableView();

    // Adjust the column widths to take up the available space
    QHeaderView* header = sprint_table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);


    if (sprint_table) {
        int IssuerowCount = sprint_table->rowCount(); // Get current row count
        sprint_table->insertRow(IssuerowCount); // Insert a new row at the end
        QTableWidgetItem* SprintstartdateItem = new QTableWidgetItem(StartDate);
        QTableWidgetItem* SprintenddateItem = new QTableWidgetItem(EndDate);
        QTableWidgetItem* SprinttitleItem = new QTableWidgetItem(Title);

        sprint_table->setItem(IssuerowCount, 0, SprintstartdateItem); // Insert taskName in column 0
        sprint_table->setItem(IssuerowCount, 1, SprintenddateItem); // Insert description in column 1
        sprint_table->setItem(IssuerowCount, 2, SprinttitleItem); // Insert description in column 2

    } else {
        qDebug() << "Table view not found or accessible.";
    }
}

void pb_sprint_implemenation::onDeleteButtonClicked() {
    deleteProject();
}


void pb_sprint_implemenation::deleteProject() {
    QTableWidget* sprint_table = parentBoard->getSprintTableView();
    QItemSelectionModel* selectionModel = sprint_table->selectionModel();
    QModelIndexList selectedRows = selectionModel->selectedRows();

    if (selectedRows.isEmpty()) {
        qDebug() << "No rows selected for deletion.";
        return;
    }

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();
    if (!dbobj.isOpen()) {
        qDebug() << "Connection Not Established - pb_productbacklog_implmentation!";
        return;
    }

    QSqlQuery query(dbobj);
    dbobj.transaction();  // Start a transaction to ensure atomicity

    for (const QModelIndex& selectedRow : selectedRows) {
        int row = selectedRow.row();
        int idSprint = sprint_table->item(row, 0)->text().toInt();  // Assuming the first column contains Sprint ID

        // SQL Statement to delete the sprint from the database
        query.prepare("DELETE FROM Sprint WHERE idSprint = :idSprint");
        query.bindValue(":idSprint", idSprint);

        if (!query.exec()) {
            qDebug() << "Error executing delete query: " << query.lastError().text();
            dbobj.rollback();  // Rollback the transaction on error
            return;
        }

        sprint_table->removeRow(row);
    }

    dbobj.commit();  // Commit the transaction if everything is successful
}


//Create-Sprint--------------------------------------------------------------------------------------
void pb_sprint_implemenation::on_create_sprint_clicked() {
    qDebug() << "Create sprint button clicked.";
    sprintGroupBox->setVisible(true);
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
