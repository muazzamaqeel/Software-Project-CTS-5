// pb_taskboard_implemenation.cpp
#include "pb_taskboard_implemenation.h"
#include "parentboard.h"  // Include parentboard header
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QComboBox>
#include <QDebug>
#include <QLabel>
#include <QTreeWidget>
#include <QTreeWidgetItem>

pb_taskboard_implemenation::pb_taskboard_implemenation(parentboard* parentBoardInstance)
    : parentBoard(parentBoardInstance),
    scrollAreaLayout(parentBoardInstance->getScrollAreaLayout())  // Initialize the layout
{
    model = new QStandardItemModel(parentBoard);

    fetchSprintData();
    generateUserTaskTree();


    connect(parentBoard->getSprintDropdown(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &pb_taskboard_implemenation::updateLabels);
}

pb_taskboard_implemenation::~pb_taskboard_implemenation()
{
    delete model;
}

void pb_taskboard_implemenation::fetchSprintData()
{
    parentBoard->getSprintDropdown()->clear();

    DatabaseManager database;
    QSqlDatabase db = database.getDatabase();

    // Passing project ID
    int PassedProjectID = parentBoard->getProjectId();
    qDebug() << "Project ID in Product Backlog: " << PassedProjectID;

    if (db.isOpen()) {
        qDebug() << "Connection Established - Taskboard class!";

        QSqlQuery query(db);
        query.prepare("SELECT idSprint, Title FROM Sprint WHERE Project_idProject = 1"); // value to replace with :projectId
        query.bindValue(":projectId", PassedProjectID);  // Use the stored project ID

        if (query.exec()) {
            while (query.next()) {
                int idSprint = query.value(0).toInt();
                QString title = query.value(1).toString();

                parentBoard->getSprintDropdown()->addItem(title, idSprint);

                qDebug() << "Sprint data fetched successfully!";
            }
        } else {
            qDebug() << "Failed to fetch Sprint data:" << query.lastError().text();
        }

        db.close();
    } else {
        qDebug() << "Connection Not Established - Taskboard class!";
    }
}

void pb_taskboard_implemenation::generateUserTaskTree()
{
    // Clear existing items from the QTreeWidget
    parentBoard->getTaskTreeWidget()->clear();

    // Fetch User and Task data and generate the tree
    DatabaseManager database;
    QSqlDatabase db = database.getDatabase();

    // Passing Project ID and Sprint ID
    int PassedProjectID = parentBoard->getProjectId();
    int selectedSprintId = parentBoard->getSprintDropdown()->currentData().toInt();
    qDebug() << "Project ID in Taskboard: " << PassedProjectID;
    qDebug() << "Selected Sprint ID: " << selectedSprintId;

    if (db.isOpen()) {
        qDebug() << "Connection Established - Taskboard class!";

        QSqlQuery query(db);
        query.prepare("SELECT User.Username, TaskSB.Title, TaskSB.Priority, TaskSB.Status   FROM User "
                      "INNER JOIN TaskSB ON User.idUser = TaskSB.Assignee "
                      "WHERE SprintBacklog_Sprint_Project_idProject = 1 "
                      "AND SprintBacklog_Sprint_idSprint = :sprintId");
        query.bindValue(":projectId", PassedProjectID);
        query.bindValue(":sprintId", selectedSprintId);

        if (query.exec()) {
            while (query.next()) {
                QString userName = query.value(0).toString();
                QString taskTitle = query.value(1).toString();
                QString taskPriority = query.value(2).toString();
                QString taskStatus = query.value(3).toString();
                qDebug() << "userName: " << userName;
                qDebug() << "taskTitle: " << taskTitle;
                qDebug() << "taskPriority: " << taskPriority;
                qDebug() << "taskStatus: " << taskStatus;


                // Find or create userItem in the QTreeWidget
                QTreeWidgetItem* treeUserItem = nullptr;

                // Check if the userItem already exists
                for (int i = 0; i < parentBoard->getTaskTreeWidget()->topLevelItemCount(); ++i) {
                    QTreeWidgetItem* treeItem = parentBoard->getTaskTreeWidget()->topLevelItem(i);
                    if (treeItem->text(0) == userName) {
                        treeUserItem = treeItem;
                        break;
                    }
                }

                // If userItem doesn't exist, create a new one
                if (!treeUserItem) {
                    treeUserItem = new QTreeWidgetItem(parentBoard->getTaskTreeWidget());
                    treeUserItem->setText(0, userName);
                }

                // Add task for the current user
                QTreeWidgetItem* treeTaskItem = new QTreeWidgetItem(treeUserItem);
                treeTaskItem->setText(1, taskTitle);
                treeTaskItem->setText(2, taskPriority);
                treeTaskItem->setText(3, taskStatus);

                qDebug() << "User and task data fetched successfully!";
            }
        } else {
            qDebug() << "Failed to fetch user and task data:" << query.lastError().text();
        }

        db.close();
    } else {
        qDebug() << "Connection Not Established - Taskboard class!";
    }
}


void pb_taskboard_implemenation::updateLabels(int index)
{
    // int selectedIdSprint = parentBoard->getSprintDropdown()->currentData().toInt();

    QComboBox* sprintDropdown = parentBoard->getSprintDropdown();

    // Fetch Sprint ID for User and Task generation
    QVariant selectedData = sprintDropdown->currentData();
    if (selectedData.isValid()) {
        selectedSprintId = selectedData.toInt();
        qDebug() << "Selected Dropdown Sprint ID: " << selectedSprintId;

        // Update the tree widget
        generateUserTaskTree();

    } else {
        qDebug() << "Invalid selected data in the sprint dropdown.";
        selectedSprintId = -1;
    }
}
int pb_taskboard_implemenation::getSelectedSprintId() const
{
    return selectedSprintId;
}
