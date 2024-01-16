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
                      "WHERE Project_idProject = 1"); // value to replace with :projectId
        query.bindValue(":projectId", PassedProjectID);  // Use the stored project ID

        if (query.exec()) {
            while (query.next()) {
                int idSprint = query.value(0).toInt();
                QString title = query.value(1).toString();

                parentBoard->getSprintDropdown()->addItem(title, idSprint);
                parentBoard->get_BL_SprintDropDownT()->addItem(title, idSprint);

                // qDebug() << "TASKBOARD: Sprint data fetched successfully!";
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
                              "   User.idUser, "
                              "   User.FirstName, "
                              "   User.LastName, "
                              "   TaskSB.Title, "
                              "   TaskSB.Priority, "
                              "   TaskSB.Status, "
                              "   UserStorySB.Title, "
                              "   UserStorySB.Priority, "
                              "   UserStorySB.Status, "
                              "   User.Username "
                              "FROM "
                              "   User "
                              "LEFT JOIN "
                              "   TaskSB ON User.idUser = TaskSB.Assignee "
                              "   AND TaskSB.SprintBacklog_Sprint_Project_idProject = 1 "
                              "LEFT JOIN "
                              "   UserStorySB ON User.idUser = UserStorySB.Assignee "
                              "   AND UserStorySB.SprintBacklog_Sprint_Project_idProject = 1 "
                              "ORDER BY User.FirstName; ");
            }
            else
            {
                query.prepare("SELECT "
                              "   User.idUser, "
                              "   User.FirstName, "
                              "   User.LastName, "
                              "   TaskSB.Title, "
                              "   TaskSB.Priority, "
                              "   TaskSB.Status, "
                              "   UserStorySB.Title, "
                              "   UserStorySB.Priority, "
                              "   UserStorySB.Status, "
                              "   User.Username "
                              "FROM "
                              "   User "
                              "LEFT JOIN "
                              "   TaskSB ON User.idUser = TaskSB.Assignee "
                              "   AND TaskSB.SprintBacklog_Sprint_Project_idProject = 1 "
                              "   AND TaskSB.SprintBacklog_Sprint_idSprint = :sprintId "
                              "LEFT JOIN "
                              "   UserStorySB ON User.idUser = UserStorySB.Assignee "
                              "   AND UserStorySB.SprintBacklog_Sprint_Project_idProject = 1 " // value to replace with :projectId
                              "   AND UserStorySB.SprintBacklog_Sprint_idSprint = :sprintId "
                              "ORDER BY User.FirstName; ");

                query.bindValue(":sprintId", selectedSprintId);

            }

            query.bindValue(":projectId", PassedProjectID);

            QMap<QString, QTreeWidgetItem*> userItemMap;

            if (query.exec()) {
                while (query.next()) {
                    int idUser = query.value(0).toInt();
                    QString firstName = query.value(1).toString();
                    QString lastName = query.value(2).toString();
                    QString taskTitle = query.value(3).toString();
                    QString taskPriority = query.value(4).toString();
                    QString taskStatus = query.value(5).toString();
                    QString storyTitle = query.value(6).toString();
                    QString storyPriority = query.value(7).toString();
                    QString storyStatus = query.value(8).toString();
                    QString username = query.value(9).toString();
                    // qDebug() << "TASKBOARD: firstName: " << firstName;
                    // qDebug() << "TASKBOARD: lastName: " << lastName;
                    // qDebug() << "TASKBOARD: taskTitle: " << taskTitle;
                    // qDebug() << "TASKBOARD: taskPriority: " << taskPriority;
                    // qDebug() << "TASKBOARD: taskStatus: " << taskStatus;

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

                    // // Find or create treeUserItem in the QTreeWidget
                    // QTreeWidgetItem* treeUserItem = userItemMap.value(name);

                    // qDebug() << "TASKBOARD: idUser: " << name << " = " << idUser;

                    // if (!addedUserIds.contains(idUser)) {
                    //     parentBoard->getInputAssigneeT()->addItem(name, QVariant(idUser));
                    //     addedUserIds.insert(idUser);  // Add the user ID to the set
                    // }

                    // if (!treeUserItem) {
                    //     treeUserItem = new QTreeWidgetItem(parentBoard->getTaskTreeWidget());
                    //     treeUserItem->setText(0, name);
                    //     // treeUserItem->setData(0, Qt::UserRole, "username");
                    //     userItemMap.insert(name, treeUserItem);
                    // }

                    // Add task for the current user
                    if (!taskTitle.isEmpty()) {
                        QTreeWidgetItem* treeTaskItem = new QTreeWidgetItem(treeUserItem);
                        // QListWidget::setItemWidget(treeUserItem, editButtonT);
                        treeTaskItem->setText(1, taskTitle);
                        treeTaskItem->setText(2, taskPriority);
                        treeTaskItem->setText(3, "Task");
                        // treeTaskItem->setData(0, Qt::UserRole, "task");
                        treeTaskItem->setText(4, taskStatus);
                    }

                    // Add user story for the current user
                    if (!storyTitle.isEmpty()) {
                        QTreeWidgetItem* treeStoryItem = new QTreeWidgetItem(treeUserItem);
                        treeStoryItem->setText(1, storyTitle);
                        treeStoryItem->setText(2, storyPriority);
                        treeStoryItem->setText(3, "User Story");
                        // treeStoryItem->setData(0, Qt::UserRole, "userstory");
                        treeStoryItem->setText(4, storyStatus);
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
                          "   TaskSB.Title, "
                          "   TaskSB.Priority, "
                          "   TaskSB.Status, "
                          "   UserStorySB.Title, "
                          "   UserStorySB.Priority, "
                          "   UserStorySB.Status "
                          "FROM "
                          "   TaskSB, UserStorySB "
                          "WHERE "
                          "   TaskSB.Assignee IS NULL AND UserStorySB.Assignee IS NULL "
                          "   AND TaskSB.SprintBacklog_Sprint_Project_idProject = 1 "
                          "ORDER BY TaskSB.Title");
        }
        else
        {
            query.prepare("SELECT "
                          "   TaskSB.Title, "
                          "   TaskSB.Priority, "
                          "   TaskSB.Status, "
                          "   UserStorySB.Title, "
                          "   UserStorySB.Priority, "
                          "   UserStorySB.Status "
                          "FROM "
                          "   TaskSB, UserStorySB "
                          "WHERE "
                          "   TaskSB.Assignee IS NULL AND UserStorySB.Assignee IS NULL "
                          "   AND TaskSB.SprintBacklog_Sprint_Project_idProject = 1 "
                          "   AND TaskSB.SprintBacklog_Sprint_idSprint = :sprintId "
                          "ORDER BY TaskSB.Title");

            query.bindValue(":sprintId", selectedSprintId);
        }

        query.bindValue(":projectId", PassedProjectID);

        if (query.exec()) {
            while (query.next()) {
                QString taskTitle = query.value(0).toString();
                QString taskPriority = query.value(1).toString();
                QString taskStatus = query.value(2).toString();
                QString storyTitle = query.value(3).toString();
                QString storyPriority = query.value(4).toString();
                QString storyStatus = query.value(5).toString();

                // Add task for unassigned
                if (!taskTitle.isEmpty()) {
                    QTreeWidgetItem* treeTaskItem = new QTreeWidgetItem(unassignedItem);
                    treeTaskItem->setText(1, taskTitle);
                    treeTaskItem->setText(2, taskPriority);
                    treeTaskItem->setText(3, "Task");
                    treeTaskItem->setText(4, taskStatus);
                }

                // Add user story for unassigned
                if (!storyTitle.isEmpty()) {
                    QTreeWidgetItem* treeStoryItem = new QTreeWidgetItem(unassignedItem);
                    treeStoryItem->setText(1, storyTitle);
                    treeStoryItem->setText(2, storyPriority);
                    treeStoryItem->setText(3, "User Story");
                    treeStoryItem->setText(4, storyStatus);
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
            parentBoard->updateSprintDateLabel("-");
        }
        else
        {
            query.prepare("SELECT StartDate, EndDate FROM Sprint "
                          "WHERE  Project_idProject = 1 "
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
    parentBoard->getCreate_PriorityT()->setVisible(false);
    parentBoard->getCreate_StatusT()->setVisible(false);
    parentBoard->getCreate_TitleT()->setVisible(false);

    parentBoard->getInputAssigneeT()->setVisible(false);
    parentBoard->getInputDescriptionT()->setVisible(false);
    parentBoard->getInputPriorityT()->setVisible(false);
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
void pb_taskboard_implemenation::showCreateTaskTaskboard()
{

    parentBoard->getCreationBoxT()->setVisible(true);

    parentBoard->getCreate_HeaderT()->setVisible(true);

    parentBoard->getCreate_AssigneeT()->setVisible(true);
    parentBoard->getCreate_DescriptionT()->setVisible(true);
    parentBoard->getCreate_PriorityT()->setVisible(true);
    parentBoard->getCreate_StatusT()->setVisible(true);
    parentBoard->getCreate_TitleT()->setVisible(true);

    parentBoard->getInputAssigneeT()->setVisible(true);
    parentBoard->getInputDescriptionT()->setVisible(true);
    parentBoard->getInputPriorityT()->setVisible(true);
    parentBoard->getInputStatusT()->setVisible(true);
    parentBoard->getInputTitleT()->setVisible(true);

    parentBoard->getButton_CreateUserStoryT()->setVisible(false);
    parentBoard->getButton_CreateTaskT()->setVisible(true);

    parentBoard->get_BL_SprintDropDownT()->setVisible(true);
    parentBoard->get_SelectedSprintT()->setVisible(true);

    QTextBrowser* Create_HeaderT = parentBoard->getCreate_HeaderT();
    Create_HeaderT->setAlignment(Qt::AlignCenter);  // Align text to center
    Create_HeaderT->setHtml("<html><head/><body><p style='font-size:14pt; text-align:center; color:black; font-weight:bold; line-height:normal;'>USER TASK</p></body></html>");

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
    parentBoard->getCreate_PriorityT()->setVisible(true);
    parentBoard->getCreate_StatusT()->setVisible(true);
    parentBoard->getCreate_TitleT()->setVisible(true);

    parentBoard->getInputAssigneeT()->setVisible(true);
    parentBoard->getInputDescriptionT()->setVisible(true);
    parentBoard->getInputPriorityT()->setVisible(true);
    parentBoard->getInputStatusT()->setVisible(true);
    parentBoard->getInputTitleT()->setVisible(true);

    parentBoard->getButton_CreateUserStoryT()->setVisible(true);
    parentBoard->getButton_CreateTaskT()->setVisible(false);

    parentBoard->get_BL_SprintDropDownT()->setVisible(true);
    parentBoard->get_SelectedSprintT()->setVisible(true);

    QTextBrowser* Create_HeaderT = parentBoard->getCreate_HeaderT();
    Create_HeaderT->setAlignment(Qt::AlignCenter);  // Align text to center
    Create_HeaderT->setHtml("<html><head/><body><p style='font-size:14pt; text-align:center; color:black; font-weight:bold; line-height:normal;'>USER STORY</p></body></html>");

}

/**
 * @brief Deletes the selected Task/UserStory.
 * Both implementations are inside this function to reduce computing.
 */
void pb_taskboard_implemenation::deleteItemTaskboard(){

    // Delete Task
    if (parentBoard->getButton_CreateTaskT()->isVisible() == true)
    {

    }

    // Delete UserStory
    if (parentBoard->getButton_CreateUserStoryT()->isVisible() == true)
    {

    }
}

void pb_taskboard_implemenation::createNewTaskTaskboard()
{
    qDebug() << "TASKBOARD: Create User Story Taskboard button clicked.";

    //QTextEdit* inputAssignee = parentBoard->getInputAssignee();
    QTextEdit* inputDescriptionTt = parentBoard->getInputDescriptionT();
    QComboBox* inputPriorityTt = parentBoard->getInputPriorityT();
    QTextEdit* inputStatusTt = parentBoard->getInputStatusT();
    QTextEdit* inputTitleTt = parentBoard->getInputTitleT();
    QComboBox* currentSprintTt = parentBoard->get_BL_SprintDropDownT();
    QComboBox* inputAssigneeTt = parentBoard->getInputAssigneeT();

    QString titleT = inputTitleTt->toPlainText();
    QString descriptionT = inputDescriptionTt->toPlainText();
    int priorityT = inputPriorityTt->currentData().toInt();
    QString statusT = inputStatusTt->toPlainText();
    int assigneeT = inputAssigneeTt->currentData().toInt();
    QString sprintT = currentSprintTt->currentText();

    qDebug() << "TASKBOARD: Input Values:";
    qDebug() << "TASKBOARD: titleT" << titleT;
    qDebug() << "TASKBOARD: descriptionT" << descriptionT;
    qDebug() << "TASKBOARD: priorityT"  << priorityT;
    qDebug() << "TASKBOARD: statusT" << statusT;
    qDebug() << "TASKBOARD: assignee" << assigneeT;
    qDebug() << "TASKBOARD: sprintT" << sprintT;

    if (titleT.isEmpty() || descriptionT.isEmpty() || priorityT == -1 || sprintT == "Select Sprint") {
        // One or more fields are empty
        QString errorMessage = "Missing Values:\n";

        if (titleT.isEmpty()) {
            errorMessage += "- Title\n";
        }
        if (descriptionT.isEmpty()) {
            errorMessage += "- Description\n";
        }
        if (priorityT == -1) {
            errorMessage += "- Priority\n";
        }
        if (sprintT == "Select Sprint") {
            errorMessage += "- Sprint\n";
        }

        QMessageBox::warning(nullptr, "Missing Values", errorMessage);
    }
    else
    {
        addToTableTaskboard(titleT, descriptionT, statusT, priorityT, assigneeT, sprintT);
    }
}

void pb_taskboard_implemenation::createNewUserStoryTaskboard()
{
    qDebug() << "TASKBOARD: Create User Story Taskboard button clicked.";

    //QTextEdit* inputAssignee = parentBoard->getInputAssignee();
    QTextEdit* inputDescriptionTus = parentBoard->getInputDescriptionT();
    QComboBox* inputPriorityTus = parentBoard->getInputPriorityT();
    QTextEdit* inputStatusTus = parentBoard->getInputStatusT();
    QTextEdit* inputTitleTus = parentBoard->getInputTitleT();
    QComboBox* currentSprintTus = parentBoard->get_BL_SprintDropDownT();
    QComboBox* inputAssigneeTus = parentBoard->getInputAssigneeT();

    QString titleT = inputTitleTus->toPlainText();
    QString descriptionT = inputDescriptionTus->toPlainText();
    int priorityT = inputPriorityTus->currentData().toInt();
    QString statusT = inputStatusTus->toPlainText();
    int assigneeT = inputAssigneeTus->currentData().toInt();
    QString sprintT = currentSprintTus->currentText();

    qDebug() << "TASKBOARD: Input Values:";
    qDebug() << "TASKBOARD: titleT" << titleT;
    qDebug() << "TASKBOARD: descriptionT" << descriptionT;
    qDebug() << "TASKBOARD: priorityT"  << priorityT;
    qDebug() << "TASKBOARD: statusT" << statusT;
    qDebug() << "TASKBOARD: assignee" << assigneeT;
    qDebug() << "TASKBOARD: sprintT" << sprintT;

    if (titleT.isEmpty() || descriptionT.isEmpty() || priorityT == -1 || sprintT == "Select Sprint") {
        // One or more fields are empty
        QString errorMessage = "Missing Values:\n";

        if (titleT.isEmpty()) {
            errorMessage += "- Title\n";
        }
        if (descriptionT.isEmpty()) {
            errorMessage += "- Description\n";
        }
        if (priorityT == -1) {
            errorMessage += "- Priority\n";
        }
        if (sprintT == "Select Sprint") {
            errorMessage += "- Sprint\n";
        }

        QMessageBox::warning(nullptr, "Missing Values", errorMessage);
    }
    else
    {
        addToTableTaskboard(titleT, descriptionT, statusT, priorityT, assigneeT, sprintT);
    }
}

void pb_taskboard_implemenation::addToTableTaskboard(const QString& title, const QString& description, const QString& status, int priority, int assignee, const QString& sprint)
{
    qDebug() << "TASKBOARD: addToTableTaskboard Function is called";
    HideShow_CreateSectionTaskboard();
    generateUserTaskTree();

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
