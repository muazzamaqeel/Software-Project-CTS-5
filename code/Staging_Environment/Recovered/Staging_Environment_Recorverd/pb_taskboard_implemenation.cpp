// pb_taskboard_implemenation.cpp
#include "pb_taskboard_implemenation.h"
#include "QtWidgets/qheaderview.h"
#include "parentboard.h"  // Include parentboard header
#include "databasemanager.h"
#include "ui_parentboard.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QComboBox>
#include <QDebug>
#include <QLabel>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDateTime>
#include <QMessageBox>

/// This class only handles data in the TaskSB and USerStorySB tables!

pb_taskboard_implemenation::pb_taskboard_implemenation(parentboard* parentBoardInstance)
    : parentBoard(parentBoardInstance),
    scrollAreaLayout(parentBoardInstance->getScrollAreaLayout())  // Initialize the layout
{
    model = new QStandardItemModel(parentBoard);

    // fetchSprintData();
    // fetchSprintDates();
    // generateUserTaskTree();
    // HideShow_CreateSectionTaskboard();
    pb_taskboard_Retrieval();

    // Resize QWidgetTree sections/columns
    QHeaderView* header = parentBoard->getTaskTreeWidget()->header();
    // header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    // header->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    // Priority Dropdown
    parentBoard->getInputPriorityT()->clear();
    parentBoard->getInputPriorityT()->addItem("Select Priority", -1);
    parentBoard->getInputPriorityT()->addItem("High", 1);
    parentBoard->getInputPriorityT()->addItem("Medium", 2);
    parentBoard->getInputPriorityT()->addItem("Low", 3);

    // Fixed
    header->setSectionResizeMode(QHeaderView::Fixed);
    header->resizeSection(0, 300); // User section wider
    header->resizeSection(1, 600); // Task section wider

    connect(parentBoard->getTaskTreeWidget(), &QTreeWidget::itemDoubleClicked, this, &pb_taskboard_implemenation::retrieveDataTaskboard);
    connect(parentBoard->getSprintDropdown(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &pb_taskboard_implemenation::updateLabels);    
 }
void pb_taskboard_implemenation::pb_taskboard_Retrieval()
{
    fetchSprintData();
    fetchSprintDates();
    generateUserTaskTree();
    HideShow_CreateSectionTaskboard();
}
void pb_taskboard_implemenation::showCreate_Taskboard()
{
    // hideShowT_Creation = true;
    // HideShow_CreateSectionTaskboard(hideShowT_Creation);
}

pb_taskboard_implemenation::~pb_taskboard_implemenation()
{
    delete model;
}

void pb_taskboard_implemenation::fetchSprintData()
{
    parentBoard->getSprintDropdown()->clear();
    parentBoard->get_BL_SprintDropDownT()->clear();

    parentBoard->get_BL_SprintDropDownT()->addItem("Select Sprint", -1);

    parentBoard->getSprintDropdown()->addItem("All Sprints", -1);

    DatabaseManager database;
    QSqlDatabase db = database.getDatabase();

    // Passing project ID
    int PassedProjectID = parentBoard->getProjectId();
    qDebug() << "TASKBOARD: Project ID in Taskboard fetchSprint: " << PassedProjectID;

    if (db.isOpen()) {
        // qDebug() << "TASKBOARD: Connection Established - Taskboard class!";

        QSqlQuery query(db);
        query.prepare("SELECT "
                      "   idSprint, Title "
                      "FROM"
                      "   Sprint "
                      "WHERE Project_idProject = :projectId"); // value to replace with :projectId
        query.bindValue(":projectId", PassedProjectID);  // Use the stored project ID

        if (query.exec()) {
            while (query.next()) {
                int idSprint = query.value(0).toInt();
                QString title = query.value(1).toString();

                parentBoard->getSprintDropdown()->addItem(title, QVariant(idSprint));
                parentBoard->get_BL_SprintDropDownT()->addItem(title, QVariant(idSprint));
                qDebug() << "TASKBOARD: QUERY SPRINT idSprint" << idSprint;

                qDebug() << "TASKBOARD: Sprint data fetched successfully!";
            }
        } else {
            // qDebug() << "TASKBOARD: Failed to fetch Sprint data:" << query.lastError().text();
        }

        db.close();
    } else {
        // qDebug() << "TASKBOARD: Connection Not Established - Taskboard class!";
    }
}

void pb_taskboard_implemenation::generateUserTaskTree()
{
    // Clear existing items from the QTreeWidget
    parentBoard->getTaskTreeWidget()->clear();
    parentBoard->getInputAssigneeT()->clear();

    QSet<int> addedUserIds;  // Use a set to track added user IDs

    parentBoard->getInputAssigneeT()->addItem("Unassigned", -1);

    // Fetch User and Task data and generate the tree
    DatabaseManager database;
    QSqlDatabase db = database.getDatabase();

    // Passing Project ID and Sprint ID
    int PassedProjectID = parentBoard->getProjectId();
    int selectedSprintId = parentBoard->getSprintDropdown()->currentData().toInt();
    qDebug() << "TASKBOARD: Project ID in Taskboard generateUserTasks: " << PassedProjectID;
    // qDebug() << "TASKBOARD: Selected Sprint ID: " << selectedSprintId;

    {
        DatabaseManager database;
        QSqlDatabase db = database.getDatabase();

        if (db.isOpen()) {
            // qDebug() << "TASKBOARD: Connection Established - Taskboard class!";

            QSqlQuery query(db);

            // Check if "All Sprints" is selected
            if (selectedSprintId == -1)
            {
                // If "All Sprints" is selected, don't filter by sprint ID
                query.prepare("SELECT "
                              "    User.idUser, "
                              "    User.FirstName, "
                              "    User.LastName, "
                              "    User.Username, "
                              "    TaskSB.Title AS TaskTitle, "
                              "    TaskSB.Priority AS TaskPriority, "
                              "    TaskSB.Status AS TaskStatus, "
                              "    UserStorySB.Title AS UserStoryTitle, "
                              "    UserStorySB.Priority AS UserStoryPriority, "
                              "    UserStorySB.Status AS UserStoryStatus, "
                              "    TaskSB.Description AS TaskDescription, "
                              "    UserStorySB.Description AS UserStoryDescription, "
                              "    TaskSB.SprintBacklog_Sprint_idSprint AS TaskSprint, "
                              "    UserStorySB.SprintBacklog_Sprint_idSprint AS UserStorySprint "
                              "FROM "
                              "    Project "
                              "INNER JOIN "
                              "    Project_has_User ON Project.idProject = Project_has_User.Project_idProject "
                              "INNER JOIN "
                              "    User ON Project_has_User.User_idUser = User.idUser "
                              "LEFT JOIN "
                              "    TaskSB ON User.idUser = TaskSB.Assignee AND TaskSB.SprintBacklog_Sprint_Project_idProject = Project_has_User.Project_idProject "
                              "LEFT JOIN "
                              "    UserStorySB ON User.idUser = UserStorySB.Assignee AND UserStorySB.SprintBacklog_Sprint_Project_idProject = Project_has_User.Project_idProject "
                              "WHERE "
                              "    Project.idProject = :projectId;");
            }
            else
            {
                query.prepare("SELECT "
                              "    User.idUser, "
                              "    User.FirstName, "
                              "    User.LastName, "
                              "    User.Username, "
                              "    TaskSB.Title AS TaskTitle, "
                              "    TaskSB.Priority AS TaskPriority, "
                              "    TaskSB.Status AS TaskStatus, "
                              "    UserStorySB.Title AS UserStoryTitle, "
                              "    UserStorySB.Priority AS UserStoryPriority, "
                              "    UserStorySB.Status AS UserStoryStatus, "
                              "    TaskSB.Description AS TaskDescription, "
                              "    UserStorySB.Description AS UserStoryDescription, "
                              "    TaskSB.SprintBacklog_Sprint_idSprint AS TaskSprint, "
                              "    UserStorySB.SprintBacklog_Sprint_idSprint AS UserStorySprint "
                              "FROM "
                              "    Project "
                              "INNER JOIN "
                              "    Project_has_User ON Project.idProject = Project_has_User.Project_idProject "
                              "INNER JOIN "
                              "    User ON Project_has_User.User_idUser = User.idUser "
                              "LEFT JOIN "
                              "    TaskSB ON User.idUser = TaskSB.Assignee AND TaskSB.SprintBacklog_Sprint_Project_idProject = Project_has_User.Project_idProject AND TaskSB.SprintBacklog_Sprint_idSprint = :sprintId "
                              "LEFT JOIN "
                              "    UserStorySB ON User.idUser = UserStorySB.Assignee AND UserStorySB.SprintBacklog_Sprint_Project_idProject = Project_has_User.Project_idProject AND UserStorySB.SprintBacklog_Sprint_idSprint = :sprintId "
                              "LEFT JOIN"
                              "    Sprint ON Sprint.idSprint = TaskSB.SprintBacklog_Sprint_idSprint "
                              "WHERE "
                              "    Project.idProject = :projectId;");

                query.bindValue(":sprintId", selectedSprintId);

            }

            query.bindValue(":projectId", PassedProjectID);

            QMap<QString, QTreeWidgetItem*> userItemMap;

            if (query.exec()) {
                while (query.next()) {
                    int idUser = query.value(0).toInt();
                    QString firstName = query.value(1).toString();
                    QString lastName = query.value(2).toString();
                    QString username = query.value(3).toString();
                    QString taskTitle = query.value(4).toString();
                    int taskPriorityTree = query.value(5).toInt();
                    QString taskStatus = query.value(6).toString();
                    QString storyTitle = query.value(7).toString();
                    int storyPriorityTree = query.value(8).toInt();
                    QString storyStatus = query.value(9).toString();
                    QString taskDescription = query.value(10).toString();
                    QString storyDescription = query.value(11).toString();
                    int taskSprint = query.value(12).toInt();
                    int storySprint = query.value(13).toInt();


                    QString taskPriority;
                    switch (taskPriorityTree)
                    {
                    case 3:
                        taskPriority = "High";
                        break;
                    case 2:
                        taskPriority = "Medium";
                        break;
                    case 1:
                        taskPriority = "Low";
                        break;
                    default:
                        break;
                    }

                    QString storyPriority;
                    switch (storyPriorityTree)
                    {
                    case 3:
                        taskPriority = "High";
                        break;
                    case 2:
                        taskPriority = "Medium";
                        break;
                    case 1:
                        taskPriority = "Low";
                        break;
                    default:
                        break;
                    }

                    qDebug() << "TASKBOARD: QUERY ASSIGNED idUser: " << idUser;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED firstName: " << firstName;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED lastName: " << lastName;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED username: " << username;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED taskTitle: " << taskTitle;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED taskPriority: " << taskPriorityTree << taskPriority;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED taskStatus: " << taskStatus;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED storyTitle: " << storyTitle;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED storyPriority: " << storyPriorityTree << storyPriorityTree;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED storyStatus: " << storyStatus;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED taskDescription: " << taskDescription;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED storyDescription: " << storyDescription;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED taskSprint: " << taskSprint;
                    qDebug() << "TASKBOARD: QUERY ASSIGNED storySprint: " << storySprint;

                    QString name = firstName + " " + lastName;
                    // qDebug() << "TASKBOARD: name: " << name;

                    QString nameWithId = QString("%1 (%2, %3)").arg(name).arg(username).arg(idUser);
                    QTreeWidgetItem* treeUserItem = userItemMap.value(nameWithId);

                    qDebug() << "TASKBOARD: idUser: " << nameWithId << " = " << idUser;

                    if (!addedUserIds.contains(idUser)) {
                        parentBoard->getInputAssigneeT()->addItem(nameWithId, QVariant(idUser));
                        addedUserIds.insert(idUser);  // Add the user ID to the set
                    }

                    if (!treeUserItem) {
                        treeUserItem = new QTreeWidgetItem(parentBoard->getTaskTreeWidget());
                        treeUserItem->setText(0, nameWithId);
                        userItemMap.insert(nameWithId, treeUserItem);
                    }

                    // Add task for the current user
                    if (!taskTitle.isEmpty()) {
                        QTreeWidgetItem* treeTaskItem = new QTreeWidgetItem(treeUserItem);
                        // QListWidget::setItemWidget(treeUserItem, editButtonT);
                        treeTaskItem->setText(1, taskTitle);
                        treeTaskItem->setText(2, taskPriority);
                        treeTaskItem->setText(3, "Task");
                        // treeTaskItem->setData(0, Qt::UserRole, "task");
                        treeTaskItem->setText(4, taskStatus);
                        // Hidden data - Description, Sprint, Assignee
                        treeTaskItem->setData(5, Qt::UserRole, taskDescription);
                        treeTaskItem->setData(6, Qt::UserRole, taskSprint);
                        treeTaskItem->setData(7, Qt::UserRole, idUser);
                    }

                    // Add user story for the current user
                    if (!storyTitle.isEmpty()) {
                        QTreeWidgetItem* treeStoryItem = new QTreeWidgetItem(treeUserItem);
                        treeStoryItem->setText(1, storyTitle);
                        treeStoryItem->setText(2, storyPriority);
                        treeStoryItem->setText(3, "User Story");
                        // treeStoryItem->setData(0, Qt::UserRole, "userstory");
                        treeStoryItem->setText(4, storyStatus);
                        // Hidden data - Description, Sprint, Assignee
                        treeStoryItem->setData(5, Qt::UserRole, storyDescription);
                        treeStoryItem->setData(6, Qt::UserRole, storySprint);
                        treeStoryItem->setData(7, Qt::UserRole, idUser);
                    }

                    // qDebug() << "TASKBOARD: User and task/user story data fetched successfully!";
                }
                generateUnassigned();
            } else {
                // qDebug() << "TASKBOARD: Failed to fetch user and task/user story data:" << query.lastError().text();
            }

            db.close();
        } else {
            // qDebug() << "TASKBOARD: Connection Not Established - Taskboard class!";
        }
    }
}

void pb_taskboard_implemenation::generateUnassigned()
{
    QTreeWidgetItem* unassignedItem = new QTreeWidgetItem(parentBoard->getTaskTreeWidget());
    unassignedItem->setText(0, "Unassigned");

    DatabaseManager database;
    QSqlDatabase db = database.getDatabase();

    // Passing Project ID and Sprint ID
    int PassedProjectID = parentBoard->getProjectId();
    int selectedSprintId = parentBoard->getSprintDropdown()->currentData().toInt();
    qDebug() << "Project ID in Taskboard generateUnassigned: " << PassedProjectID;
    // qDebug() << "Selected Sprint ID generateUnassigned: " << selectedSprintId;

    if (db.isOpen()) {
        QSqlQuery query(db);

        // Check if "All Sprints" is selected
        if (selectedSprintId == -1)
        {
            query.prepare("SELECT "
                          "    TaskSB.Title AS TaskTitle, "
                          "    TaskSB.Priority AS TaskPriority, "
                          "    TaskSB.Status AS TaskStatus, "
                          "    TaskSB.Description AS TaskDescription, "
                          "    UserStorySB.Title AS UserStoryTitle, "
                          "    UserStorySB.Priority AS UserStoryPriority, "
                          "    UserStorySB.Status AS UserStoryStatus, "
                          "    UserStorySB.Description AS UserStoryDescription, "
                          "    TaskSB.SprintBacklog_Sprint_idSprint AS TaskSprint, "
                          "    UserStorySB.SprintBacklog_Sprint_idSprint AS UserStorySprint "
                          "FROM "
                          "    Project "
                          "INNER JOIN "
                          "    Project_has_User ON Project.idProject = Project_has_User.Project_idProject "
                          "INNER JOIN "
                          "    User ON Project_has_User.User_idUser = User.idUser "
                          "LEFT JOIN "
                          "    TaskSB ON User.idUser = TaskSB.Assignee AND TaskSB.SprintBacklog_Sprint_Project_idProject = Project_has_User.Project_idProject "
                          "LEFT JOIN "
                          "    UserStorySB ON User.idUser = UserStorySB.Assignee AND UserStorySB.SprintBacklog_Sprint_Project_idProject = Project_has_User.Project_idProject "
                          "WHERE "
                          "    Project.idProject = :projectId "
                          "    AND TaskSB.Assignee IS NULL "
                          "    AND UserStorySB.Assignee IS NULL;");
        }
        else
        {
            query.prepare("SELECT "
                          "    TaskSB.Title AS TaskTitle, "
                          "    TaskSB.Priority AS TaskPriority, "
                          "    TaskSB.Status AS TaskStatus, "
                          "    TaskSB.Description AS TaskDescription, "
                          "    UserStorySB.Title AS UserStoryTitle, "
                          "    UserStorySB.Priority AS UserStoryPriority, "
                          "    UserStorySB.Status AS UserStoryStatus, "
                          "    UserStorySB.Description AS UserStoryDescription, "
                          "    TaskSB.SprintBacklog_Sprint_idSprint AS TaskSprint, "
                          "    UserStorySB.SprintBacklog_Sprint_idSprint AS UserStorySprint "
                          "FROM "
                          "    Project "
                          "INNER JOIN "
                          "    Project_has_User ON Project.idProject = Project_has_User.Project_idProject "
                          "INNER JOIN "
                          "    User ON Project_has_User.User_idUser = User.idUser "
                          "LEFT JOIN "
                          "    TaskSB ON User.idUser = TaskSB.Assignee AND TaskSB.SprintBacklog_Sprint_Project_idProject = Project_has_User.Project_idProject AND TaskSB.SprintBacklog_Sprint_idSprint = :sprintId "
                          "LEFT JOIN "
                          "    UserStorySB ON User.idUser = UserStorySB.Assignee AND UserStorySB.SprintBacklog_Sprint_Project_idProject = Project_has_User.Project_idProject AND UserStorySB.SprintBacklog_Sprint_idSprint = :sprintId "
                          "LEFT JOIN"
                          "    Sprint ON Sprint.idSprint = TaskSB.SprintBacklog_Sprint_idSprint "
                          "WHERE "
                          "    Project.idProject = :projectId "
                          "    AND TaskSB.Assignee IS NULL "
                          "    AND UserStorySB.Assignee IS NULL;");

            query.bindValue(":sprintId", selectedSprintId);
        }

        query.bindValue(":projectId", PassedProjectID);

        if (query.exec()) {
            while (query.next()) {
                QString taskTitle = query.value(0).toString();
                int taskPriorityTree = query.value(1).toInt();
                QString taskStatus = query.value(2).toString();
                QString taskDescription = query.value(3).toString();

                QString storyTitle = query.value(4).toString();
                int storyPriorityTree = query.value(5).toInt();
                QString storyStatus = query.value(6).toString();
                QString storyDescription = query.value(7).toString();

                int taskSprint = query.value(12).toInt();
                int storySprint = query.value(13).toInt();

                QString taskPriority;
                switch (taskPriorityTree)
                {
                case 3:
                    taskPriority = "High";
                    break;
                case 2:
                    taskPriority = "Medium";
                    break;
                case 1:
                    taskPriority = "Low";
                    break;
                default:
                    break;
                }

                QString storyPriority;
                switch (storyPriorityTree)
                {
                case 3:
                    taskPriority = "High";
                    break;
                case 2:
                    taskPriority = "Medium";
                    break;
                case 1:
                    taskPriority = "Low";
                    break;
                default:
                    break;
                }

                qDebug() << "TASKBOARD: QUERY UNASSIGNED taskTitle: " << taskTitle;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED taskPriority: " << taskPriorityTree << taskPriority;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED taskStatus: " << taskStatus;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED storyTitle: " << storyTitle;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED storyPriority: " << storyPriorityTree << storyPriorityTree;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED storyStatus: " << storyStatus;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED taskDescription: " << taskDescription;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED storyDescription: " << storyDescription;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED taskSprint: " << taskSprint;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED storySprint: " << storySprint;

                int unassigned = -1;
                // Add task for unassigned
                if (!taskTitle.isEmpty()) {
                    QTreeWidgetItem* treeTaskItem = new QTreeWidgetItem(unassignedItem);
                    treeTaskItem->setText(1, taskTitle);
                    treeTaskItem->setText(2, taskPriority);
                    treeTaskItem->setText(3, "Task");
                    treeTaskItem->setText(4, taskStatus);
                    // Hidden data - Description, Sprint, Assignee
                    treeTaskItem->setData(5, Qt::UserRole, taskDescription);
                    treeTaskItem->setData(6, Qt::UserRole, taskSprint);
                    treeTaskItem->setData(7, Qt::UserRole, unassigned);
                }

                // Add user story for unassigned
                if (!storyTitle.isEmpty()) {
                    QTreeWidgetItem* treeStoryItem = new QTreeWidgetItem(unassignedItem);
                    treeStoryItem->setText(1, storyTitle);
                    treeStoryItem->setText(2, storyPriority);
                    treeStoryItem->setText(3, "User Story");
                    treeStoryItem->setText(4, storyStatus);
                    // Hidden data - Description, Sprint, Assignee
                    treeStoryItem->setData(5, Qt::UserRole, storyDescription);
                    treeStoryItem->setData(6, Qt::UserRole, storySprint);
                    treeStoryItem->setData(7, Qt::UserRole, unassigned);
                }

            }
        } else {
            // qDebug() << "Failed to fetch unassigned tasks and user stories:" << query.lastError().text();
        }

        db.close();
    } else {
        // qDebug() << "Connection Not Established - Taskboard class!";
    }
}

void pb_taskboard_implemenation::fetchSprintDates()
{
    DatabaseManager database;
    QSqlDatabase db = database.getDatabase();

    // Passing Project ID and Sprint ID
    int PassedProjectID = parentBoard->getProjectId();
    int selectedSprintId = parentBoard->getSprintDropdown()->currentData().toInt();
    qDebug() << "Project ID in Taskboard fetchDates: " << PassedProjectID;
    // qDebug() << "Selected Sprint ID in fetchDates: " << selectedSprintId;

    if (db.isOpen()) {
        QSqlQuery query(db);

        if (selectedSprintId == -1)
        {
            parentBoard->updateSprintDateLabel("All Sprints");
        }
        else
        {
            query.prepare("SELECT StartDate, EndDate FROM Sprint "
                          "WHERE  Project_idProject = :projectId "
                          "AND idSprint = :sprintId");
            query.bindValue(":projectId", PassedProjectID);
            query.bindValue(":sprintId", selectedSprintId);

            if (query.exec() && query.next()) {
                QString startDate = query.value(0).toString();
                QString endDate = query.value(1).toString();

                if (startDate.isEmpty() || endDate.isEmpty())
                {
                    parentBoard->updateSprintDateLabel("Missing Date");
                }
                else
                {
                // Format the StartDate and EndDate
                startDate = startDate.mid(5, 5);
                endDate = endDate.mid(5, 5);
                startDate.replace("-", ".");
                endDate.replace("-", ".");

                // Update the label with the new text
                parentBoard->updateSprintDateLabel(startDate + " - " + endDate);
                // qDebug() << "Dates: " << startDate << " - " << endDate;
                }
            } else {
                // qDebug() << "Failed to fetch Sprint dates:" << query.lastError().text();
            }
        }

        db.close();
    } else {
        // qDebug() << "Connection Not Established - Taskboard class!";
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

        // Fetch Sprint dates and update the label
        fetchSprintDates();

        // Update the tree widget
        generateUserTaskTree();

    } else {
        // qDebug() << "Invalid selected data in the sprint dropdown.";
        selectedSprintId = -2;
    }
}
int pb_taskboard_implemenation::getSelectedSprintId() const
{
    return selectedSprintId;
}


/**
 * @brief Hides the create section UI elements.
 * This includes various input fields and buttons related to creating new user stories or tasks.
 */
void pb_taskboard_implemenation::HideShow_CreateSectionTaskboard()
{
    parentBoard->getCreationBoxT()->setVisible(false);

    parentBoard->getCreate_AssigneeT()->setVisible(false);
    parentBoard->getCreate_DescriptionT()->setVisible(false);
    parentBoard->getCreate_HeaderT()->setVisible(false);
    parentBoard->getCreate_StatusT()->setVisible(false);
    parentBoard->getCreate_TitleT()->setVisible(false);

    parentBoard->getInputAssigneeT()->setVisible(false);
    parentBoard->getInputDescriptionT()->setVisible(false);
    parentBoard->getInputStatusT()->setVisible(false);
    parentBoard->getInputTitleT()->setVisible(false);

    parentBoard->getButton_CreateUserStoryT()->setVisible(false);
    parentBoard->getButton_CreateTaskT()->setVisible(false);

    parentBoard->get_BL_SprintDropDownT()->setVisible(false);
    parentBoard->get_SelectedSprintT()->setVisible(false);
}

/**
 * @brief Shows the create section specifically for creating tasks.
 * Adjusts the UI layout and makes relevant elements visible for task creation.
 */
void pb_taskboard_implemenation::showEditTaskboard()
{

    parentBoard->getCreationBoxT()->setVisible(true);

    parentBoard->getCreate_HeaderT()->setVisible(true);

    parentBoard->getCreate_AssigneeT()->setVisible(true);
    parentBoard->getCreate_DescriptionT()->setVisible(true);
    parentBoard->getCreate_StatusT()->setVisible(true);
    parentBoard->getCreate_TitleT()->setVisible(true);

    parentBoard->getInputAssigneeT()->setVisible(true);
    parentBoard->getInputDescriptionT()->setVisible(true);
    parentBoard->getInputStatusT()->setVisible(true);
    parentBoard->getInputTitleT()->setVisible(true);

    parentBoard->getButton_CreateUserStoryT()->setVisible(false);
    parentBoard->getButton_CreateTaskT()->setVisible(true);

    parentBoard->get_BL_SprintDropDownT()->setVisible(true);
    parentBoard->get_SelectedSprintT()->setVisible(true);

    QLabel* Create_HeaderT = parentBoard->getCreate_HeaderT();
    Create_HeaderT->setAlignment(Qt::AlignCenter);  // Align text to center
    Create_HeaderT->setText("TASK");

}

/**
 * @brief Shows the create section specifically for creating user stories.
 * Adjusts the UI layout and makes relevant elements visible for user story creation.
 */
void pb_taskboard_implemenation::showCreateUseStoryTaskboard()
{

    parentBoard->getCreationBoxT()->setVisible(true);

    parentBoard->getCreate_HeaderT()->setVisible(true);

    parentBoard->getCreate_AssigneeT()->setVisible(true);
    parentBoard->getCreate_DescriptionT()->setVisible(true);
    parentBoard->getCreate_StatusT()->setVisible(true);
    parentBoard->getCreate_TitleT()->setVisible(true);

    parentBoard->getInputAssigneeT()->setVisible(true);
    parentBoard->getInputDescriptionT()->setVisible(true);
    parentBoard->getInputStatusT()->setVisible(true);
    parentBoard->getInputTitleT()->setVisible(true);

    parentBoard->getButton_CreateUserStoryT()->setVisible(true);
    parentBoard->getButton_CreateTaskT()->setVisible(false);

    parentBoard->get_BL_SprintDropDownT()->setVisible(true);
    parentBoard->get_SelectedSprintT()->setVisible(true);

    QLabel* Create_HeaderT = parentBoard->getCreate_HeaderT();
    Create_HeaderT->setAlignment(Qt::AlignCenter);  // Align text to center
    Create_HeaderT->setText("USER STORY");

}

/**
 * @brief Retrieves data from the selected item in the Tree Widget for edit
 * Title, Priority, Type, Status
 */
void pb_taskboard_implemenation::retrieveDataTaskboard()
{
    // Clear Previous Inputs
    parentBoard->getInputTitleT()->clear();
    parentBoard->getInputDescriptionT()->clear();
    parentBoard->getInputStatusT()->clear();


    QTreeWidget* treeWidget = parentBoard->getTaskTreeWidget();
    QTreeWidgetItem* selectedItem = treeWidget->currentItem();

    // Tree Widget item retrieval
    if (selectedItem) {

        QString taskTitle = selectedItem->data(1, Qt::DisplayRole).toString();
        QString taskStatus = selectedItem->data(4, Qt::DisplayRole).toString();
        QString hiddenTaskDescription = selectedItem->data(5, Qt::UserRole).toString();
        int hiddenSprint = selectedItem->data(6, Qt::UserRole).toInt();
        int hiddenAssignee = selectedItem->data(7, Qt::UserRole).toInt();

        // Updating Input for editing
        parentBoard->updateInputTitleT(taskTitle);
        parentBoard->updateInputStatusT(taskStatus);
        parentBoard->updateInputDescriptionT(hiddenTaskDescription);
        parentBoard->updateInputAssigneeT(hiddenAssignee);
        parentBoard->updateBL_SprintDropDownT(hiddenSprint);


        qDebug() << "TASKBOARD: RETRIEVE taskTitle:" << taskTitle;
        qDebug() << "TASKBOARD: RETRIEVE taskStatus:" << taskStatus;
        qDebug() << "TASKBOARD: RETRIEVE hiddenTaskDescription: " << hiddenTaskDescription;
        qDebug() << "TASKBOARD: RETRIEVE hiddenAssignee: " << hiddenAssignee;
        qDebug() << "TASKBOARD: RETRIEVE hiddenSprint: " << hiddenSprint;

    } else {
        qDebug() << "TASKBOARD: No item selected.";
    }

}

void pb_taskboard_implemenation::editTaskTaskboard()
{
    qDebug() << "TASKBOARD: EDIT Save Task Taskboard button clicked.";

    QTextEdit* inputDescriptionTt = parentBoard->getInputDescriptionT();
    QTextEdit* inputStatusTt = parentBoard->getInputStatusT();
    QTextEdit* inputTitleTt = parentBoard->getInputTitleT();
    QComboBox* currentSprintTt = parentBoard->get_BL_SprintDropDownT();
    QComboBox* inputAssigneeTt = parentBoard->getInputAssigneeT();

    QString titleT = inputTitleTt->toPlainText();
    QString descriptionT = inputDescriptionTt->toPlainText();
    QString statusT = inputStatusTt->toPlainText();
    int assigneeT = inputAssigneeTt->currentData().toInt();
    QString sprintT = currentSprintTt->currentText();
    int sprintID = currentSprintTt->currentIndex();

    qDebug() << "TASKBOARD: EDIT Input Values:";
    qDebug() << "TASKBOARD: EDIT titleT" << titleT;
    qDebug() << "TASKBOARD: EDIT descriptionT" << descriptionT;
    qDebug() << "TASKBOARD: EDIT statusT" << statusT;
    qDebug() << "TASKBOARD: EDIT assignee" << assigneeT;
    qDebug() << "TASKBOARD: EDIT sprintT" << sprintT << sprintID;

    if (titleT.isEmpty() || descriptionT.isEmpty() || sprintT == "Select Sprint") {
        // One or more fields are empty
        QString errorMessage = "Missing Values:\n";

        if (titleT.isEmpty()) {
            errorMessage += "- Title\n";
        }
        if (descriptionT.isEmpty()) {
            errorMessage += "- Description\n";
        }
        if (sprintT == "Select Sprint") {
            errorMessage += "- Sprint\n";
        }

        QMessageBox::warning(nullptr, "Missing Values", errorMessage);
    }
    else
    {
        addToTableTaskboard(titleT, descriptionT, statusT, assigneeT, sprintT);
    }
}

void pb_taskboard_implemenation::editUserStoryTaskboard()
{
    qDebug() << "TASKBOARD: EDIT Save User Story Taskboard button clicked.";

    QTextEdit* inputDescriptionTus = parentBoard->getInputDescriptionT();
    QTextEdit* inputStatusTus = parentBoard->getInputStatusT();
    QTextEdit* inputTitleTus = parentBoard->getInputTitleT();
    QComboBox* currentSprintTus = parentBoard->get_BL_SprintDropDownT();
    QComboBox* inputAssigneeTus = parentBoard->getInputAssigneeT();

    QString titleT = inputTitleTus->toPlainText();
    QString descriptionT = inputDescriptionTus->toPlainText();
    QString statusT = inputStatusTus->toPlainText();
    int assigneeT = inputAssigneeTus->currentData().toInt();
    QString sprintT = currentSprintTus->currentText();
    int sprintID = currentSprintTus->currentIndex();

    qDebug() << "TASKBOARD: EDIT Input Values:";
    qDebug() << "TASKBOARD: EDIT titleT" << titleT;
    qDebug() << "TASKBOARD: EDIT descriptionT" << descriptionT;
    qDebug() << "TASKBOARD: EDIT statusT" << statusT;
    qDebug() << "TASKBOARD: EDIT assignee" << assigneeT;
    qDebug() << "TASKBOARD: EDIT sprintT" << sprintT << sprintID;

    if (titleT.isEmpty() || descriptionT.isEmpty()|| sprintT == "Select Sprint") {
        // One or more fields are empty
        QString errorMessage = "Missing Values:\n";

        if (titleT.isEmpty()) {
            errorMessage += "- Title\n";
        }
        if (descriptionT.isEmpty()) {
            errorMessage += "- Description\n";
        }
        if (sprintT == "Select Sprint") {
            errorMessage += "- Sprint\n";
        }

        QMessageBox::warning(nullptr, "Missing Values", errorMessage);
    }
    else
    {
        addToTableTaskboard(titleT, descriptionT, statusT, assigneeT, sprintT);
    }
}


void pb_taskboard_implemenation::addToTableTaskboard(const QString& title, const QString& description, const QString& status, int assignee, const QString& sprint)
{
    qDebug() << "TASKBOARD: addToTableTaskboard Function is called";
    HideShow_CreateSectionTaskboard();
    generateUserTaskTree();


    if (assignee == -1)
    {
        // doesnt input assignee so 2 queries, 1 with assignee, 1 without
    }

    // if (parentBoard->getButton_CreateTaskT()->isVisible() == true)
    // {
    //     DatabaseManager database;
    //     QSqlDatabase UserStorySB = database.getDatabase();
    //     if (!UserStorySB.isOpen()) {
    //         qDebug() << "TASKBOARD: Connection Not Established - Task Insert!";
    //         return;
    //     }

    //     QSqlQuery query(UserStorySB);
    //     query.prepare("INSERT INTO scrummy.TaskSB(Title, Description, Status, Priority, Assignee, ProductBacklog_idProductBacklog, ProductBacklog_Project_idProject)"
    //                   "VALUES (:title, :description, :status, :priority, :assignee, 1, 1)");
    //     query.bindValue(":title", title);
    //     query.bindValue(":description", description);
    //     query.bindValue(":status", status);
    //     query.bindValue(":priority", priority);
    //     query.bindValue(":assignee", assignee);
    //     query.bindValue(":sprint", sprint);


    //     if (!query.exec()) {
    //         qDebug() << "TASKBOARD: Failed to insert data into UserStorySB table:" << query.lastError().text();
    //         UserStorySB.close();
    //         return;
    //     }
    //     qDebug() << "TASKBOARD: Data inserted into UserStorySB table successfully!";
    //     UserStorySB.close();
    // }

    // if (parentBoard->getButton_CreateUserStoryT()->isVisible() == true)
    // {
    //     DatabaseManager database;
    //     QSqlDatabase TaskSB = database.getDatabase();
    //     if (!TaskSB.isOpen()) {
    //         qDebug() << "TASKBOARD: Connection Not Established - UserStory Insert!";
    //         return;
    //     }

    //     QSqlQuery query(TaskSB);
    //     query.prepare("INSERT INTO scrummy.UserStorySB(Title, Description, Status, Priority, Assignee, ProductBacklog_idProductBacklog, ProductBacklog_Project_idProject)"
    //                   "VALUES (:title, :description, :status, :priority, :assignee, 1, 1)");
    //     query.bindValue(":title", title);
    //     query.bindValue(":description", description);
    //     query.bindValue(":status", status);
    //     query.bindValue(":priority", priority);
    //     query.bindValue(":assignee", assignee);
    //     query.bindValue(":sprint", sprint);


    //     if (!query.exec()) {
    //         qDebug() << "TASKBOARD: Failed to insert data into TaskSB table:" << query.lastError().text();
    //         TaskSB.close();
    //         return;
    //     }
    //     qDebug() << "TASKBOARD: Data inserted into TaskSB table successfully!";
    //     TaskSB.close();
    // }
}

/**
 * @brief Edits/Creates the selected Task/UserStory.
 * Both implementations are inside this function to reduce computing.
 */
void pb_taskboard_implemenation::createNewItemInDatabase()
{

    // // Get the userItemMap
    // QMap<QString, QTreeWidgetItem*> userItemMap = getUserItemMap();
}
