#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QDebug> // Include qDebug for debugging
#include <QTableView>
#include "databasemanager.h"
#include "pb_productbacklog_implementation.h"
#include "pb_productbacklog_implementation_extension.h"
#include "qheaderview.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include <QRegularExpression>
#include <QFont>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QMessageBox>
#include "email_notification.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
/**
 * @brief Constructor for pb_productbacklog_implementation.
 * Initializes the necessary variables and sets up the user stories table and its connections.
 *
 * @param parentBoardInstance Pointer to the parent board instance.
 */
pb_productbacklog_implementation::pb_productbacklog_implementation(parentboard* parentBoardInstance) {
    // Initialize any necessary variables or connections
    parentBoard = parentBoardInstance;
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    // userStoriesTable->setGeometry(20, 55, 1250, 500);

    QHeaderView* headerView = userStoriesTable->horizontalHeader();
    connect(headerView, SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked(int)));
    parentBoard->getCreationBox()->setVisible(false);
}
/**
 * @brief Clears the contents of the user stories table and the sprint combo box.
 */
void pb_productbacklog_implementation::clearUserStoriesTable() {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    QComboBox* SprintComboBox = parentBoard->get_BL_SprintDropDown();
    userStoriesTable->clearContents();
    userStoriesTable->setRowCount(0);
    SprintComboBox->clear();
    //QComboBox* SprintBox = parentBoard->getSprintComboBox();
    //SprintBox->clear();
}
/**
 * @brief Retrieves and displays the backlog in the user stories table.
 * This function first clears the table, then fetches and displays the tasks and user stories.
 */
void pb_productbacklog_implementation::RetrieveAndDisplayBacklog() {
    qDebug() <<"RetrieveAndDisplayBacklog Called";
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    // userStoriesTable->setGeometry(20, 55, 1250, 500);
    parentBoard->getCreationBox()->setVisible(false);
    if (userStoriesTable) {
        userStoriesTable->blockSignals(true); // Block signals
        Hide_CreateSection();
        clearUserStoriesTable(); // Clears the table before adding new entries
        TaskPBretrieval(); // Retrieves tasks and adds them to the table
        UserStoryPBretrieval();
        BL_fetechSprints();
        // SendTasksToSprints();
        userStoriesTable->blockSignals(false); // Unblock signals
    }
}
/**
 * @brief Hides the create section UI elements.
 * This includes various input fields and buttons related to creating new user stories or tasks.
 */
void pb_productbacklog_implementation::Hide_CreateSection(){

    /*
    QPushButton* buttonCreate = parentBoard->getButton_Create();
    QTextBrowser* createAssignee = parentBoard->getCreate_Assignee();
    QTextBrowser* createDescription = parentBoard->getCreate_Description();
    QTextBrowser* createHeader = parentBoard->getCreate_Header();
    QTextBrowser* createPriority = parentBoard->getCreate_Priority();
    QTextBrowser* createStatus = parentBoard->getCreate_Status();
    QTextBrowser* createTitle = parentBoard->getCreate_Title();

    QTextEdit* inputAssignee = parentBoard->getInputAssignee();
    QTextEdit* inputDescription = parentBoard->getInputDescription();
    QTextEdit* inputPriority = parentBoard->getInputPriority();
    QTextEdit* inputStatus = parentBoard->getInputStatus();
    QTextEdit* inputTitle = parentBoard->getInputTitle();
*/
    parentBoard->getCreate_Assignee()->setVisible(false);
    parentBoard->getCreate_Description()->setVisible(false);
    parentBoard->getCreate_Header()->setVisible(false);
    parentBoard->getCreate_Priority()->setVisible(false);
    parentBoard->getCreate_Status()->setVisible(false);
    parentBoard->getCreate_Title()->setVisible(false);

    parentBoard->getInputAssignee()->setVisible(false);
    parentBoard->getInputDescription()->setVisible(false);
    parentBoard->getInputPriority()->setVisible(false);
    parentBoard->getInputStatus()->setVisible(false);
    parentBoard->getInputTitle()->setVisible(false);
    parentBoard->getButton_CreateUserStory()->setVisible(false);
    parentBoard->getButton_CreateTask()->setVisible(false);

    parentBoard->get_BL_SprintDropDown()->setVisible(false);
    parentBoard->get_SelecteSprint()->setVisible(false);

}
/**
 * @brief Shows the create section for adding new user stories or tasks.
 * Makes the relevant UI elements visible and sets up the layout.
 */
void pb_productbacklog_implementation::Show_CreateSection(){
    parentBoard->getCreationBox()->setVisible(true);
    parentBoard->getCreate_Assignee()->setVisible(true);
    parentBoard->getCreate_Description()->setVisible(true);
    parentBoard->getCreate_Header()->setVisible(true);
    parentBoard->getCreate_Priority()->setVisible(true);
    parentBoard->getCreate_Status()->setVisible(true);
    parentBoard->getCreate_Title()->setVisible(true);
    parentBoard->getInputAssignee()->setVisible(true);
    parentBoard->getInputDescription()->setVisible(true);
    parentBoard->getInputPriority()->setVisible(true);
    parentBoard->getInputStatus()->setVisible(true);
    parentBoard->getInputTitle()->setVisible(true);
    parentBoard->get_BL_SprintDropDown()->setVisible(true);
    parentBoard->get_SelecteSprint()->setVisible(true);


}
/**
 * @brief Shows the create section specifically for creating user stories.
 * Adjusts the UI layout and makes relevant elements visible for user story creation.
 */
void pb_productbacklog_implementation::Show_CreateSection_UserStory(){

    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    // userStoriesTable->setGeometry(20, 55, 750, 500);

    parentBoard->getCreationBox()->setVisible(true);
    parentBoard->getButton_CreateUserStory()->setVisible(true);
    parentBoard->getButton_CreateTask()->setVisible(false);

    parentBoard->get_BL_SprintDropDown()->setVisible(false);
    parentBoard->get_SelecteSprint()->setVisible(false);

    QTextBrowser* Create_Header = parentBoard->getCreate_Header();
    Create_Header->setAlignment(Qt::AlignCenter);  // Align text to center
    Create_Header->setHtml("<html><head/><body><p style='font-size:14pt; text-align:center; color:white;'>Create User Story</p></body></html>");

}
/**
 * @brief Shows the create section specifically for creating tasks.
 * Adjusts the UI layout and makes relevant elements visible for task creation.
 */
void pb_productbacklog_implementation::Show_CreateSection_Tasks(){

    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    // userStoriesTable->setGeometry(20, 55, 750, 500);
    parentBoard->getCreationBox()->setVisible(true);
    parentBoard->getButton_CreateUserStory()->setVisible(false);
    parentBoard->getButton_CreateTask()->setVisible(true);
    parentBoard->get_BL_SprintDropDown()->setVisible(true);
    parentBoard->get_SelecteSprint()->setVisible(true);
    QTextBrowser* Create_Header = parentBoard->getCreate_Header();
    Create_Header->setAlignment(Qt::AlignCenter);  // Align text to center
    Create_Header->setHtml("<html><head/><body><p style='font-size:14pt; text-align:center; color:white;'>Create Task</p></body></html>");

}



//------------------------------------------------------------------------------------------------------------------------------
//FULL IMPLEMENTATION OF CREATION OF TASK AND EDIT FUCNTIONALITY    -----    START
//------------------------------------------------------------------------------------------------------------------------------


void pb_productbacklog_implementation::TaskPBretrieval() {
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    int PassedProjectID = parentBoard->getProjectId();
    qDebug() << "Project ID in Product Backlog: " << PassedProjectID;

    if (dbobj.isOpen()) {
        // First, retrieve the sprint titles.
        QStringList sprintTitles;
        QSqlQuery sprintQuery(dbobj);
        sprintQuery.prepare("SELECT Title FROM Sprint WHERE Project_idProject = :projectID");
        sprintQuery.bindValue(":projectID", PassedProjectID);
        if (sprintQuery.exec()) {
            while (sprintQuery.next()) {
                sprintTitles << sprintQuery.value(0).toString();
            }
        } else {
            qDebug() << "Failed to retrieve sprints: " << sprintQuery.lastError().text();
        }


        // Retrieve assignees from the database
        QStringList assigneeList;
        QSqlQuery queryUser(dbobj);
        queryUser.prepare("SELECT User.Username "
                          "FROM Project "
                          "INNER JOIN Project_has_User ON Project.idProject = Project_has_User.Project_idProject "
                          "INNER JOIN User ON Project_has_User.User_idUser = User.idUser "
                          "WHERE Project_has_User.Project_idProject = :projectID");
        queryUser.bindValue(":projectID", PassedProjectID);
        if (queryUser.exec()) {
            while (queryUser.next()) {
                assigneeList << queryUser.value(0).toString();
            }
        } else {
            qDebug() << "Error executing query:" << queryUser.lastError().text();
        }

        // Now retrieve the tasks.
        QSqlQuery taskQuery(dbobj);
        taskQuery.prepare("SELECT idTaskPB, Title, Description, Status, Assignee, Priority, ProductBacklog_idProductBacklog, ProductBacklog_Project_idProject, AssignedSprint FROM scrummy.TaskPB WHERE ProductBacklog_Project_idProject = :projectID");
        taskQuery.bindValue(":projectID", PassedProjectID);

        if (taskQuery.exec()) {
            qDebug() << "Tasks Retrieved Successfully!";
            while (taskQuery.next()) {
                int taskID = taskQuery.value(0).toInt();
                qDebug() << "Retrieved Task ID:" << taskID;
                QString title = taskQuery.value(1).toString();
                QString description = taskQuery.value(2).toString();
                QString status = taskQuery.value(3).toString();
                QString assignee = taskQuery.value(4).toString();
                int priority = taskQuery.value(5).toInt();
                QString assignedSprint = taskQuery.value(8).toString(); // This assumes AssignedSprint is the ninth column

                // Include sprintTitles as the last argument
                Tasks_Added_In_Table("Task", title, description, status, assignee, priority, taskID, sprintTitles, assignedSprint, assigneeList);

                // Store additional information in taskMap, if necessary
                taskMap[taskID] = {title, description, status, assignee, priority, taskID};
            }
        } else {
            qDebug() << "Failed to retrieve tasks: " << taskQuery.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - pb_productbacklog_implementation class! - Task";
    }
}


void pb_productbacklog_implementation::Tasks_Added_In_Table(const QString& type_pb, const QString& taskName, const QString& description, const QString& status, QString assignee, int priority, int taskID, const QStringList& sprintTitles, const QString& assignedSprint, const QStringList& assigneeList) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    if (!userStoriesTable) {
        qDebug() << "Table view not found or accessible.";
        return;
    }

    userStoriesTable->setColumnCount(8); // Include an additional column for Task ID
    userStoriesTable->setHorizontalHeaderLabels({"ID", "Type", "Title", "Description", "Status", "Assignee", "Priority", "Sprint"});
    userStoriesTable->setColumnHidden(0, true);

    QHeaderView* header = userStoriesTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    int rowCount = userStoriesTable->rowCount();
    userStoriesTable->insertRow(rowCount);

    QTableWidgetItem* itemTaskID = new QTableWidgetItem();
    itemTaskID->setData(Qt::UserRole, QVariant(taskID));
    itemTaskID->setText(QString::number(taskID));
    userStoriesTable->setItem(rowCount, 0, itemTaskID);

    QTableWidgetItem* type = new QTableWidgetItem(type_pb);
    type->setFlags(type->flags() & ~Qt::ItemIsEditable);
    userStoriesTable->setItem(rowCount, 1, type);

    QTableWidgetItem* itemTaskName = new QTableWidgetItem(taskName);
    userStoriesTable->setItem(rowCount, 2, itemTaskName);

    QTableWidgetItem* itemDescription = new QTableWidgetItem(description);
    userStoriesTable->setItem(rowCount, 3, itemDescription);

    QComboBox* statusComboBox = new QComboBox();
    statusComboBox->addItems({"To Do", "In Progress", "Blocked", "Done"});
    // Set the stylesheet for the QComboBox directly
    statusComboBox->setStyleSheet(
        "QComboBox {"
        "    color: black;"
        "    combobox-popup: 0;"
        "    background-color: white;"
        "    border: none;"
        "}"
        "QComboBox::drop-down {"
        "    subcontrol-origin: padding;"
        "    subcontrol-position: top right;"
        "    width: 20px;"
        "    color: black;"
        "    border: 4px solid white;"
        "}"
        "QComboBox::up-arrow:open {"
        "    image: url(:/down-arrow.png);"
        "    width: 20px;"
        "    height: 20px;"
        "    border-radius: 4px;"
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    border: none;"
        "}"
        "QComboBox::down-arrow:closed {"
        "    image: url(:/up-arrow.png);"
        "    width: 20px;"
        "    height: 20px;"
        "    border-radius: 4px;"
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "    background-color: white;"
        "    color: black;"
        "    border: 1px solid white;"
        "    border-radius: 4px;"
        "    bottom: -1px;"
        "    margin-top: 1px;"
        "}"
        "QComboBox QAbstractItemView::item {"
        "    height: 25px;"
        "    padding: 3px 10px;"
        "    border-radius: 4px;"
        "}"
        "QComboBox QAbstractItemView::item:selected {"
        "    background-color: #D5FEFF;"
        "    color: black;"
        "    border-radius: 4px;"
        "}");
    statusComboBox->setCurrentText(status);
    userStoriesTable->setCellWidget(rowCount, 4, statusComboBox);
    connect(statusComboBox, &QComboBox::currentTextChanged,
            [this, taskID](const QString &newStatus) {
                onStatusChanged(taskID, newStatus);
            });



    QComboBox* assigneeComboBox = new QComboBox();
    // Set the stylesheet for the QComboBox directly
    assigneeComboBox->setStyleSheet(
        "QComboBox {"
        "    color: black;"
        "    combobox-popup: 0;"
        "    background-color: white;"
        "    border: none;"
        "}"
        "QComboBox::drop-down {"
        "    subcontrol-origin: padding;"
        "    subcontrol-position: top right;"
        "    width: 20px;"
        "    color: black;"
        "    border: 4px solid white;"
        "}"
        "QComboBox::up-arrow:open {"
        "    image: url(:/down-arrow.png);"
        "    width: 20px;"
        "    height: 20px;"
        "    border-radius: 4px;"
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    border: none;"
        "}"
        "QComboBox::down-arrow:closed {"
        "    image: url(:/up-arrow.png);"
        "    width: 20px;"
        "    height: 20px;"
        "    border-radius: 4px;"
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "    background-color: white;"
        "    color: black;"
        "    border: 1px solid white;"
        "    border-radius: 4px;"
        "    bottom: -1px;"
        "    margin-top: 1px;"
        "}"
        "QComboBox QAbstractItemView::item {"
        "    height: 25px;"
        "    padding: 3px 10px;"
        "    border-radius: 4px;"
        "}"
        "QComboBox QAbstractItemView::item:selected {"
        "    background-color: #D5FEFF;"
        "    color: black;"
        "    border-radius: 4px;"
        "}");
    assigneeComboBox->addItems(assigneeList);
    assigneeComboBox->setCurrentText(assignee); // Set the current assignee
    userStoriesTable->setCellWidget(rowCount, 5, assigneeComboBox);

    // Connect the ComboBox signal to a slot
    connect(assigneeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this, taskID, assigneeComboBox](int index) {
                QString newAssignee = assigneeComboBox->currentText();
                onTaskAssigneeChanged(taskID, newAssignee);
            });

    QComboBox* itemPriority1 = new QComboBox();
    // Set the stylesheet for the QComboBox directly
    itemPriority1->setStyleSheet(
        "QComboBox {"
        "    color: black;"
        "    combobox-popup: 0;"
        "    background-color: white;"
        "    border: none;"
        "}"
        "QComboBox::drop-down {"
        "    subcontrol-origin: padding;"
        "    subcontrol-position: top right;"
        "    width: 20px;"
        "    color: black;"
        "    border: 4px solid white;"
        "}"
        "QComboBox::up-arrow:open {"
        "    image: url(:/down-arrow.png);"
        "    width: 20px;"
        "    height: 20px;"
        "    border-radius: 4px;"
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    border: none;"
        "}"
        "QComboBox::down-arrow:closed {"
        "    image: url(:/up-arrow.png);"
        "    width: 20px;"
        "    height: 20px;"
        "    border-radius: 4px;"
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "    background-color: white;"
        "    color: black;"
        "    border: 1px solid white;"
        "    border-radius: 4px;"
        "    bottom: -1px;"
        "    margin-top: 1px;"
        "}"
        "QComboBox QAbstractItemView::item {"
        "    height: 25px;"
        "    padding: 3px 10px;"
        "    border-radius: 4px;"
        "}"
        "QComboBox QAbstractItemView::item:selected {"
        "    background-color: #D5FEFF;"
        "    color: black;"
        "    border-radius: 4px;"
        "}");
    itemPriority1->addItems({"High", "Medium", "Low"});
    itemPriority1->setCurrentText(priorityToString(priority));
    userStoriesTable->setCellWidget(rowCount, 6, itemPriority1);
    connect(itemPriority1, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this, taskID, itemPriority1](int index) {
                QString Priority = itemPriority1->currentText();
                onPriorityChanged(taskID, Priority);
            });




    SprintSelectionComboBox = new QComboBox();
    // Set the stylesheet for the QComboBox directly
    SprintSelectionComboBox->setStyleSheet(
        "QComboBox {"
        "    color: black;"
        "    combobox-popup: 0;"
        "    background-color: white;"
        "    border: none;"
        "}"
        "QComboBox::drop-down {"
        "    subcontrol-origin: padding;"
        "    subcontrol-position: top right;"
        "    width: 20px;"
        "    color: black;"
        "    border: 4px solid white;"
        "}"
        "QComboBox::up-arrow:open {"
        "    image: url(:/down-arrow.png);"
        "    width: 20px;"
        "    height: 20px;"
        "    border-radius: 4px;"
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    border: none;"
        "}"
        "QComboBox::down-arrow:closed {"
        "    image: url(:/up-arrow.png);"
        "    width: 20px;"
        "    height: 20px;"
        "    border-radius: 4px;"
        "    background-repeat: no-repeat;"
        "    background-position: center;"
        "    border: none;"
        "}"
        "QComboBox QAbstractItemView {"
        "    background-color: white;"
        "    color: black;"
        "    border: 1px solid white;"
        "    border-radius: 4px;"
        "    bottom: -1px;"
        "    margin-top: 1px;"
        "}"
        "QComboBox QAbstractItemView::item {"
        "    height: 25px;"
        "    padding: 3px 10px;"
        "    border-radius: 4px;"
        "}"
        "QComboBox QAbstractItemView::item:selected {"
        "    background-color: #D5FEFF;"
        "    color: black;"
        "    border-radius: 4px;"
        "}");
    SprintSelectionComboBox->addItems(sprintTitles);
    // Set the current text of the combo box to the assigned sprint
    if (sprintTitles.contains(assignedSprint)) {
        SprintSelectionComboBox->setCurrentText(assignedSprint);
    } else {
        SprintSelectionComboBox->addItem(assignedSprint);
        SprintSelectionComboBox->setCurrentText(assignedSprint);
    }
    userStoriesTable->setCellWidget(rowCount, 7, SprintSelectionComboBox);

    connect(SprintSelectionComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this, userStoriesTable, rowCount, taskID](int index) {
                QString title = userStoriesTable->item(rowCount, 2)->text();
                QString description = userStoriesTable->item(rowCount, 3)->text();

                // Retrieve the status from the ComboBox in column 4
                QString status;
                QWidget* statusWidget = userStoriesTable->cellWidget(rowCount, 4);
                if (statusWidget) {
                    QComboBox* statusComboBox = qobject_cast<QComboBox*>(statusWidget);
                    if (statusComboBox) {
                        status = statusComboBox->currentText();
                    }
                }

                // Retrieve the assigneeId from the ComboBox in column 5
                QString assigneeId;
                QWidget* assigneeWidget = userStoriesTable->cellWidget(rowCount, 5);
                if (assigneeWidget) {
                    QComboBox* assigneeComboBox = qobject_cast<QComboBox*>(assigneeWidget);
                    if (assigneeComboBox) {
                        assigneeId = assigneeComboBox->currentText();
                    }
                }

                QString priorityString = getStatusFromRow(userStoriesTable, rowCount); // use your function to get the priority string
                int priority = priorityToInt(priorityString); // convert the string to an integer
                QString selectedSprint = qobject_cast<QComboBox *>(userStoriesTable->cellWidget(rowCount, 7))->currentText();
                SendToSprint(taskID, title, description, status, priority, assigneeId, selectedSprint);
            });


}

QString pb_productbacklog_implementation::priorityToString(int priority) {
    switch (priority) {
    case 1: return "High";
    case 2: return "Medium";
    case 3: return "Low";
    default: return "Unknown"; // For any other value that is not 1, 2, or 3
    }
}
int pb_productbacklog_implementation::priorityToInt(QString& priorityString) {
    if (priorityString == "High") return 1;
    if (priorityString == "Medium") return 2;
    if (priorityString == "Low") return 3;
    return -1; // return a default value for unknown priority strings
}


void pb_productbacklog_implementation::SendToSprint(int taskID, const QString& title, const QString& description, const QString& status, int priority, const QString& assigneeId, const QString& selectedSprint){

    //First we need to delete exisiting row from TaskPB in the Table
    deleteTaskFromDatabase(taskID);


    //Then we Add a new Entry in TaskPB
    QTableWidget* table = parentBoard->getUserStoriesTableView(); // Assuming there's a method to get the task table view
    int PassedProjectID = parentBoard->getProjectId();
    QComboBox* SprintComboBox = parentBoard->get_BL_SprintDropDown();
    QString selectedValue = SprintComboBox->currentText().trimmed(); // Trim to remove any whitespace
    qDebug() << "Project ID in TASKPB - TASKSB: " << PassedProjectID;
    //Getting the assignee value from the database
    if (!table) {
        qDebug() << "Task table view not found or accessible.";
        return;
    }
    DatabaseManager database1;
    QSqlDatabase dbobj12 = database1.getDatabase();
    if (!dbobj12.isOpen()) {
        qDebug() << "Connection Not Established - pb_productbacklog_implmentation!";
        return;
    }
    //-----------------Taking the Correct ProductBacklog ID--------------------
    QSqlQuery querySelect(dbobj12);
    querySelect.prepare("SELECT PB.idProductBacklog "
                        "FROM Project AS P "
                        "INNER JOIN ProductBacklog AS PB ON P.idProject = PB.Project_idProject "
                        "WHERE P.idProject = :projectId");
    querySelect.bindValue(":projectId", PassedProjectID);

    int productBacklogId = 0;
    if (querySelect.exec()) {
        if (querySelect.next()) {
            productBacklogId = querySelect.value(0).toInt();
        }
    } else {
        qDebug() << "Failed to retrieve ProductBacklog ID:" << querySelect.lastError().text();
        return;
    }
    QSqlDatabase TaskPB = database.getDatabase();
    QSqlQuery query(TaskPB);
    query.prepare("INSERT INTO scrummy.TaskPB(Title, Description, Status, Priority, Assignee, ProductBacklog_idProductBacklog, ProductBacklog_Project_idProject, AssignedSprint) "
                  "VALUES (:title, :description, :status, :priority, :assignee, :productBacklogId, :projectId, :assignedSprint)");
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":status", status);
    query.bindValue(":priority", priority);
    query.bindValue(":assignee", assigneeId);
    query.bindValue(":productBacklogId", productBacklogId); // Assuming this value is correctly provided
    query.bindValue(":projectId", PassedProjectID);
    query.bindValue(":assignedSprint", selectedSprint); // Corrected the double colon and misspelling

    if (!query.exec()) {
        qDebug() << "Failed to insert data into TaskPB table:" << query.lastError().text();
        dbobj12.close();
        return;
    }
    qDebug() << "Data inserted into TaskPB table successfully!";
    // Retrieve the auto-incremented idTaskPB from the TaskPB table
    QVariant lastInsertId = query.lastInsertId();
    if (!lastInsertId.isValid()) {
        qDebug() << "Failed to retrieve the last inserted TaskPB ID.";
        dbobj12.close();
        return;
    }
    int SameValueTaskPB = lastInsertId.toInt(); // This will be used for TaskSB

    /*
    //Then we update the Assigned Sprint Column
    //Udpate in the TaskPB-Column "AssignedSprint"
    //Udpate in the TaskPB-Column "AssignedSprint"
    //Udpate in the TaskPB-Column "AssignedSprint"
    DatabaseManager database;
    QSqlDatabase dbobj1 = database.getDatabase();
    QSqlQuery UpdateTaskPB(dbobj1);
    UpdateTaskPB.prepare("UPDATE TaskPB "
                         "SET AssignedSprint = :selectedSprint "
                         "WHERE idTaskPB = :taskID" );
    UpdateTaskPB.bindValue(":selectedSprint", selectedSprint);
    UpdateTaskPB.bindValue(":taskID", SameValueTaskPB);   //Take the new entry
    if (!UpdateTaskPB.exec()) {
        qDebug() << "Update failed:" << UpdateTaskPB.lastError().text();
    } else {
        // If the update affects no rows, it may be because the taskID does not exist.
        if (UpdateTaskPB.numRowsAffected() > 0) {
            qDebug() << "TaskPB updated successfully for taskID" << taskID;
        } else {
            qDebug() << "No rows affected. Check if the taskID exists.";
        }
    }
    //Udpate in the TaskPB-Column "AssignedSprint"
    //Udpate in the TaskPB-Column "AssignedSprint"
    //Udpate in the TaskPB-Column "AssignedSprint"
    */




    //Add Task To a Sprint"
    //Add Task To a Sprint"
    //Add Task To a Sprint"

    QSqlDatabase dbobj = database.getDatabase();
    QString idSprintBacklog;
    QString Sprint_idSprint;
    QString selectedValue1 = selectedSprint;
    qDebug() << "Selected Value from ComboBox: " << selectedValue;


    if (selectedSprint == "Unassigned") {
        qDebug() << "Nothing Happend: " << selectedValue;
    }else{
        deleteTaskFromDatabase(taskID);



        //Take the Correct ID of the Username
        QSqlQuery queryUserId(dbobj);
        queryUserId.prepare("SELECT U.idUser FROM User AS U WHERE U.Username = :username");
        queryUserId.bindValue(":username", assigneeId);

        int userId = -1; // Default value, in case the query fails
        if(queryUserId.exec()) {
            if(queryUserId.next()) {
                userId = queryUserId.value(0).toInt();
                qDebug() << "Fetched User ID: " << userId;
            } else {
                qDebug() << "No user found for username: " << assigneeId;
            }
        } else {
            qDebug() << "Query error while fetching user ID:" << queryUserId.lastError().text();
        }


        QSqlQuery querySprintValues(dbobj);
        querySprintValues.prepare("SELECT SB.idSprintBacklog, SB.Sprint_idSprint "
                                  "FROM SprintBacklog SB "
                                  "INNER JOIN Sprint S ON S.idSprint = SB.Sprint_idSprint "
                                  "WHERE S.Title = :sprintTitle");
        querySprintValues.bindValue(":sprintTitle", selectedValue1); // Binding the selected value

        if(querySprintValues.exec()) {
            if(querySprintValues.next()) {
                idSprintBacklog = querySprintValues.value(0).toString();
                Sprint_idSprint = querySprintValues.value(1).toString();
                qDebug() << "Fetched Values: " << idSprintBacklog << ", " << Sprint_idSprint;
            } else {
                qDebug() << "No data fetched. Check if the query returns any rows.";
            }
        } else {
            qDebug() << "Query error:" << querySprintValues.lastError().text();
        }
        qDebug() << "Executed query:" << querySprintValues.executedQuery();
        //COPY IN THE TASKSB TABLE
        QSqlQuery query1(dbobj);
        query1.prepare("INSERT INTO scrummy.TaskSB(idTask, Title, Description, Status, Priority, Assignee, SprintBacklog_idSprintBacklog, SprintBacklog_Sprint_idSprint, SprintBacklog_Sprint_Project_idProject) "
                       "VALUES (:idTask, :title, :description, :status, :priority, :assignee, :sprintBacklogId, :sprintId, :projectId)");
        query1.bindValue(":idTask", SameValueTaskPB);
        query1.bindValue(":title", title);
        query1.bindValue(":description", description);
        query1.bindValue(":status", status);
        query1.bindValue(":priority", priority);
        query1.bindValue(":assignee", userId);
        query1.bindValue(":sprintBacklogId", idSprintBacklog);
        query1.bindValue(":sprintId", Sprint_idSprint);
        query1.bindValue(":projectId", PassedProjectID);

        if (!query1.exec()) {
            qDebug() << "Failed to insert data into TaskSB table:" << query1.lastError().text();
            dbobj.close();
            return;
        }
        qDebug() << "Data inserted into TaskSB table successfully!";
        dbobj.close();
    }
}


QString pb_productbacklog_implementation::getAssigneeFromRow(QTableWidget* table, int row) {
    QWidget* widget = table->cellWidget(row, 5); // Assuming that assignees are in the 6th column (index 5)
    QComboBox* comboBox = qobject_cast<QComboBox*>(widget);
    if (comboBox) {
        return comboBox->currentText();
    } else {
        qDebug() << "No assignee combo box found at row" << row;
        return QString();
    }
}

QString pb_productbacklog_implementation::getStatusFromRow(QTableWidget* table, int row) {
    QWidget* widget = table->cellWidget(row, 4); // Assuming that status values are in the 5th column (index 4)
    QComboBox* comboBox = qobject_cast<QComboBox*>(widget);
    if (comboBox) {
        return comboBox->currentText();
    } else {
        qDebug() << "No status combo box found at row" << row;
        return QString();
    }
}

void pb_productbacklog_implementation::onPriorityChanged(int taskID, QString& Priority) {

    // Convert the priority string to an int
    int priorityValue = priorityToInt(Priority);

    // Check for valid priorityValue
    if(priorityValue == -1) {
        qDebug() << "Invalid priority string: " << Priority;
        return;
    }

    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    if (!userStoriesTable) return;

    // Find the row for the taskID. This assumes taskID is unique.
    int row = -1;
    for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
        if (userStoriesTable->item(i, 0)->data(Qt::UserRole).toInt() == taskID) {
            row = i;
            break;
        }
    }
    if (row == -1) {
        qDebug() << "Task ID not found in the table: " << taskID;
        return; // Task ID not found
    }

    // Assuming taskMap is a data structure to check for task existence and updateTaskInDatabase is a method to update the task
    if (taskMap.contains(taskID)) {
        QString title = userStoriesTable->item(row, 2)->text();
        QString description = userStoriesTable->item(row, 3)->text();
        QString assignee = getAssigneeFromRow(userStoriesTable, row); // Implement this method or retrieve the text directly
        QString status = getStatusFromRow(userStoriesTable, row); // Implement this method or retrieve the text directly

        // Your method to update the task in the database, including the new priority
        updateTaskInDatabase(taskID, title, description, status, assignee, priorityValue);
    } else {
        qDebug() << "TaskID not found in taskMap";
    }
}



void pb_productbacklog_implementation::onTaskAssigneeChanged(int taskID, const QString& newAssignee) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    if (!userStoriesTable) return;

    int row = -1;
    for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
        if (userStoriesTable->item(i, 0)->data(Qt::UserRole).toInt() == taskID) {
            row = i;
            break;
        }
    }
    if (row == -1) return;

    QString title = userStoriesTable->item(row, 2)->text();
    QString description = userStoriesTable->item(row, 3)->text();

    QString status;
    QWidget* statusWidget = userStoriesTable->cellWidget(row, 4);
    if (statusWidget) {
        QComboBox* statusComboBox = qobject_cast<QComboBox*>(statusWidget);
        if (statusComboBox) {
            status = statusComboBox->currentText();
        }
    }

    int priority = 0;
    QString priorityString;    // Default priority value
    QWidget* priorityWidget = userStoriesTable->cellWidget(row, 6);
    if (priorityWidget) {
        QComboBox* priorityComboBox = qobject_cast<QComboBox*>(priorityWidget);
        if (priorityComboBox) {
            priorityString = priorityComboBox->currentText();
            priority = priorityToInt(priorityString); // Ensure this function handles invalid inputs gracefully
            qDebug() << "Priority" << priority;
        }
    }

    DatabaseManager database1;
    QSqlDatabase onTaskAssigneeChangedConnection = database1.getDatabase();
    QSqlQuery query(onTaskAssigneeChangedConnection);
    query.prepare("UPDATE scrummy.TaskPB SET Assignee = ? WHERE idTaskPB = ?");
    query.addBindValue(newAssignee);
    query.addBindValue(taskID);

    if (!query.exec()) {
        qDebug() << "Update failed for Task ID:" << taskID << " Error:" << query.lastError();
        return; // Add return statement to avoid further processing in case of failure
    } else {
        qDebug() << "Assignee updated successfully for task ID:" << taskID;
    }

    if (taskMap.contains(taskID)) {
        updateTaskInDatabase(taskID, title, description, status, newAssignee, priority);
    } else {
        qDebug() << "TaskID in onTaskAssigneeChanged not found";
        return; // Add return statement if taskID is not found
    }

    QSqlDatabase database2 = QSqlDatabase::database();
    QSqlQuery EmailQuery(database2);
    EmailQuery.prepare("SELECT Email FROM User WHERE Username = :newAssignee");
    EmailQuery.bindValue(":newAssignee", newAssignee);
    QString email;

    if (EmailQuery.exec()) {
        if (EmailQuery.next()) {
            email = EmailQuery.value(0).toString();
            qDebug() << "email:" << email;
        }
    } else {
        qDebug() << "Error executing query:" << EmailQuery.lastError().text();
        return; // Add return statement to handle query error
    }

    QString emailBody = QString(
                            "Task Details: \n"
                            "ID: %1 \n"
                            "Title: %2 \n"
                            "Description: %3 \n"
                            "Status: %4 \n"
                            "Assignee: %5 \n"
                            "Priority: %6 \n"
                            "This is an automated message. Please do not reply directly to this email. \n"
                            )
                            .arg(QString::number(taskID))
                            .arg(title)
                            .arg(description)
                            .arg(status)
                            .arg(newAssignee)
                            .arg(priorityString);

    std::string recipient_email = email.toStdString();
    std::string subject = "Task Assignment Update";
    std::string email_body = emailBody.toStdString();

    qDebug() << "recipient_email: " + recipient_email << taskID;

    Email_Notification emailNotifier;
    bool success = emailNotifier.sendEmail(recipient_email, subject, email_body);

    if (success) {
        qDebug() << "Email sent successfully for task ID";

    } else {
        qDebug() << "Failed to send email for task ID:" << taskID;
    }


    emailNotifier.~Email_Notification();

}

void pb_productbacklog_implementation::onStatusChanged(int taskID, const QString& status) {
    qDebug() << "onStatusChanged called with taskID:" << taskID << " status:" << status;
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    if (!userStoriesTable) return;

    // Find the row for the taskID. This assumes taskID is unique.
    int row = -1;
    for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
        if (userStoriesTable->item(i, 0)->data(Qt::UserRole).toInt() == taskID) {
            row = i;
            break;
        }
    }
    if (row == -1) return; // Task ID not found

    QString title = userStoriesTable->item(row, 2)->text();
    QString description = userStoriesTable->item(row, 3)->text();

    // Retrieve the assignee from the ComboBox in column 5
    QString assignee;
    QWidget* assigneeWidget = userStoriesTable->cellWidget(row, 5);
    if (assigneeWidget) {
        QComboBox* assigneeComboBox = qobject_cast<QComboBox*>(assigneeWidget);
        if (assigneeComboBox) {
            assignee = assigneeComboBox->currentText();
        }
    }
    QString priorityString = getStatusFromRow(userStoriesTable, row); // use your function to get the priority string
    int priority = priorityToInt(priorityString); // convert the string to an integer

    if (taskMap.contains(taskID)) {
        updateTaskInDatabase(taskID, title, description, status, assignee, priority);
    }else{
        qDebug() << "TaskID in onStatusChagned not found";

    }
}



//EDIT FUNCTIONALITY
void pb_productbacklog_implementation::onTableItemChanged(QTableWidgetItem* item) {
    if (!item) {
        qDebug() << "Item is null";
        return;
    }

    int row = item->row();
    int column = item->column();
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();

    if (!userStoriesTable) {
        qDebug() << "User stories table not found";
        return;
    }

    // Debugging information
    qDebug() << "Changed item at row:" << row << "column:" << column << "Value:" << item->text();

    int taskID = userStoriesTable->item(row, 0)->data(Qt::UserRole).toInt();
    qDebug() << "Task ID to update:" << taskID;

    if (!taskMap.contains(taskID)) {
        qDebug() << "Task ID not found in taskMap:" << taskID;
        return;
    }

    QString title = userStoriesTable->item(row, 2)->text();
    QString description = userStoriesTable->item(row, 3)->text();
    QString status;
    QString assignee;
    QString priorityinter;
    int priority;


    // Retrieve status and assignee from their ComboBoxes
    QWidget* statusWidget = userStoriesTable->cellWidget(row, 4);
    QWidget* assigneeWidget = userStoriesTable->cellWidget(row, 5);
    QWidget* priorityString = userStoriesTable->cellWidget(row, 6);

    if(priority == 1){
        priority=1;
    }
    if(priority == 2){
        priority=2;
    }
    if(priority == 3){
        priority=3;
    }
    else{
        qDebug() << "Not Correct Value Priority";
        // Create a QWidget (main window)
        QWidget window;

        // Create a QLabel widget to display text
        QLabel label("Hello, Qt!");

        // Create a layout for the main window
        QVBoxLayout layout;
        layout.addWidget(&label);

        // Set the layout for the main window
        window.setLayout(&layout);

        // Set the window properties
        window.setWindowTitle("Qt Window with Text");
        window.resize(400, 300);

        // Show the window
        window.show();
        priority=1;
    }
    if (statusWidget) {
        QComboBox* statusComboBox = qobject_cast<QComboBox*>(statusWidget);
        if (statusComboBox) {
            status = statusComboBox->currentText();
        }
    }
    if (assigneeWidget) {
        QComboBox* assigneeComboBox = qobject_cast<QComboBox*>(assigneeWidget);
        if (assigneeComboBox) {
            assignee = assigneeComboBox->currentText();
        }
    }

    if (priorityString) {
        QComboBox* priorityStringComboBox = qobject_cast<QComboBox*>(priorityString);
        if (priorityStringComboBox) {
            priorityinter = priorityStringComboBox->currentText();
            priority = priorityToInt(priorityinter); // Ensure this function handles invalid inputs gracefully
            //COMEHERE
        }
    }

    // Update the task in the database
    updateTaskInDatabase(taskID, title, description, status, assignee, priority);
}




void pb_productbacklog_implementation::updateTaskInDatabase(int taskID, const QString& title, const QString& description, const QString& status, QString assignee, int priority) {

    qDebug() << "updateTaskInDatabase Function has been called";


    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open";
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE scrummy.TaskPB SET Title = ?, Description = ?, Status = ?, Assignee = ?, Priority = ? WHERE idTaskPB = ?");
    query.addBindValue(title);
    query.addBindValue(description);
    query.addBindValue(status);
    query.addBindValue(assignee);
    query.addBindValue(priority);
    query.addBindValue(taskID);

    if (!query.exec()) {
        qDebug() << "Update failed: " << query.lastError();
    } else {
        qDebug() << "Update successful for task ID:" << taskID;
    }

    //Taking the correct ID of the UserName
    QSqlQuery query3;
    query3.prepare("SELECT U.idUser FROM User AS U WHERE U.Username = :username");
    query3.bindValue(":username", assignee);

    int userId = -1; // Default value, in case the query fails
    if(query3.exec()) {
        if(query3.next()) {
            userId = query3.value(0).toInt();
            qDebug() << "Fetched User ID: " << userId;
        } else {
            qDebug() << "No user found for username: " << assignee;
        }
    } else {
        qDebug() << "Query error while fetching user ID:" << query3.lastError().text();
    }

    qDebug() << "Status:" << status;
    qDebug() << "Assignee:" << userId;

    //Update TaskSB at the Same time
    QSqlQuery query2;
    query2.prepare("UPDATE scrummy.TaskSB SET Title = ?, Description = ?, Status = ?, Assignee = ?, Priority = ? WHERE idTask = ?");
    query2.addBindValue(title);
    query2.addBindValue(description);
    query2.addBindValue(status);
    query2.addBindValue(userId);
    query2.addBindValue(priority);
    query2.addBindValue(taskID);

    if (!query2.exec()) {
        qDebug() << "Update failed: " << query2.lastError();
    } else {
        qDebug() << "Update successful for task ID:" << taskID;
    }
}


// Slot to handle row deletion when a row is clicked
void pb_productbacklog_implementation::onRowClicked(QTableWidgetItem* item) {
    if (!item) {
        qDebug() << "Item is null";
        return;
    }

    int row = item->row();
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();

    if (!userStoriesTable) {
        qDebug() << "User stories table not found";
        return;
    }

    // Retrieve the task ID associated with the clicked row
    int taskID = userStoriesTable->item(row, 0)->data(Qt::UserRole).toInt();

    // Remove the row from the table
    userStoriesTable->removeRow(row);

    // Call a function to delete the task from the database
    deleteTaskFromDatabase(taskID);
}

// Function to delete a task from the database
void pb_productbacklog_implementation::deleteTaskFromDatabase(int taskID) {
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open";
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM scrummy.TaskPB WHERE idTaskPB = ?");
    query.addBindValue(taskID);

    if (!query.exec()) {
        qDebug() << "Delete failed: " << query.lastError();
    } else {
        qDebug() << "Delete successful for task ID:" << taskID;
    }

    //Also Gets Deleted in
    QSqlQuery query1;
    query.prepare("DELETE FROM scrummy.TaskSB WHERE idTask = ?");
    query.addBindValue(taskID);

    if (!query.exec()) {
        qDebug() << "Delete failed: " << query.lastError();
    } else {
        qDebug() << "Delete successful for task ID:" << taskID;
    }
}




//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//Creation of Tasks  - - - - - - - - - - - - - - - - - - - - NEW WINDOW ON THE RIGHT
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------


void pb_productbacklog_implementation::onButtonIssueClicked() {
    //QComboBox* inputAssignee = parentBoard->getInputAssignee();
    QTextEdit* inputDescription = parentBoard->getInputDescription();
    QTextEdit* inputPriority = parentBoard->getInputPriority();
    QTextEdit* inputStatus = parentBoard->getInputStatus();
    QTextEdit* inputTitle = parentBoard->getInputTitle();
    QString title = inputTitle->toPlainText();
    QString description = inputDescription->toPlainText();
    QString priorityText = inputPriority->toPlainText();
    int priority = priorityText.toInt();
    QString status = inputStatus->toPlainText();
    QComboBox* SprintDropDown = parentBoard->get_BL_SprintDropDown();
    QComboBox* InputAssignee = parentBoard->getInputAssignee();
    // To get the currently selected text from the combo boxes
    QString Pass_sprint = SprintDropDown->currentText();
    QString assignee = InputAssignee->currentText();
    if (title.isEmpty() || description.isEmpty() || priorityText.isEmpty() || status.isEmpty()) {
        // One or more fields are empty
        QMessageBox::warning(nullptr, "Missing Values", "Please fill in all fields.");
    } else {
        addTaskToBacklog(title, description, status, priority, assignee, Pass_sprint);
    }
}





void pb_productbacklog_implementation::addTaskToBacklog(const QString& title, const QString& description, const QString& status, int priority, QString assignee, QString SelectedSprint) {
    /*
     *
     * // Adding the task in the TaskPB
     *
    */

    QTableWidget* table = parentBoard->getUserStoriesTableView(); // Assuming there's a method to get the task table view
    int PassedProjectID = parentBoard->getProjectId();
    QComboBox* SprintComboBox = parentBoard->get_BL_SprintDropDown();
    QString selectedValue = SprintComboBox->currentText().trimmed(); // Trim to remove any whitespace
    qDebug() << "Project ID in TASKPB - TASKSB: " << PassedProjectID;
    //Getting the assignee value from the database
    if (!table) {
        qDebug() << "Task table view not found or accessible.";
        return;
    }
    table->setColumnCount(8);
    table->setHorizontalHeaderLabels({"ID", "Title", "Description", "Status", "Assignee", "Priority", "ProductBacklog ID", "Sprint"});
    QHeaderView* header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();
    if (!dbobj.isOpen()) {
        qDebug() << "Connection Not Established - pb_productbacklog_implmentation!";
        return;
    }
    //-----------------Taking the Correct ProductBacklog ID--------------------
    QSqlQuery querySelect(dbobj);
    querySelect.prepare("SELECT PB.idProductBacklog "
                        "FROM Project AS P "
                        "INNER JOIN ProductBacklog AS PB ON P.idProject = PB.Project_idProject "
                        "WHERE P.idProject = :projectId");
    querySelect.bindValue(":projectId", PassedProjectID);

    int productBacklogId = 0;
    if (querySelect.exec()) {
        if (querySelect.next()) {
            productBacklogId = querySelect.value(0).toInt();
        }
    } else {
        qDebug() << "Failed to retrieve ProductBacklog ID:" << querySelect.lastError().text();
        return;
    }
    QSqlQuery query(dbobj);
    query.prepare("INSERT INTO scrummy.TaskPB(Title, Description, Status, Priority, Assignee, ProductBacklog_idProductBacklog, ProductBacklog_Project_idProject, AssignedSprint) "
                  "VALUES (:title, :description, :status, :priority, :assignee, :productBacklogId, :projectId, :assignedSprint)");
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":status", status);
    query.bindValue(":priority", priority);
    query.bindValue(":assignee", assignee);
    query.bindValue(":productBacklogId", productBacklogId); // Assuming this value is correctly provided
    query.bindValue(":projectId", PassedProjectID);
    query.bindValue(":assignedSprint", selectedValue); // Corrected the double colon and misspelling

    if (!query.exec()) {
        qDebug() << "Failed to insert data into TaskPB table:" << query.lastError().text();
        dbobj.close();
        return;
    }
    //We need to get the Same Value of the Primary key of this table to store in TaskSB, where we are now able to make a relation mannually
    QVariant lastInsertId = query.lastInsertId();
    if (!lastInsertId.isValid()) {
        qDebug() << "Failed to retrieve the last inserted TaskPB ID.";
        dbobj.close();
        return;
    }
    int SameValueTaskPB = lastInsertId.toInt(); // This will be used for TaskSB

    qDebug() << "Data inserted into TaskPB table successfully!";








    /*
     *
     * // Condition to either add in TaskSB or skip it)
     *
    */







    if (SelectedSprint == "Unassigned" ) {
        goto ONLYTASKPB_END;
    } else {
        //-----------------START-----------------------------Copy Of the Task in the Sprint Table
        QSqlQuery queryUser(dbobj);
        queryUser.prepare("SELECT idUser FROM User WHERE Username = :username");
        queryUser.bindValue(":username", assignee);

        int assigneeId = 0;
        if (queryUser.exec()) {
            if (queryUser.next()) {
                assigneeId = queryUser.value(0).toInt(); // Assuming the first column is the user ID
            }
        } else {
            qDebug() << "Failed to retrieve user ID:" << queryUser.lastError().text();
            return;
        }
        //TAKE THE CORRECT VALUES FROM THE SPRINT BACKLOG TABLE
        /*
    */
        QString idSprintBacklog;
        QString Sprint_idSprint;
        QComboBox* SprintComboBox = parentBoard->get_BL_SprintDropDown();
        QString selectedValue = SprintComboBox->currentText().trimmed(); // Trim to remove any whitespace
        qDebug() << "Selected Value from ComboBox: " << selectedValue;

        QSqlQuery querySprintValues(dbobj);
        querySprintValues.prepare("SELECT SB.idSprintBacklog, SB.Sprint_idSprint "
                                  "FROM SprintBacklog SB "
                                  "INNER JOIN Sprint S ON S.idSprint = SB.Sprint_idSprint "
                                  "WHERE S.Title = :sprintTitle");
        querySprintValues.bindValue(":sprintTitle", selectedValue); // Binding the selected value

        if(querySprintValues.exec()) {
            if(querySprintValues.next()) {
                idSprintBacklog = querySprintValues.value(0).toString();
                Sprint_idSprint = querySprintValues.value(1).toString();
                qDebug() << "Fetched Values: " << idSprintBacklog << ", " << Sprint_idSprint;
            } else {
                qDebug() << "No data fetched. Check if the query returns any rows.";
            }
        } else {
            qDebug() << "Query error:" << querySprintValues.lastError().text();
        }

        qDebug() << "Executed query:" << querySprintValues.executedQuery();
        //COPY IN THE TASKSB TABLE
        QSqlQuery query1(dbobj);
        query1.prepare("INSERT INTO scrummy.TaskSB(idTask, Title, Description, Status, Priority, Assignee, SprintBacklog_idSprintBacklog, SprintBacklog_Sprint_idSprint, SprintBacklog_Sprint_Project_idProject) "
                       "VALUES (:idTask, :title, :description, :status, :priority, :assignee, :sprintBacklogId, :sprintId, :projectId)");
        query1.bindValue(":idTask", SameValueTaskPB);
        query1.bindValue(":title", title);
        query1.bindValue(":description", description);
        query1.bindValue(":status", status);
        query1.bindValue(":priority", priority);
        query1.bindValue(":assignee", assigneeId); // Assuming 'assignee' is a variable holding the assignee's ID
        query1.bindValue(":sprintBacklogId", idSprintBacklog); // Assuming this is a constant or should be obtained dynamically
        query1.bindValue(":sprintId", Sprint_idSprint); // Assuming SelectedSprint is a variable holding the sprint ID
        query1.bindValue(":projectId", PassedProjectID); // Assuming PassedProjectID is a variable holding the project ID

        if (!query1.exec()) {
            qDebug() << "Failed to insert data into TaskSB table:" << query1.lastError().text();
            dbobj.close();
            return;
        }
        qDebug() << "Data inserted into TaskSB table successfully!";
        dbobj.close();
    }
    //-----------------END-----------------------------Copy Of the Task in the Sprint Table



ONLYTASKPB_END:
    int rowCount = table->rowCount();
    table->insertRow(rowCount);

    QTableWidgetItem* itemID = new QTableWidgetItem(query.lastInsertId().toString()); // Assuming auto-increment ID
    QTableWidgetItem* itemTitle = new QTableWidgetItem(title);
    QTableWidgetItem* itemDescription = new QTableWidgetItem(description);
    QTableWidgetItem* itemStatus = new QTableWidgetItem(status);
    QTableWidgetItem* itemPriority = new QTableWidgetItem(QString::number(priority));
    QTableWidgetItem* itemAssignee = new QTableWidgetItem(assignee);

    itemID->setFlags(itemID->flags() & ~Qt::ItemIsEditable);

    table->setItem(rowCount, 0, itemID);
    table->setItem(rowCount, 1, itemTitle);
    table->setItem(rowCount, 2, itemDescription);
    table->setItem(rowCount, 3, itemStatus);
    table->setItem(rowCount, 4, itemPriority);
    table->setItem(rowCount, 5, itemAssignee);

    RetrieveAndDisplayBacklog();
}




//------------------------------------------------------------------------------------------------------------------------------
//FULL IMPLEMENTATION OF CREATION OF TASK AND EDIT FUCNTIONALITY    -----    END
//------------------------------------------------------------------------------------------------------------------------------












//------------------------------------------------------------------------------------------------------------------------------












//------------------------------------------------------------------------------------------------------------------------------
//FULL IMPLEMENTATION OF CREATION OF USER-STORIES AND EDIT FUCNTIONALITY    -----    START
//------------------------------------------------------------------------------------------------------------------------------



void pb_productbacklog_implementation::UserStoryPBretrieval() {
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    int PassedProjectID = parentBoard->getProjectId();

    if (dbobj.isOpen()) {
        QSqlQuery query(dbobj);
        query.prepare("SELECT idUserStoryPB, Title, Description, Status, Priority, Assignee, AssignedSprint FROM scrummy.UserStoryPB WHERE ProductBacklog_Project_idProject = :projectID");
        query.bindValue(":projectID", PassedProjectID);

        if (query.exec()) {
            qDebug() << "User Stories Retrieved Successfully!";
            while (query.next()) {
                int storyID = query.value(0).toInt();
                QString title = query.value(1).toString();
                QString description = query.value(2).toString();
                QString status = query.value(3).toString();
                int priority = query.value(4).toInt();
                int assignee = query.value(5).toInt();
                /*
                qDebug() << "Retrieved User Story ID:" << storyID
                         << " Title:" << title
                         << " Description:" << description
                         << " Status:" << status
                         << " Priority:" << priority
                         << " Assignee:" << assignee;
                */
                QString assignedSprint = query.value(6).toString(); // Assuming 'AssignedSprint' is the 7th column

                QStringList sprintTitles;
                QSqlQuery sprintQuery(dbobj);
                sprintQuery.prepare("SELECT Title FROM Sprint WHERE Project_idProject = :projectID");
                sprintQuery.bindValue(":projectID", PassedProjectID);
                if (sprintQuery.exec()) {
                    while (sprintQuery.next()) {
                        sprintTitles << sprintQuery.value(0).toString();
                    }
                } else {
                    qDebug() << "Failed to retrieve sprints: " << sprintQuery.lastError().text();
                }


                QComboBox* priorityComboBox = new QComboBox();
                // Set the stylesheet for the QComboBox directly
                priorityComboBox->setStyleSheet(
                    "QComboBox {"
                    "    color: black;"
                    "    combobox-popup: 0;"
                    "    background-color: white;"
                    "    border: none;"
                    "}"
                    "QComboBox::drop-down {"
                    "    subcontrol-origin: padding;"
                    "    subcontrol-position: top right;"
                    "    width: 20px;"
                    "    color: black;"
                    "    border: 4px solid white;"
                    "}"
                    "QComboBox::up-arrow:open {"
                    "    image: url(:/down-arrow.png);"
                    "    width: 20px;"
                    "    height: 20px;"
                    "    border-radius: 4px;"
                    "    background-repeat: no-repeat;"
                    "    background-position: center;"
                    "    border: none;"
                    "}"
                    "QComboBox::down-arrow:closed {"
                    "    image: url(:/up-arrow.png);"
                    "    width: 20px;"
                    "    height: 20px;"
                    "    border-radius: 4px;"
                    "    background-repeat: no-repeat;"
                    "    background-position: center;"
                    "    border: none;"
                    "}"
                    "QComboBox QAbstractItemView {"
                    "    background-color: white;"
                    "    color: black;"
                    "    border: 1px solid white;"
                    "    border-radius: 4px;"
                    "    bottom: -1px;"
                    "    margin-top: 1px;"
                    "}"
                    "QComboBox QAbstractItemView::item {"
                    "    height: 25px;"
                    "    padding: 3px 10px;"
                    "    border-radius: 4px;"
                    "}"
                    "QComboBox QAbstractItemView::item:selected {"
                    "    background-color: #D5FEFF;"
                    "    color: black;"
                    "    border-radius: 4px;"
                    "}");
                priorityComboBox->addItems({"High", "Medium", "Low"});
                int priorityValue = query.value(4).toInt();
                priorityComboBox->setCurrentIndex(priorityValue - 1);  // Assuming 1 = High, 2 = Medium, 3 = Low

                UserStories_Added_In_Table("User Story", title, description, status, assignee, priorityComboBox, storyID, assignedSprint, sprintTitles);
                storyMap[storyID] = {title, description, status, priority, assignee, storyID};
            }
        } else {
            qDebug() << "Failed to retrieve data: " << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - pb_productbacklog_implementation class! - User Story";
    }
}

void pb_productbacklog_implementation::UserStories_Added_In_Table(const QString& type_pb, const QString& storyName, const QString& description, const QString& status, int assignee, QComboBox* priorityComboBox, int storyID, const QString& assignedSprint, const QStringList& sprintTitles) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    userStoriesTable->setColumnCount(8);
    userStoriesTable->setHorizontalHeaderLabels({"ID", "Type", "Title", "Description", "Status", "Assignee", "Priority", "Sprint"});
    userStoriesTable->setColumnHidden(0, true);
    //userStoriesTable->setColumnHidden(6, true);
    QHeaderView* header = userStoriesTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    if (userStoriesTable) {
        int rowCount = userStoriesTable->rowCount();
        userStoriesTable->insertRow(rowCount);

        QTableWidgetItem* itemStoryID = new QTableWidgetItem(QString::number(storyID));
        itemStoryID->setData(Qt::UserRole, QVariant(storyID));
        userStoriesTable->setItem(rowCount, 0, itemStoryID);

        QTableWidgetItem* type = new QTableWidgetItem(type_pb);
        QTableWidgetItem* itemStoryName = new QTableWidgetItem(storyName);
        QTableWidgetItem* itemDescription = new QTableWidgetItem(description);
        //QTableWidgetItem* itemStatus = new QTableWidgetItem(status);
        //QTableWidgetItem* itemPriority = new QTableWidgetItem(QString::number(priority));
        QTableWidgetItem* itemAssignee = new QTableWidgetItem(QString::number(assignee));

        type->setFlags(type->flags() & ~Qt::ItemIsEditable);
        itemStoryID->setFlags(itemStoryID->flags() & ~Qt::ItemIsEditable);

        userStoriesTable->setItem(rowCount, 1, type);
        userStoriesTable->setItem(rowCount, 2, itemStoryName);
        userStoriesTable->setItem(rowCount, 3, itemDescription);


        QComboBox* statusComboBox = new QComboBox();
        // Set the stylesheet for the QComboBox directly
        statusComboBox->setStyleSheet(
            "QComboBox {"
            "    color: black;"
            "    combobox-popup: 0;"
            "    background-color: white;"
            "    border: none;"
            "}"
            "QComboBox::drop-down {"
            "    subcontrol-origin: padding;"
            "    subcontrol-position: top right;"
            "    width: 20px;"
            "    color: black;"
            "    border: 4px solid white;"
            "}"
            "QComboBox::up-arrow:open {"
            "    image: url(:/down-arrow.png);"
            "    width: 20px;"
            "    height: 20px;"
            "    border-radius: 4px;"
            "    background-repeat: no-repeat;"
            "    background-position: center;"
            "    border: none;"
            "}"
            "QComboBox::down-arrow:closed {"
            "    image: url(:/up-arrow.png);"
            "    width: 20px;"
            "    height: 20px;"
            "    border-radius: 4px;"
            "    background-repeat: no-repeat;"
            "    background-position: center;"
            "    border: none;"
            "}"
            "QComboBox QAbstractItemView {"
            "    background-color: white;"
            "    color: black;"
            "    border: 1px solid white;"
            "    border-radius: 4px;"
            "    bottom: -1px;"
            "    margin-top: 1px;"
            "}"
            "QComboBox QAbstractItemView::item {"
            "    height: 25px;"
            "    padding: 3px 10px;"
            "    border-radius: 4px;"
            "}"
            "QComboBox QAbstractItemView::item:selected {"
            "    background-color: #D5FEFF;"
            "    color: black;"
            "    border-radius: 4px;"
            "}");
        statusComboBox->addItems({"To Do", "In Progress", "Blocked", "Done"});
        statusComboBox->setCurrentText(status);
        userStoriesTable->setCellWidget(rowCount, 4, statusComboBox);

        // Correct the connection to use the overload of currentIndexChanged that passes the current text
        connect(statusComboBox, &QComboBox::currentTextChanged,
                [this, storyID, statusComboBox](const QString &newStatus) {
                    // Since storyID is captured by value, it is the correct ID for the row
                    onUserStoryStatusChanged(storyID, newStatus);
                });

        //userStoriesTable->setItem(rowCount, 5, itemPriority);


        userStoriesTable->setCellWidget(rowCount, 6, priorityComboBox);
        connect(priorityComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                [this, storyID, priorityComboBox](int index) {
                    int newPriority = priorityComboBox->currentIndex() + 1;
                    onUserStoryPriorityChanged(storyID, newPriority);
                });





        int PassedProjectID = parentBoard->getProjectId();



        //COME HERE
        QStringList assigneeList;
        QSqlDatabase db = QSqlDatabase::database();
        QSqlQuery assigneeQuery(db);


        assigneeQuery.prepare("SELECT User.Username "
                              "FROM Project "
                              "INNER JOIN Project_has_User ON Project.idProject = Project_has_User.Project_idProject "
                              "INNER JOIN User ON Project_has_User.User_idUser = User.idUser "
                              "WHERE Project_has_User.Project_idProject = :projectID");
        assigneeQuery.bindValue(":projectID", PassedProjectID);
        if (assigneeQuery.exec()) {
            while (assigneeQuery.next()) {
                assigneeList << assigneeQuery.value(0).toString();
            }
        } else {
            qDebug() << "Error executing assignee query:" << assigneeQuery.lastError().text();
        }

        // Create and set up the assignee combo box
        QComboBox* assigneeComboBox = new QComboBox();
        // Set the stylesheet for the QComboBox directly
        assigneeComboBox->setStyleSheet(
            "QComboBox {"
            "    color: black;"
            "    combobox-popup: 0;"
            "    background-color: white;"
            "    border: none;"
            "}"
            "QComboBox::drop-down {"
            "    subcontrol-origin: padding;"
            "    subcontrol-position: top right;"
            "    width: 20px;"
            "    color: black;"
            "    border: 4px solid white;"
            "}"
            "QComboBox::up-arrow:open {"
            "    image: url(:/down-arrow.png);"
            "    width: 20px;"
            "    height: 20px;"
            "    border-radius: 4px;"
            "    background-repeat: no-repeat;"
            "    background-position: center;"
            "    border: none;"
            "}"
            "QComboBox::down-arrow:closed {"
            "    image: url(:/up-arrow.png);"
            "    width: 20px;"
            "    height: 20px;"
            "    border-radius: 4px;"
            "    background-repeat: no-repeat;"
            "    background-position: center;"
            "    border: none;"
            "}"
            "QComboBox QAbstractItemView {"
            "    background-color: white;"
            "    color: black;"
            "    border: 1px solid white;"
            "    border-radius: 4px;"
            "    bottom: -1px;"
            "    margin-top: 1px;"
            "}"
            "QComboBox QAbstractItemView::item {"
            "    height: 25px;"
            "    padding: 3px 10px;"
            "    border-radius: 4px;"
            "}"
            "QComboBox QAbstractItemView::item:selected {"
            "    background-color: #D5FEFF;"
            "    color: black;"
            "    border-radius: 4px;"
            "}");
        assigneeComboBox->addItems(assigneeList);
        QString currentAssignee = fetchAssigneeNameById(assignee); // Use 'assignee' instead of 'assigneeId'
        assigneeComboBox->setCurrentText(currentAssignee);
        userStoriesTable->setCellWidget(rowCount, 5, assigneeComboBox);

        // Connect the ComboBox signal to a slot
        connect(assigneeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                [this, storyID, assigneeComboBox](int index) {
                    QString newAssignee = assigneeComboBox->currentText();
                    onUserStoryAssigneeChanged(storyID, newAssignee); // Ensure this method is declared and defined
                });





        QComboBox* sprintComboBox = new QComboBox();
        // Set the stylesheet for the QComboBox directly
        sprintComboBox->setStyleSheet(
            "QComboBox {"
            "    color: black;"
            "    combobox-popup: 0;"
            "    background-color: white;"
            "    border: none;"
            "}"
            "QComboBox::drop-down {"
            "    subcontrol-origin: padding;"
            "    subcontrol-position: top right;"
            "    width: 20px;"
            "    color: black;"
            "    border: 4px solid white;"
            "}"
            "QComboBox::up-arrow:open {"
            "    image: url(:/down-arrow.png);"
            "    width: 20px;"
            "    height: 20px;"
            "    border-radius: 4px;"
            "    background-repeat: no-repeat;"
            "    background-position: center;"
            "    border: none;"
            "}"
            "QComboBox::down-arrow:closed {"
            "    image: url(:/up-arrow.png);"
            "    width: 20px;"
            "    height: 20px;"
            "    border-radius: 4px;"
            "    background-repeat: no-repeat;"
            "    background-position: center;"
            "    border: none;"
            "}"
            "QComboBox QAbstractItemView {"
            "    background-color: white;"
            "    color: black;"
            "    border: 1px solid white;"
            "    border-radius: 4px;"
            "    bottom: -1px;"
            "    margin-top: 1px;"
            "}"
            "QComboBox QAbstractItemView::item {"
            "    height: 25px;"
            "    padding: 3px 10px;"
            "    border-radius: 4px;"
            "}"
            "QComboBox QAbstractItemView::item:selected {"
            "    background-color: #D5FEFF;"
            "    color: black;"
            "    border-radius: 4px;"
            "}");
        sprintComboBox->addItems(sprintTitles); // Use sprintTitles instead of hardcoded values
        sprintComboBox->setCurrentText(assignedSprint);
        userStoriesTable->setCellWidget(rowCount, 7, sprintComboBox);


        pb_productbacklog_implementation_Extension *pbbacklogextensionobj = new pb_productbacklog_implementation_Extension(parentBoard);
        connect(sprintComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                [this, userStoriesTable, rowCount, storyID, pbbacklogextensionobj](int index) {
                    QString title = userStoriesTable->item(rowCount, 2)->text();
                    QString description = userStoriesTable->item(rowCount, 3)->text();

                    // Retrieve the status from the ComboBox in column 4
                    QString status;
                    QWidget* statusWidget = userStoriesTable->cellWidget(rowCount, 4);
                    if (statusWidget) {
                        QComboBox* statusComboBox = qobject_cast<QComboBox*>(statusWidget);
                        if (statusComboBox) {
                            status = statusComboBox->currentText();
                        }
                    }

                    // Retrieve the assigneeId from the ComboBox in column 5
                    QString assigneeId;
                    QWidget* assigneeWidget = userStoriesTable->cellWidget(rowCount, 5);
                    if (assigneeWidget) {
                        QComboBox* assigneeComboBox = qobject_cast<QComboBox*>(assigneeWidget);
                        if (assigneeComboBox) {
                            assigneeId = assigneeComboBox->currentText();
                        }
                    }

                    QString priorityString = getStatusFromRow(userStoriesTable, rowCount); // use your function to get the priority string
                    int priority = priorityToInt(priorityString); // convert the string to an integer
                    QString selectedSprint = qobject_cast<QComboBox *>(userStoriesTable->cellWidget(rowCount, 7))->currentText();



                    pbbacklogextensionobj->Send_UserStory_ToSprint(storyID, title, description, status, priority, assigneeId, selectedSprint);
                });


        /*

        connect(sprintComboBox, &QComboBox::currentTextChanged,
                [this, storyID, sprintComboBox](const QString &newSprint) {
                    onUserStorySprintChanged(storyID, newSprint);
                });

        qDebug() << "Adding User Story to Table: ID:" << storyID
                 << " Title:" << storyName
                 << " Description:" << description
                 << " Status:" << status
                 << " Priority:" << priority
                 << " Assignee:" << assignee;
        */
    } else {
        qDebug() << "Table view not found or accessible.";
    }
}


void pb_productbacklog_implementation::onUserStoryAssigneeChanged(int storyID, const QString& newAssignee) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    if (!userStoriesTable) return;

    int row = -1;
    for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
        if (userStoriesTable->item(i, 0)->data(Qt::UserRole).toInt() == storyID) {
            row = i;
            break;
        }
    }

    if (row == -1) {
        qDebug() << "Story ID not found in the table: " << storyID;
        return;
    }

    QString title = userStoriesTable->item(row, 2)->text();
    QString description = userStoriesTable->item(row, 3)->text();
    QString status = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 4))->currentText();
    int priority = 0;
    QWidget* priorityWidget = userStoriesTable->cellWidget(row, 6);
    if (priorityWidget) {
        QComboBox* priorityComboBox = qobject_cast<QComboBox*>(priorityWidget);
        if (priorityComboBox) {
            priority = priorityComboBox->currentIndex() + 1;
        }
    }
    QString assignedSprint = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 7))->currentText();

    int newAssigneeId = fetchAssigneeIdByName(newAssignee); // Convert assignee name to ID

    updateUserStoryInDatabase(storyID, title, description, status, priority, newAssigneeId, assignedSprint);
}

int pb_productbacklog_implementation::fetchAssigneeIdByName(const QString& assigneeName) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return -1; // Return -1 or an appropriate error code
    }

    QSqlQuery query(db);
    query.prepare("SELECT idUser FROM User WHERE Username = :assigneeName");
    query.bindValue(":assigneeName", assigneeName);

    if (!query.exec()) {
        qDebug() << "Query failed: " << query.lastError();
        return -1; // Return -1 or an appropriate error code
    }

    if (query.next()) {
        return query.value(0).toInt(); // Return the user ID
    } else {
        qDebug() << "No user found for name:" << assigneeName;
        return -1; // Return -1 or an appropriate error code
    }
}


QString pb_productbacklog_implementation::fetchAssigneeNameById(int assigneeId) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return QString(); // Return an empty string if the database is not open
    }

    QSqlQuery query(db);
    query.prepare("SELECT Username FROM User WHERE idUser = :assigneeId");
    query.bindValue(":assigneeId", assigneeId);

    if (!query.exec()) {
        qDebug() << "Query failed: " << query.lastError();
        return QString(); // Return an empty string if the query fails
    }

    if (query.next()) {
        return query.value(0).toString(); // Return the username
    } else {
        qDebug() << "No user found for ID:" << assigneeId;
        return QString(); // Return an empty string if no user is found
    }
}

void pb_productbacklog_implementation::onUserStoryPriorityChanged(int storyID, int newPriority) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    if (!userStoriesTable) return;

    int row = -1;
    for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
        if (userStoriesTable->item(i, 0)->data(Qt::UserRole).toInt() == storyID) {
            row = i;
            break;
        }
    }
    if (row == -1) return;

    QString title = userStoriesTable->item(row, 2)->text();
    QString description = userStoriesTable->item(row, 3)->text();
    QString status = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 4))->currentText();
    QString assigneeName = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 5))->currentText();
    QString assignedSprint = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 7))->currentText();
    int assigneeId = fetchAssigneeIdByName(assigneeName);

    updateUserStoryInDatabase(storyID, title, description, status, newPriority, assigneeId, assignedSprint);
}


void pb_productbacklog_implementation::onUserStorySprintChanged(int storyID, const QString& newSprint) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    if (!userStoriesTable) return;

    int row = -1;
    for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
        if (userStoriesTable->item(i, 0)->data(Qt::UserRole).toInt() == storyID) {
            row = i;
            break;
        }
    }
    if (row == -1) return;

    QString title = userStoriesTable->item(row, 2)->text();
    QString description = userStoriesTable->item(row, 3)->text();
    QString status = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 4))->currentText();
    QString assigneeName = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 5))->currentText();
    int priority = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 6))->currentIndex() + 1;
    int assigneeId = fetchAssigneeIdByName(assigneeName);

    updateUserStoryInDatabase(storyID, title, description, status, priority, assigneeId, newSprint);
}


void pb_productbacklog_implementation::onUserStoryStatusChanged(int storyID, const QString& newStatus) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    if (!userStoriesTable) return;

    int row = -1;
    for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
        if (userStoriesTable->item(i, 0)->data(Qt::UserRole).toInt() == storyID) {
            row = i;
            break;
        }
    }
    if (row == -1) return;

    QString title = userStoriesTable->item(row, 2)->text();
    QString description = userStoriesTable->item(row, 3)->text();
    QString assigneeName = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 5))->currentText();
    int priority = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 6))->currentIndex() + 1;
    QString assignedSprint = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 7))->currentText();
    int assigneeId = fetchAssigneeIdByName(assigneeName);

    updateUserStoryInDatabase(storyID, title, description, newStatus, priority, assigneeId, assignedSprint);
}



void pb_productbacklog_implementation::updateUserStoryInDatabase(int storyID, const QString& title, const QString& description, const QString& status, int priority, int assigneeId, const QString& assignedSprint) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE scrummy.UserStoryPB SET Title = ?, Description = ?, Status = ?, Priority = ?, Assignee = ?, AssignedSprint = ? WHERE idUserStoryPB = ?");
    query.addBindValue(title);
    query.addBindValue(description);
    query.addBindValue(status);
    query.addBindValue(priority);
    query.addBindValue(assigneeId);
    query.addBindValue(assignedSprint);
    query.addBindValue(storyID);

    if (!query.exec()) {
        qDebug() << "Update failed for User Story ID:" << storyID << " Error:" << query.lastError();
    } else {
        qDebug() << "Update successful for user story ID:" << storyID;
    }


    QSqlQuery query1(db);
    query1.prepare("UPDATE scrummy.UserStorySB SET Title = ?, Description = ?, Status = ?, Priority = ?, Assignee = ?, SprintBacklog_idSprintBacklog = ? WHERE idUserStorySB = ?");
    query1.addBindValue(title);
    query1.addBindValue(description);
    query1.addBindValue(status);
    query1.addBindValue(priority);
    query1.addBindValue(assigneeId);
    query1.addBindValue(assignedSprint);
    query1.addBindValue(storyID);

    if (!query1.exec()) {
        qDebug() << "Update failed for User Story ID:" << storyID << " Error:" << query1.lastError();
    } else {
        qDebug() << "Update successful for user story ID:" << storyID;
    }




}


void pb_productbacklog_implementation::onUserStoryTableItemChanged(QTableWidgetItem* item) {
    if (!item) {
        qDebug() << "Item is null";
        return;
    }

    int row = item->row();
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();

    if (!userStoriesTable) {
        qDebug() << "User stories table not found";
        return;
    }

    int storyID = userStoriesTable->item(row, 0)->data(Qt::UserRole).toInt();

    if (storyMap.contains(storyID)) {
        QString title = userStoriesTable->item(row, 2)->text();
        QString description = userStoriesTable->item(row, 3)->text();
        QString status = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 4))->currentText();

        int priority = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 6))->currentIndex() + 1;

        QString assigneeName = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 5))->currentText();
        int assigneeId = fetchAssigneeIdByName(assigneeName); // Convert assignee name to ID

        QString assignedSprint = qobject_cast<QComboBox*>(userStoriesTable->cellWidget(row, 7))->currentText();

        updateUserStoryInDatabase(storyID, title, description, status, priority, assigneeId, assignedSprint);
    } else {
        qDebug() << "User story ID not found in storyMap. ID:" << storyID;
    }
}





//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//Creation of UserStories
//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------


void pb_productbacklog_implementation::on_createUserStory_clicked() {
    qDebug() << "Create User Story button clicked.";


    //QTextEdit* inputAssignee = parentBoard->getInputAssignee();
    QTextEdit* inputDescription = parentBoard->getInputDescription();
    QTextEdit* inputPriority = parentBoard->getInputPriority();
    QTextEdit* inputStatus = parentBoard->getInputStatus();
    QTextEdit* inputTitle = parentBoard->getInputTitle();

    QString title = inputTitle->toPlainText();
    // QString assignee = inputAssignee->toPlainText();
    QString description = inputDescription->toPlainText();
    QString priorityText = inputPriority->toPlainText();
    int priority = priorityText.toInt();
    QString status = inputStatus->toPlainText();

    if (title.isEmpty() || description.isEmpty() || priorityText.isEmpty()) {
        // One or more fields are empty
        QMessageBox::warning(nullptr, "Missing Values", "Please fill in all fields.");
    } else {
        addUserStoryToBacklog(title, description, status, priority, "assignee");
    }

    /*
    QString title = QInputDialog::getText(nullptr, "Enter Title", "Title:");
    QString description = QInputDialog::getText(nullptr, "Enter Description", "Description:");
    QStringList statuses = {"To Do", "In Progress", "Done"};
    QString status = QInputDialog::getItem(nullptr, "Select Status", "Status:", statuses, 0, false);
    int priority = QInputDialog::getInt(nullptr, "Enter Priority", "Priority:", 1, 1, 5, 1);
    QString assignee = QInputDialog::getText(nullptr, "Enter Assignee", "Assignee:");
    */
}

void pb_productbacklog_implementation::addUserStoryToBacklog(const QString& title, const QString& description, const QString& status, int priority, const QString& assignee) {
    QTableWidget* table = parentBoard->getUserStoriesTableView();
    if (!table) {
        qDebug() << "Table view not found or accessible.";
        return;
    }
    table->setColumnCount(8);
    table->setHorizontalHeaderLabels({"ID", "Type", "Title", "Description", "Status", "Priority", "Assignee", "Sprint"});

    QHeaderView* header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();
    if (!dbobj.isOpen()) {
        qDebug() << "Connection Not Established - pb_productbacklog_implmentation!";
        return;
    }

    QSqlQuery query(dbobj);
    query.prepare("INSERT INTO scrummy.UserStoryPB(Title, Description, Status, Priority, Assignee, ProductBacklog_idProductBacklog, ProductBacklog_Project_idProject)"
                  "VALUES (:title, :description, :status, :priority, :assignee, 1, 1)");
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":status", status);
    query.bindValue(":priority", priority);
    query.bindValue(":assignee", assignee);

    if (!query.exec()) {
        qDebug() << "Failed to insert data into UserStoryPB table:" << query.lastError().text();
        dbobj.close();
        return;
    }
    qDebug() << "Data inserted into UserStoryPB table successfully!";
    dbobj.close();

    int rowCount = table->rowCount();
    table->insertRow(rowCount);

    QTableWidgetItem* itemID = new QTableWidgetItem(query.lastInsertId().toString()); // Assuming auto-increment ID
    QTableWidgetItem* itemTitle = new QTableWidgetItem(title);
    QTableWidgetItem* itemDescription = new QTableWidgetItem(description);
    QTableWidgetItem* itemStatus = new QTableWidgetItem(status);
    QTableWidgetItem* itemPriority = new QTableWidgetItem(QString::number(priority));
    QTableWidgetItem* itemAssignee = new QTableWidgetItem(assignee);

    itemID->setFlags(itemID->flags() & ~Qt::ItemIsEditable);

    table->setItem(rowCount, 0, itemID);
    table->setItem(rowCount, 1, itemTitle);
    table->setItem(rowCount, 2, itemDescription);
    table->setItem(rowCount, 3, itemStatus);
    table->setItem(rowCount, 4, itemPriority);
    table->setItem(rowCount, 5, itemAssignee);

    RetrieveAndDisplayBacklog();
}
//------------------------------------------------------------------------------------------------------------------------------
//FULL IMPLEMENTATION OF CREATION OF USER-STORIES AND EDIT FUCNTIONALITY    -----    END
//------------------------------------------------------------------------------------------------------------------------------









//------------------------------------------------------------------------------------------------------------------------------
//Fetch Spirits and Username - According to the project you are logged in with
//------------------------------------------------------------------------------------------------------------------------------



void pb_productbacklog_implementation::BL_fetechSprints() {
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (!dbobj.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QComboBox* SprintComboBox = parentBoard->get_BL_SprintDropDown();
    QComboBox* InputAssignee = parentBoard->getInputAssignee();
    int PassedProjectID = parentBoard->getProjectId();
    qDebug() << "Project ID in Product Backlog: " << PassedProjectID;

    // Set font size for the combo boxes
    QFont comboBoxFont;
    comboBoxFont.setPointSize(12);
    SprintComboBox->setFont(comboBoxFont);
    InputAssignee->setFont(comboBoxFont);

    // Clear existing items in both combo boxes
    SprintComboBox->clear();
    InputAssignee->clear();
    SprintComboBox->addItem("Unassigned");
    InputAssignee->addItem("Unassigned");

    // Fetch Sprints
    QSqlQuery query(dbobj);
    query.prepare("SELECT Title FROM Sprint WHERE Project_idProject = :projectID");
    query.bindValue(":projectID", PassedProjectID);

    if (!query.exec()) {
        qDebug() << "Sprint query failed: " << query.lastError();
        return;
    }

    if (query.size() == 0) {
        qDebug() << "No sprints found for Project ID: " << PassedProjectID;
        SprintComboBox->addItem("No Sprints Available");
    } else {
        while (query.next()) {
            QString title = query.value(0).toString();
            SprintComboBox->addItem(title);
        }
    }

    // Fetch Assignees
    QSqlQuery query1(dbobj);
    query1.prepare("SELECT User.Username "
                   "FROM Project "
                   "INNER JOIN Project_has_User ON Project.idProject = Project_has_User.Project_idProject "
                   "INNER JOIN User ON Project_has_User.User_idUser = User.idUser "
                   "WHERE Project_has_User.Project_idProject = :projectID");
    query1.bindValue(":projectID", PassedProjectID);

    if (!query1.exec()) {
        qDebug() << "Assignee query failed: " << query1.lastError();
        return;
    }

    if (query1.size() == 0) {
        qDebug() << "No assignees found for Project ID: " << PassedProjectID;
        InputAssignee->addItem("No Assignees Available");
    } else {
        while (query1.next()) {
            QString username = query1.value(0).toString();
            InputAssignee->addItem(username);
        }
    }
}




/**
 * @brief Handles the sorting of a QTableWidget based on the clicked header column.
 *
 * This function sorts the QTableWidget named userStoriesTable based on the clicked header column.
 * If the column clicked is column 6 (assumed to represent "Sprint"), the table is sorted in ascending order.
 * If the column clicked is column 5 (assumed to represent "Assignee"), a custom sort is applied where "Unassigned"
 * items are moved to the top of the sorted list. It temporarily alters the text of "Unassigned" items during sorting
 * by replacing it with a space (' '), ensuring it appears at the beginning, then restores the original text
 * after sorting.
 *
 * @param column The index of the column header that was clicked.
 */
void pb_productbacklog_implementation::onHeaderClicked(int column) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();

    if (column == 6) { // Assuming column 6 is "Sprint"
        userStoriesTable->sortByColumn(column, Qt::DescendingOrder);
    } else if (column == 5) { // Assuming column 5 is "Assignee"
        // Custom sort: "Unassigned" comes first
        for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
            QTableWidgetItem* item = userStoriesTable->item(i, column);
            if (item->text() == "Unassigned") {
                // Set the item's text to something that will come first in the sort
                item->setData(Qt::UserRole, item->text()); // Save the original text
                item->setText(" "); // A space will sort before any other text
            }
        }

        userStoriesTable->sortByColumn(column, Qt::AscendingOrder);

        // Restore the original text after sorting
        for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
            QTableWidgetItem* item = userStoriesTable->item(i, column);
            if (item->data(Qt::UserRole).isValid()) {
                item->setText(item->data(Qt::UserRole).toString());
                item->setData(Qt::UserRole, QVariant()); // Clear the user role data
            }
        }
    }
}






















void pb_productbacklog_implementation::SendTasksToSprints() {
    qDebug() << "SendTasksToSprints called";


    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();


    if (dbobj.isOpen()) {
        QSqlQuery query(dbobj);
        query.prepare("SELECT Title FROM scrummy.Sprint");

        if (query.exec()) {
            qDebug() << "Sprint Data Retrieved Successfully!";

            while (query.next()) {
                QString sprintTitle = query.value(0).toString(); // Assuming Title is in the first column of the result
            }

        } else {
            qDebug() << "Failed to retrieve Sprint Data : " << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - pb_productbacklog_implementation class - ! - Sprint Data";
    }

}
