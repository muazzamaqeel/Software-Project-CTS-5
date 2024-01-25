// pb_taskboard_implemenation.cpp
#include "pb_taskboard_implemenation.h"
#include "QtWidgets/qheaderview.h"
#include "parentboard.h"  // Include parentboard header
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QComboBox>
#include <QDebug>
#include <QLabel>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDateTime>
#include <QMessageBox>

/** Known Errors/Bugs
 *  -
 */

/**
 * @brief Implementation for the Taskboard Page in Parentboard
 * This class handles data in the TaskSB and UserStorySB tables
 * @param parentBoardInstance
 *
 * @details Functions:
 *      pb_taskboard_Retrieval()
 *      fetchSprintData()
 *      generateUserTaskTree()
 *      generateUnassigned()
 *      fetchSprintDates()
 *      updateLabels(int index)
 *      getSelectedSprintId() const
 *      showEditTaskboard()
 *      retrieveDataTaskboard()
 *      editTaskTaskboard()
 *      addToTableTaskboard(const QString& title, const QString& description, const QString& status, int assignee, int sprint, int id, const QString& type)
 *      ~pb_taskboard_implemenation()
 */
pb_taskboard_implemenation::pb_taskboard_implemenation(parentboard* parentBoardInstance)
    : parentBoard(parentBoardInstance),
    scrollAreaLayout(parentBoardInstance->getScrollAreaLayout())  // Initialize the layout
{
    model = new QStandardItemModel(parentBoard);

    // Passing project ID
    int PassedProjectID = parentBoard->getProjectId();
    qDebug() << "TASKBOARD: Project ID in Taskboard: " << PassedProjectID;

    if (PassedProjectID != 0)
    {
        pb_taskboard_Retrieval();
    }

    // Tree Table Resize Header/Section
    QHeaderView* header = parentBoard->getTaskTreeWidget()->header();
    header->resizeSection(0, 300);
    header->resizeSection(1, 600);

    // Connections
    connect(parentBoard->getTaskTreeWidget(), &QTreeWidget::itemDoubleClicked, this, &pb_taskboard_implemenation::retrieveDataTaskboard);
    connect(parentBoard->getSprintDropdown(), QOverload<int>::of(&QComboBox::currentIndexChanged), this, &pb_taskboard_implemenation::updateLabels);    
}
/**
 * @brief Function call hub for data fetching and generation.
 */
void pb_taskboard_implemenation::pb_taskboard_Retrieval()
{
    fetchSprintData();
    fetchSprintDates();
    generateUserTaskTree();
    parentBoard->getCreationBoxT()->setVisible(false);
}

/**
 * @brief Populates the sprint selection Dropdown/ComboBox
 * getSprintDropdown, get_BL_SprintDropDownT
 */
void pb_taskboard_implemenation::fetchSprintData()
{
    // Clearing Dropdowns/ComboBoxes before adding items
    parentBoard->getSprintDropdown()->clear();
    parentBoard->get_BL_SprintDropDownT()->clear();

    // Initializing first Items
    parentBoard->getSprintDropdown()->addItem("All Sprints", -1);
    parentBoard->get_BL_SprintDropDownT()->addItem(" ", -1);

    // Sprint Fetching Database
    DatabaseManager database;
    QSqlDatabase FetchSprintsTaskboard = database.getDatabase();

    // Passing project ID
    int PassedProjectID = parentBoard->getProjectId();
    qDebug() << "TASKBOARD: Project ID in Taskboard fetchSprint: " << PassedProjectID;

    if (FetchSprintsTaskboard.isOpen()) {
        // qDebug() << "TASKBOARD: Connection Established - Taskboard class!";

        QSqlQuery query(FetchSprintsTaskboard);
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

        FetchSprintsTaskboard.close();
    } else {
        // qDebug() << "TASKBOARD: Connection Not Established - Taskboard class!";
    }
}

/**
 * @brief Adds User parent items to the Tree Widget
 * Adds Task/UserStory children items to the parent items
 * Calls generateUnassigned
 */
void pb_taskboard_implemenation::generateUserTaskTree()
{

    // Clear existing items from the InputAssigneeT
    parentBoard->getInputAssigneeT()->clear();

    QSet<int> addedUserIds;  // Use a set to track added user IDs

    parentBoard->getInputAssigneeT()->addItem("Unassigned", -1);

    // Fetch User and Task data and generate the tree
    DatabaseManager database;
    QSqlDatabase UserTasksTaskboard = database.getDatabase();

    // Passing Project ID and Sprint ID
    int PassedProjectID = parentBoard->getProjectId();
    int selectedSprintId = parentBoard->getSprintDropdown()->currentData().toInt();
    qDebug() << "TASKBOARD: Project ID in Taskboard generateUserTasks: " << PassedProjectID;
    // qDebug() << "TASKBOARD: Selected Sprint ID: " << selectedSprintId;

    if (UserTasksTaskboard.isOpen()) {
        // qDebug() << "TASKBOARD: Connection Established - Taskboard class!";

        QSqlQuery query(UserTasksTaskboard);

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
                          "    UserStorySB.SprintBacklog_Sprint_idSprint AS UserStorySprint, "
                          "    TaskSB.idTask AS idTask, "
                          "    UserStorySB.idUserStorySB AS idStory "
                          "FROM "
                          "    Project "
                          "INNER JOIN "
                          "    User_Role_Project ON Project.idProject = User_Role_Project.Project_idProject "
                          "INNER JOIN "
                          "    User ON User_Role_Project.User_idUser = User.idUser "
                          "LEFT JOIN "
                          "    TaskSB ON User.idUser = TaskSB.Assignee AND TaskSB.SprintBacklog_Sprint_Project_idProject = User_Role_Project.Project_idProject "
                          "LEFT JOIN "
                          "    UserStorySB ON User.idUser = UserStorySB.Assignee AND UserStorySB.SprintBacklog_Sprint_Project_idProject = User_Role_Project.Project_idProject "
                          "WHERE "
                          "    Project.idProject = :projectId "
                          "ORDER BY "
                          "    User.LastName;");
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
                          "    UserStorySB.SprintBacklog_Sprint_idSprint AS UserStorySprint, "
                          "    TaskSB.idTask AS idTask, "
                          "    UserStorySB.idUserStorySB AS idStory "
                          "FROM "
                          "    Project "
                          "INNER JOIN "
                          "    User_Role_Project ON Project.idProject = User_Role_Project.Project_idProject "
                          "INNER JOIN "
                          "    User ON User_Role_Project.User_idUser = User.idUser "
                          "LEFT JOIN "
                          "    TaskSB ON User.idUser = TaskSB.Assignee AND TaskSB.SprintBacklog_Sprint_Project_idProject = User_Role_Project.Project_idProject AND TaskSB.SprintBacklog_Sprint_idSprint = :sprintId "
                          "LEFT JOIN "
                          "    UserStorySB ON User.idUser = UserStorySB.Assignee AND UserStorySB.SprintBacklog_Sprint_Project_idProject = User_Role_Project.Project_idProject AND UserStorySB.SprintBacklog_Sprint_idSprint = :sprintId "
                          "LEFT JOIN"
                          "    Sprint ON Sprint.idSprint = TaskSB.SprintBacklog_Sprint_idSprint "
                          "WHERE "
                          "    Project.idProject = :projectId "
                          "ORDER BY "
                          "    User.LastName;");

            query.bindValue(":sprintId", selectedSprintId);

        }

        query.bindValue(":projectId", PassedProjectID);

        QMap<QString, QTreeWidgetItem*> userItemMap;
        QSet<int> uniqueTaskIDs;
        QSet<int> uniqueStoryIDs;

        // Clear Tree Wdiget items
        parentBoard->getTaskTreeWidget()->clear();

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

                int idTask = query.value(14).toInt();
                int idStory = query.value(15).toInt();


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
                case -1:
                    taskPriority = "None";
                    break;
                default:
                    break;
                }

                QString storyPriority;
                switch (storyPriorityTree)
                {
                case 3:
                    storyPriority = "High";
                    break;
                case 2:
                    storyPriority = "Medium";
                    break;
                case 1:
                    storyPriority = "Low";
                    break;
                case -1:
                    storyPriority = "None";
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
                qDebug() << "TASKBOARD: QUERY ASSIGNED storyPriority: " << storyPriorityTree << storyPriority;
                qDebug() << "TASKBOARD: QUERY ASSIGNED storyStatus: " << storyStatus;
                qDebug() << "TASKBOARD: QUERY ASSIGNED taskDescription: " << taskDescription;
                qDebug() << "TASKBOARD: QUERY ASSIGNED storyDescription: " << storyDescription;
                qDebug() << "TASKBOARD: QUERY ASSIGNED taskSprint: " << taskSprint;
                qDebug() << "TASKBOARD: QUERY ASSIGNED storySprint: " << storySprint;
                qDebug() << "TASKBOARD: QUERY ASSIGNED idTask: " << idTask;
                qDebug() << "TASKBOARD: QUERY ASSIGNED idStory: " << idStory;

                QString name = firstName + " " + lastName;
                // qDebug() << "TASKBOARD: name: " << name;

                QString nameWithId = name + " (" + username + ")";
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
                if (!taskTitle.isEmpty() && !uniqueTaskIDs.contains(idTask)) {
                    QTreeWidgetItem* treeTaskItem = new QTreeWidgetItem(treeUserItem);
                    treeTaskItem->setText(1, taskTitle);
                    treeTaskItem->setText(2, taskPriority);
                    treeTaskItem->setText(3, "Task");
                    treeTaskItem->setText(4, taskStatus);
                    treeTaskItem->setData(5, Qt::UserRole, taskDescription);
                    treeTaskItem->setData(6, Qt::UserRole, taskSprint);
                    treeTaskItem->setData(7, Qt::UserRole, idUser);
                    treeTaskItem->setData(8, Qt::UserRole, idTask);

                    // Add the task ID to the set to mark it as added
                    uniqueTaskIDs.insert(idTask);
                }

                // Add user story for the current user
                if (!storyTitle.isEmpty() && !uniqueStoryIDs.contains(idStory)) {
                    QTreeWidgetItem* treeStoryItem = new QTreeWidgetItem(treeUserItem);
                    treeStoryItem->setText(1, storyTitle);
                    treeStoryItem->setText(2, storyPriority);
                    treeStoryItem->setText(3, "User Story");
                    treeStoryItem->setText(4, storyStatus);
                    treeStoryItem->setData(5, Qt::UserRole, storyDescription);
                    treeStoryItem->setData(6, Qt::UserRole, storySprint);
                    treeStoryItem->setData(7, Qt::UserRole, idUser);
                    treeStoryItem->setData(8, Qt::UserRole, idStory);

                    // Add the user story ID to the set to mark it as added
                    uniqueStoryIDs.insert(idStory);
                }


                // qDebug() << "TASKBOARD: User and task/user story data fetched successfully!";
            }
            generateUnassigned();
        } else {
            // qDebug() << "TASKBOARD: Failed to fetch user and task/user story data:" << query.lastError().text();
        }

        UserTasksTaskboard.close();
    } else {
        // qDebug() << "TASKBOARD: Connection Not Established - Taskboard class!";
    }
}

/**
 * @brief Adds children items to unassignedItem
 * Fetches Tasks/User Stories where assignee is NULL
 */
void pb_taskboard_implemenation::generateUnassigned()
{
    QTreeWidgetItem* unassignedItem = new QTreeWidgetItem(parentBoard->getTaskTreeWidget());
    unassignedItem->setText(0, "Unassigned");

    DatabaseManager database;
    QSqlDatabase UnassignedTaskboard = database.getDatabase();

    // Passing Project ID and Sprint ID
    int PassedProjectID = parentBoard->getProjectId();
    int selectedSprintId = parentBoard->getSprintDropdown()->currentData().toInt();
    qDebug() << "Project ID in Taskboard generateUnassigned: " << PassedProjectID;
    // qDebug() << "Selected Sprint ID generateUnassigned: " << selectedSprintId;

    if (UnassignedTaskboard.isOpen()) {
        QSqlQuery query(UnassignedTaskboard);

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
                          "    UserStorySB.SprintBacklog_Sprint_idSprint AS UserStorySprint, "
                          "    TaskSB.idTask AS idTask, "
                          "    UserStorySB.idUserStorySB AS idStory "
                          "FROM "
                          "    Project "
                          "LEFT JOIN "
                          "    TaskSB ON TaskSB.Assignee IS NULL "
                          "LEFT JOIN "
                          "    UserStorySB ON UserStorySB.Assignee IS NULL "
                          "WHERE "
                          "    Project.idProject = :projectId");
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
                          "    UserStorySB.SprintBacklog_Sprint_idSprint AS UserStorySprint, "
                          "    TaskSB.idTask AS idTask, "
                          "    UserStorySB.idUserStorySB AS idStory "
                          "FROM "
                          "    Project "
                          "LEFT JOIN "
                          "    TaskSB ON TaskSB.Assignee IS NULL AND TaskSB.SprintBacklog_Sprint_idSprint = :sprintId "
                          "LEFT JOIN "
                          "    UserStorySB ON UserStorySB.Assignee IS NULL AND UserStorySB.SprintBacklog_Sprint_idSprint = :sprintId "
                          "LEFT JOIN "
                          "    Sprint ON Sprint.idSprint = TaskSB.SprintBacklog_Sprint_idSprint AND Sprint.idSprint = UserStorySB.SprintBacklog_Sprint_idSprint "
                          "WHERE "
                          "    Project.idProject = :projectId;");

            query.bindValue(":sprintId", selectedSprintId);
        }

        query.bindValue(":projectId", PassedProjectID);

        QSet<int> uniqueTaskIDs;
        QSet<int> uniqueStoryIDs;

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

                int taskSprint = query.value(8).toInt();
                int storySprint = query.value(9).toInt();

                int idTask = query.value(10).toInt();
                int idStory = query.value(11).toInt();

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
                    storyPriority = "High";
                    break;
                case 2:
                    storyPriority = "Medium";
                    break;
                case 1:
                    storyPriority = "Low";
                    break;
                default:
                    break;
                }

                qDebug() << "TASKBOARD: QUERY UNASSIGNED taskTitle: " << taskTitle;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED taskPriority: " << taskPriorityTree << taskPriority;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED taskStatus: " << taskStatus;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED storyTitle: " << storyTitle;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED storyPriority: " << storyPriorityTree << storyPriority;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED storyStatus: " << storyStatus;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED taskDescription: " << taskDescription;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED storyDescription: " << storyDescription;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED taskSprint: " << taskSprint;
                qDebug() << "TASKBOARD: QUERY UNASSIGNED storySprint: " << storySprint;
                qDebug() << "TASKBOARD: QUERY ASSIGNED idTask: " << idTask;
                qDebug() << "TASKBOARD: QUERY ASSIGNED idStory: " << idStory;

                int unassigned = -1;
                // Add task for unassigned
                if (!taskTitle.isEmpty() && !uniqueTaskIDs.contains(idTask)) {
                    QTreeWidgetItem* treeTaskItem = new QTreeWidgetItem(unassignedItem);
                    treeTaskItem->setText(1, taskTitle);
                    treeTaskItem->setText(2, taskPriority);
                    treeTaskItem->setText(3, "Task");
                    treeTaskItem->setText(4, taskStatus);
                    // Hidden data - Description, Sprint, Assignee
                    treeTaskItem->setData(5, Qt::UserRole, taskDescription);
                    treeTaskItem->setData(6, Qt::UserRole, taskSprint);
                    treeTaskItem->setData(7, Qt::UserRole, unassigned);
                    treeTaskItem->setData(8, Qt::UserRole, idTask);

                    // Add the task ID to the set to mark it as added
                    uniqueTaskIDs.insert(idTask);
                }

                // Add user story for unassigned
                if (!storyTitle.isEmpty() && !uniqueStoryIDs.contains(idStory)) {
                    QTreeWidgetItem* treeStoryItem = new QTreeWidgetItem(unassignedItem);
                    treeStoryItem->setText(1, storyTitle);
                    treeStoryItem->setText(2, storyPriority);
                    treeStoryItem->setText(3, "User Story");
                    treeStoryItem->setText(4, storyStatus);
                    // Hidden data - Description, Sprint, Assignee
                    treeStoryItem->setData(5, Qt::UserRole, storyDescription);
                    treeStoryItem->setData(6, Qt::UserRole, storySprint);
                    treeStoryItem->setData(7, Qt::UserRole, unassigned);
                    treeStoryItem->setData(8, Qt::UserRole, idStory);

                    // Add the user story ID to the set to mark it as added
                    uniqueStoryIDs.insert(idStory);
                }

            }
        } else {
            // qDebug() << "Failed to fetch unassigned tasks and user stories:" << query.lastError().text();
        }

        UnassignedTaskboard.close();
    } else {
        // qDebug() << "Connection Not Established - Taskboard class!";
    }
}

/**
 * @brief Fetches sprint dates based on the selected sprint
 * Updates SprintDateLabel - Format: startDate - endDate
 */
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
            parentBoard->updateSprintDateLabel("");
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

/**
 * @brief Intermediate function to update the Tree Widget based on the selected sprint
 * @param index of selected sprint
 * Calls fetchSprintDates, generateUserTaskTree
 */
void pb_taskboard_implemenation::updateLabels(int index)
{

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

/**
 * @brief Returns the ID of the selected sprint from the Dropdown/ComboBox
 * @return selectedSprintId
 */
int pb_taskboard_implemenation::getSelectedSprintId() const
{
    return selectedSprintId;
}

/**
 * @brief Shows the editing section specifically for editing Tasks/User Stories.
 * Adjusts the UI layout and makes relevant elements visible for task creation.
 */
void pb_taskboard_implemenation::showEditTaskboard()
{

    QComboBox* inputAssigneeT = parentBoard->getInputAssigneeT();
    QComboBox* inputSprintT = parentBoard->get_BL_SprintDropDownT();

    if (parentBoard->getCreationBoxT()->isVisible())
    {
        parentBoard->getCreationBoxT()->setVisible(false);
        parentBoard->getButton_CreateTaskT()->setVisible(false);
        // Clear Previous Inputs
        parentBoard->getInputTitleT()->clear();
        parentBoard->getInputDescriptionT()->clear();
        parentBoard->getInputStatusT()->clear();

        inputAssigneeT->setCurrentIndex(-1);
        inputSprintT->setCurrentIndex(-1);

    }
    else
    {
        parentBoard->getCreationBoxT()->setVisible(true);
        parentBoard->getButton_CreateTaskT()->setVisible(false);
        // Clear Previous Inputs
        parentBoard->getInputTitleT()->clear();
        parentBoard->getInputDescriptionT()->clear();
        parentBoard->getInputStatusT()->clear();

        inputAssigneeT->setCurrentIndex(-1);
        inputSprintT->setCurrentIndex(-1);
    }

    QLabel* Create_HeaderT = parentBoard->getCreate_HeaderT();
    Create_HeaderT->setAlignment(Qt::AlignCenter);  // Align text to center
    Create_HeaderT->setText("Edit");
}

/**
 * @brief Retrieves data from the selected item in the Tree Widget for edit
 */
void pb_taskboard_implemenation::retrieveDataTaskboard()
{
    if (!parentBoard->getCreationBoxT()->isVisible())
    {
        return;
    }

    // Tree Widget item retrieval
    QTreeWidget* treeWidget = parentBoard->getTaskTreeWidget();
    QTreeWidgetItem* selectedItem = treeWidget->currentItem();
    if (selectedItem) {

        QString taskTitle = selectedItem->data(1, Qt::DisplayRole).toString();
        QString taskStatus = selectedItem->data(4, Qt::DisplayRole).toString();
        QString hiddenTaskDescription = selectedItem->data(5, Qt::UserRole).toString();
        int hiddenSprint = selectedItem->data(6, Qt::UserRole).toInt();
        int hiddenAssignee = selectedItem->data(7, Qt::UserRole).toInt();

        // Hiding buttons depending on the taskType
        QLabel* Create_HeaderT = parentBoard->getCreate_HeaderT();
        QString taskType = selectedItem->data(3, Qt::DisplayRole).toString();
        if (taskType == "Task")
        {
            parentBoard->getButton_CreateTaskT()->setVisible(true);
            Create_HeaderT->setText("Task");
        }
        if (taskType == "User Story")
        {
            parentBoard->getButton_CreateTaskT()->setVisible(true);
            Create_HeaderT->setText("User Story");
        }

        // Updating Input for editing
        if (!taskTitle.isEmpty()) // Ignoring User Items
        {
            // Clear Previous Inputs
            parentBoard->getInputTitleT()->clear();
            parentBoard->getInputDescriptionT()->clear();
            parentBoard->getInputStatusT()->clear();

            parentBoard->updateInputTitleT(taskTitle);
            parentBoard->updateInputStatusT(taskStatus);
            parentBoard->updateInputDescriptionT(hiddenTaskDescription);
            parentBoard->updateInputAssigneeT(hiddenAssignee);
            parentBoard->updateBL_SprintDropDownT(hiddenSprint);

            qDebug() << "TASKBOARD: RETRIEVE hiddenSprint: " << hiddenSprint;
            qDebug() << "TASKBOARD: RETRIEVE taskTitle:" << taskTitle;
            qDebug() << "TASKBOARD: RETRIEVE taskStatus:" << taskStatus;
            qDebug() << "TASKBOARD: RETRIEVE hiddenTaskDescription: " << hiddenTaskDescription;
            qDebug() << "TASKBOARD: RETRIEVE hiddenAssignee: " << hiddenAssignee;

        }

    } else {
        qDebug() << "TASKBOARD: No item selected.";
    }

}

/**
 * @brief Retrieves all inputs and data on selected Task/UserStory
 * Calls addToTableTaskboard
 */
void pb_taskboard_implemenation::editTaskTaskboard()
{
    qDebug() << "TASKBOARD: EDIT Save Task/UserStory Taskboard button clicked.";

    // Tree Widget Task/User Story ID retrieval
    QTreeWidget* treeWidget = parentBoard->getTaskTreeWidget();
    QTreeWidgetItem* selectedItem = treeWidget->currentItem();
    if (selectedItem)
    {
        QString taskType = selectedItem->data(3, Qt::DisplayRole).toString();
        int hiddenID = selectedItem->data(8, Qt::UserRole).toInt();

        QTextEdit* inputDescriptionT = parentBoard->getInputDescriptionT();
        QTextEdit* inputStatusT = parentBoard->getInputStatusT();
        QTextEdit* inputTitleT = parentBoard->getInputTitleT();
        QComboBox* inputAssigneeT = parentBoard->getInputAssigneeT();
        QComboBox* inputSprintT = parentBoard->get_BL_SprintDropDownT();

        QString titleT = inputTitleT->toPlainText();
        QString descriptionT = inputDescriptionT->toPlainText();
        QString statusT = inputStatusT->toPlainText();
        int assigneeT = inputAssigneeT->currentData().toInt();
        int sprintT = inputSprintT->currentData().toInt();

        qDebug() << "TASKBOARD: EDIT Input Values:";
        qDebug() << "TASKBOARD: EDIT titleT" << titleT;
        qDebug() << "TASKBOARD: EDIT descriptionT" << descriptionT;
        qDebug() << "TASKBOARD: EDIT statusT" << statusT;
        qDebug() << "TASKBOARD: EDIT assignee" << assigneeT;
        qDebug() << "TASKBOARD: EDIT sprintT" << sprintT;
        qDebug() << "TASKBOARD: EDIT hiddenID" << hiddenID;
        qDebug() << "TASKBOARD: EDIT taskType" << taskType;

        if (titleT.isEmpty() || descriptionT.isEmpty() || sprintT == -1) {
            // One or more fields are empty
            QString errorMessage = "Missing Values:\n";

            if (titleT.isEmpty()) {
                errorMessage += "- Title\n";
            }
            if (descriptionT.isEmpty()) {
                errorMessage += "- Description\n";
            }
            if (sprintT == -1) {
                errorMessage += "- Sprint\n";
            }

            QMessageBox::warning(nullptr, "Missing Values", errorMessage);
        }
        else
        {
            addToTableTaskboard(titleT, descriptionT, statusT, assigneeT, sprintT, hiddenID, taskType);
        }
    }
}

/**
 * @brief Function to update TaskSB and UserStorySB tables in the database.
 * @param title of Task/User Story
 * @param description of Task/User Story
 * @param status of Task/User Story
 * @param assignee of Task/User Story
 * @param sprint of Task/User Story
 * @param id of Task/User Story
 * @param type Task/User Story
 */
void pb_taskboard_implemenation::addToTableTaskboard(const QString& title, const QString& description, const QString& status, int assignee, int sprint, int id, const QString& type)
{
    qDebug() << "TASKBOARD: addToTableTaskboard Function is called";

    qDebug() << "TASKBOARD: QUERY UPDATE Edit Input Values:";
    qDebug() << "TASKBOARD: QUERY UPDATE Edit title" << title;
    qDebug() << "TASKBOARD: QUERY UPDATE Edit description" << description;
    qDebug() << "TASKBOARD: QUERY UPDATE Edit status" << status;
    qDebug() << "TASKBOARD: QUERY UPDATE Edit assignee" << assignee;
    qDebug() << "TASKBOARD: QUERY UPDATE Edit sprint" << sprint;
    qDebug() << "TASKBOARD: QUERY UPDATE Edit ID" << id;
    qDebug() << "TASKBOARD: QUERY UPDATE Edit type" << type;


    // Task Update Query
    if (parentBoard->getButton_CreateTaskT()->isVisible() == true && type == "Task")
    {
        DatabaseManager database;
        QSqlDatabase EditTaskSB = database.getDatabase();
        if (!EditTaskSB.isOpen()) {
            qDebug() << "TASKBOARD: Connection Not Established - Task Insert!";
            return;
        }

        QSqlQuery query(EditTaskSB);
        query.prepare("UPDATE TaskSB "
                      "SET Title=:title, "
                      "Description=:description, "
                      "Status=:status, "
                      "Assignee=:assignee, "
                      "SprintBacklog_idSprintBacklog=:sprint, "
                      "SprintBacklog_Sprint_idSprint=:sprint "
                      "WHERE idTask=:id;");

        // Bind the 'assignee' value, handling NULL if necessary
        if (assignee == -1) {
            query.bindValue(":assignee", QVariant()); // assignee = NULL
        } else {
            query.bindValue(":assignee", assignee);
        }
        query.bindValue(":title", title);
        query.bindValue(":description", description);
        query.bindValue(":status", status);
        query.bindValue(":sprint", sprint);
        query.bindValue(":id", id);


        if (!query.exec()) {
            qDebug() << "TASKBOARD: Failed to update data into TaskSB table:" << query.lastError().text();
            EditTaskSB.close();
            return;
        }
        qDebug() << "TASKBOARD: Data update in TaskSB table successfully!";
        parentBoard->getCreationBoxT()->setVisible(false);
        generateUserTaskTree();
        EditTaskSB.close();
    } else {
        qDebug() << "TASKBOARD: TASK Could not open Query";
    }


    // User Story Update Query
    if (parentBoard->getButton_CreateTaskT()->isVisible() == true && type == "User Story")
    {
        DatabaseManager database;
        QSqlDatabase EditUserStorySB = database.getDatabase();
        if (!EditUserStorySB.isOpen()) {
            qDebug() << "TASKBOARD: Connection Not Established - User Story Insert!";
            return;
        }

        QSqlQuery query(EditUserStorySB);
        query.prepare("UPDATE UserStorySB "
                      "SET Title=:title, "
                      "Description=:description, "
                      "Status=:status, "
                      "Assignee=:assignee, "
                      "SprintBacklog_idSprintBacklog=:sprint, "
                      "SprintBacklog_Sprint_idSprint=:sprint "
                      "WHERE idUserStorySB=:id;");

        // Bind the 'assignee' value, handling NULL if necessary
        if (assignee == -1) {
            query.bindValue(":assignee", QVariant()); // assignee = NULL
        } else {
            query.bindValue(":assignee", assignee);
        }
        query.bindValue(":title", title);
        query.bindValue(":description", description);
        query.bindValue(":status", status);
        query.bindValue(":sprint", sprint);
        query.bindValue(":id", id);


        if (!query.exec()) {
            qDebug() << "TASKBOARD: Failed to update data into TaskSB table:" << query.lastError().text();
            EditUserStorySB.close();
            return;
        }
        qDebug() << "TASKBOARD: Data update in TaskSB table successfully!";
        parentBoard->getCreationBoxT()->setVisible(false);
        generateUserTaskTree();
        EditUserStorySB.close();
    } else {
        qDebug() << "TASKBOARD: USER-STORY Could not open Query";
    }
}


/**
 * @brief Destructor
 */
pb_taskboard_implemenation::~pb_taskboard_implemenation()
{
    delete model;
}
