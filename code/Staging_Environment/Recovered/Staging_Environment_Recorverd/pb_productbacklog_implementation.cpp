#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QDebug> // Include qDebug for debugging
#include <QTableView>
#include "databasemanager.h"
#include "pb_productbacklog_implementation.h"
#include "qheaderview.h"
#include "qsqlerror.h"
#include "qsqlquery.h"


pb_productbacklog_implementation::pb_productbacklog_implementation(parentboard* parentBoardInstance) {
    // Initialize any necessary variables or connections
    parentBoard = parentBoardInstance;


}

void pb_productbacklog_implementation::RetrieveAndDisplayBacklog() {
    clearUserStoriesTable(); // Clears the table before adding new entries
    TaskPBretrieval(); // Retrieves tasks and adds them to the table
    UserStoryPBretrieval(); // Retrieves user stories and adds them to the table
}


void pb_productbacklog_implementation::clearUserStoriesTable() {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    userStoriesTable->clearContents();
    userStoriesTable->setRowCount(0);
}



//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

void pb_productbacklog_implementation::TaskPBretrieval() {

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (dbobj.isOpen()) {
        QSqlQuery query(dbobj);
        query.prepare("SELECT Title, Description, Priority FROM scrummy.TaskPB");

        if (query.exec()) {
            qDebug() << "Tasks Retrieved Successfully!";

            while (query.next()) {
                // Retrieve each value from the query result
                QString title = query.value(0).toString();
                QString description = query.value(1).toString();
                int priority = query.value(2).toInt();

                // Now use the addBacklog function to add each retrieved row to the table
                addBacklog("Task", title, description, priority); // Assuming type is "Task"
            }
        } else {
            qDebug() << "Failed to retrieve data: " << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - pb_productbacklog_implementation class! - Task";
    }
}


void pb_productbacklog_implementation::UserStoryPBretrieval() {

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (dbobj.isOpen()) {
        QSqlQuery query(dbobj);
        query.prepare("SELECT Title, Description, Priority FROM scrummy.UserStory");

        if (query.exec()) {
            qDebug() << "User Stoires Retrieved Successfully!";

            while (query.next()) {
                // Retrieve each value from the query result
                QString title = query.value(0).toString();
                QString description = query.value(1).toString();
                int priority = query.value(2).toInt();

                // Now use the addBacklog function to add each retrieved row to the table
                addBacklog("UserStory", title, description, priority); // Assuming type is "Task"
            }
        } else {
            qDebug() << "Failed to retrieve data: " << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - pb_productbacklog_implementation class - ! - UserStory";
    }
}
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------








//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------

void pb_productbacklog_implementation::on_createuserstories_backlog_clicked() {
    qDebug() << "Create user story button clicked in the pb class.";

    QString type_pb = "User Story";
    QString UserStoryName = QInputDialog::getText(nullptr, "Enter Userstory", "Userstory:");
    QString UserStoryDescription = QInputDialog::getText(nullptr, "Enter Userstory", "Userstory Description:");
    int priority = QInputDialog::getInt(nullptr, "Enter Priority", "Priority:", 1, 1, 3, 1);

    addBacklog(type_pb, UserStoryName, UserStoryDescription, priority); // Use this-> to refer to member function


    qDebug() << "Userstory: " << UserStoryName;
    qDebug() << "Userstory Description: " << UserStoryDescription;
    qDebug() << "Priority: " << priority;

}

void pb_productbacklog_implementation::addBacklog(const QString& type_pb,const QString& taskName, const QString& description, int priority) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    userStoriesTable->setColumnCount(4); // Ensure there are four columns in the table
    userStoriesTable->setHorizontalHeaderLabels({"Type", "User Story", "Description", "Priority"});

    // Adjust the column widths to take up the available space
    QHeaderView* header = userStoriesTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    if (userStoriesTable) {
        int rowCount = userStoriesTable->rowCount(); // Get current row count
        userStoriesTable->insertRow(rowCount); // Insert a new row at the end

        QTableWidgetItem* type = new QTableWidgetItem(type_pb);
        QTableWidgetItem* itemTaskName = new QTableWidgetItem(taskName);
        QTableWidgetItem* itemDescription = new QTableWidgetItem(description);
        QTableWidgetItem* itemPriority = new QTableWidgetItem(QString::number(priority));

        //Making is non editable
        type->setFlags(type->flags() & ~Qt::ItemIsEditable);

        userStoriesTable->setItem(rowCount, 0, type); // Insert type in column 0
        userStoriesTable->setItem(rowCount, 1, itemTaskName); // Insert taskName in column 1
        userStoriesTable->setItem(rowCount, 2, itemDescription); // Insert description in column 2
        userStoriesTable->setItem(rowCount, 3, itemPriority); // Insert priority in column 3

    } else {
        qDebug() << "Table view not found or accessible.";
    }
}






//------------------------------------------------------------------------------------------------------------------------------


void pb_productbacklog_implementation::on_createissues_clicked(){
    qDebug() << "Create issue button clicked.";

    QString type_pb = "Task";
    QString taskName = QInputDialog::getText(nullptr, "Enter Issue", "Issue:");
    QString taskDescription = QInputDialog::getText(nullptr, "Enter Issue Description", "Issue Description:");
    bool ok;
    int priority = QInputDialog::getInt(nullptr, "Enter Priority", "Priority:", 1, 1, 3, 1);


    addTasks_backlog(type_pb, taskName, taskDescription, priority);
    qDebug() << "Task: " << taskName;
    qDebug() << "Task Description: " << taskDescription;
    qDebug() << "Priority: " << priority;

}

void pb_productbacklog_implementation::addTasks_backlog(const QString& type_pb ,const QString& taskName, const QString& description, int priority) {

    //QTableWidget* IssuesTable = parentBoard->getIssuesTableView();
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    userStoriesTable->setColumnCount(4); // Ensure there are four columns in the table
    userStoriesTable->setHorizontalHeaderLabels({"Type", "User Story", "Description", "Priority"});

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (userStoriesTable) {
        if (dbobj.isOpen()) {
            QSqlQuery query(dbobj);
            query.prepare("INSERT INTO scrummy.TaskPB(Title, Description, Priority, ProductBacklog_idProductBacklog, ProductBacklog_Project_idProject)"
                          "VALUES (:taskName, :description, :priority, 1, 1)");

            query.bindValue(":taskName", taskName);
            query.bindValue(":description", description);
            query.bindValue(":priority", priority);



            if (query.exec()) {
                qDebug() << "Data inserted into TaskPB table successfully!";
            } else {
                qDebug() << "Failed to insert data into TaskPB table:" << query.lastError().text();
            }
            dbobj.close();
        } else {
            qDebug() << "Connection Not Established - pb_productbacklog_implmentation!";

        }






        int IssuerowCount = userStoriesTable->rowCount(); // Get current row count
        userStoriesTable->insertRow(IssuerowCount); // Insert a new row at the end

        QTableWidgetItem* type = new QTableWidgetItem(type_pb);
        QTableWidgetItem* issueTaskName = new QTableWidgetItem(taskName);
        QTableWidgetItem* issueDescription = new QTableWidgetItem(description);
        QTableWidgetItem* issuePriority = new QTableWidgetItem(QString::number(priority));

        //Making is non editable
        type->setFlags(type->flags() & ~Qt::ItemIsEditable);

        userStoriesTable->setItem(IssuerowCount, 0, type); // Insert type in column 0
        userStoriesTable->setItem(IssuerowCount, 1, issueTaskName); // Insert taskName in column 0
        userStoriesTable->setItem(IssuerowCount, 2, issueDescription); // Insert description in column 1
        userStoriesTable->setItem(IssuerowCount, 3, issuePriority); // Insert priority in column 2


    } else {
        qDebug() << "Table view not found or accessible.";
    }
}

//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
