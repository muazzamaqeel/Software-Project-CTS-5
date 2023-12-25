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
#include <QRegularExpression>
#include "TableAnimator.h"
//Fetch the Sprints from the Sprint table
#include <QFont>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QMessageBox>

pb_productbacklog_implementation::pb_productbacklog_implementation(parentboard* parentBoardInstance) {
    // Initialize any necessary variables or connections
    parentBoard = parentBoardInstance;
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    userStoriesTable->setStyleSheet(
        "QTableWidget {"
        "    background-color: #f5f5f5;"  // Lighter gray background
        "    border: 1px solid #e0e0e0;"  // Light gray border
        "    gridline-color: #d0d0d0;"    // Gridline color
        "}"
        "QTableWidget::item {"
        "    padding: 4px;"  // Increased padding for table cells
        "    border-bottom: 1px solid #e0e0e0;"  // Bottom border for cells
        "}"
        "QTableWidget::item:selected {"
        "    background-color: #cce6ff;"  // Light blue background for selected cells
        "}"
        "QHeaderView::section {"
        "    background-color: #333333;"  // Dark gray header background
        "    color: white;"  // White text in headers
        "    padding: 2px;"  // Padding for header sections
        "    border-top: 1px solid #666666;"  // Top border for headers
        "}"
        "QHeaderView::section:checked {" // Styling for checked headers (if applicable)
        "    background-color: #007acc;" // Example color for checked headers
        "}"
        );

    TableAnimator animator(userStoriesTable); // Assuming the constructor takes a QTableWidget* parameter
    int newRowIndex = 0; // Assuming you have the new row index
    animator.animateRowAddition(newRowIndex); // Use this when a new row is added

    userStoriesTable->setGeometry(20, 55, 1250, 500);
        parentBoard->getCreationBox()->setVisible(false);
}
void pb_productbacklog_implementation::clearUserStoriesTable() {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    QComboBox* SprintComboBox = parentBoard->get_BL_SprintDropDown();
    userStoriesTable->clearContents();
    userStoriesTable->setRowCount(0);
    SprintComboBox->clear();
    //QComboBox* SprintBox = parentBoard->getSprintComboBox();
    //SprintBox->clear();
}
void pb_productbacklog_implementation::RetrieveAndDisplayBacklog() {

    qDebug() <<"RetrieveAndDisplayBacklog Called";
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    userStoriesTable->setGeometry(20, 55, 1250, 500);
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
void pb_productbacklog_implementation::Hide_CreateSection(){
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

void pb_productbacklog_implementation::Show_CreateSection_UserStory(){

    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    userStoriesTable->setGeometry(20, 55, 750, 500);
    parentBoard->getCreationBox()->setVisible(true);
    parentBoard->getButton_CreateUserStory()->setVisible(true);
    parentBoard->getButton_CreateTask()->setVisible(false);
    parentBoard->get_BL_SprintDropDown()->setVisible(false);
    parentBoard->get_SelecteSprint()->setVisible(false);
    QTextBrowser* Create_Header = parentBoard->getCreate_Header();
    Create_Header->setAlignment(Qt::AlignCenter);  // Align text to center
    Create_Header->setHtml("<html><head/><body><p style='font-size:12pt; text-align:center;'>Create User Stories</p></body></html>");

}

void pb_productbacklog_implementation::Show_CreateSection_Tasks(){
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    userStoriesTable->setGeometry(20, 55, 750, 500);
    parentBoard->getCreationBox()->setVisible(true);
    parentBoard->getButton_CreateUserStory()->setVisible(false);
    parentBoard->getButton_CreateTask()->setVisible(true);
    parentBoard->get_BL_SprintDropDown()->setVisible(true);
    parentBoard->get_SelecteSprint()->setVisible(true);
    QTextBrowser* Create_Header = parentBoard->getCreate_Header();
    Create_Header->setAlignment(Qt::AlignCenter);  // Align text to center
    Create_Header->setHtml("<html><head/><body><p style='font-size:12pt; text-align:center;'>Create User Tasks</p></body></html>");
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
        QSqlQuery query(dbobj);
        query.prepare("SELECT idTaskPB, Title, Description, Status, Assignee, Priority, ProductBacklog_idProductBacklog, ProductBacklog_Project_idProject FROM scrummy.TaskPB WHERE ProductBacklog_Project_idProject = :projectID");
        query.bindValue(":projectID", PassedProjectID);

        if (query.exec()) {
            qDebug() << "Tasks Retrieved Successfully!";
            while (query.next()) {
                int taskID = query.value(0).toInt();
                qDebug() << "Retrieved Task ID:" << taskID;
                QString title = query.value(1).toString();
                QString description = query.value(2).toString();
                QString status = query.value(3).toString();
                QString assignee = query.value(4).toString();
                int priority = query.value(5).toInt();

                // Include taskID as the seventh argument
                Tasks_Added_In_Table("Task", title, description, status, assignee, priority, taskID);

                // Store additional information in taskMap
                taskMap[taskID] = {title, description, status, assignee, priority, taskID};
            }
        } else {
            qDebug() << "Failed to retrieve data: " << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - pb_productbacklog_implementation class! - Task";
    }
}

void pb_productbacklog_implementation::Tasks_Added_In_Table(const QString& type_pb, const QString& taskName, const QString& description, const QString& status, QString assignee, int priority, int taskID) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    userStoriesTable->setColumnCount(7); // Include an additional column for Task ID
    userStoriesTable->setHorizontalHeaderLabels({"ID", "Type", "Title", "Description", "Status", "Assignee", "Priority"});
    userStoriesTable->setColumnHidden(0, true);

    QHeaderView* header = userStoriesTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    if (userStoriesTable) {
        int rowCount = userStoriesTable->rowCount();
        userStoriesTable->insertRow(rowCount);
        QTableWidgetItem* itemTaskID = new QTableWidgetItem();
        itemTaskID->setData(Qt::UserRole, QVariant(taskID));
        itemTaskID->setText(QString::number(taskID));
        userStoriesTable->setItem(rowCount, 0, itemTaskID);
        QTableWidgetItem* type = new QTableWidgetItem(type_pb);
        QTableWidgetItem* itemTaskName = new QTableWidgetItem(taskName);
        QTableWidgetItem* itemDescription = new QTableWidgetItem(description);
        QTableWidgetItem* itemPriority = new QTableWidgetItem(QString::number(priority));
        type->setFlags(type->flags() & ~Qt::ItemIsEditable);
        itemTaskID->setFlags(itemTaskID->flags() & ~Qt::ItemIsEditable);
        userStoriesTable->setItem(rowCount, 1, type);
        userStoriesTable->setItem(rowCount, 2, itemTaskName);
        userStoriesTable->setItem(rowCount, 3, itemDescription);


        // Adding a combo box for Status
        QComboBox* statusComboBox = new QComboBox();
        statusComboBox->addItems({"ToDo", "InProgress", "Blocked", "Done"});
        statusComboBox->setCurrentText(status);
        statusComboBox->setProperty("row", rowCount); // Set the property for the row
        userStoriesTable->setCellWidget(rowCount, 4, statusComboBox);
        // Connect the QComboBox currentIndexChanged signal using a lambda function
        disconnect(statusComboBox, &QComboBox::currentTextChanged, 0, 0);
        connect(statusComboBox, &QComboBox::currentTextChanged,
                [this, taskID, statusComboBox]() {
                    QString status = statusComboBox->currentText();
                    onStatusChanged(taskID, status);
                });

        // Adding a combo box for Assignee
        QComboBox* assigneeComboBox = new QComboBox();
        fillAssigneeComboBox(assigneeComboBox, assignee); // 'assignee' is the current assignee for the task
        assigneeComboBox->setProperty("row", rowCount);
        userStoriesTable->setCellWidget(rowCount, 5, assigneeComboBox);
        // Connect the QComboBox currentIndexChanged signal using a lambda function
        disconnect(assigneeComboBox, &QComboBox::currentTextChanged, 0, 0);
        // Add a check to ensure we don't re-fill the combobox if it's already populated
        if (assigneeComboBox->count() == 0) {
            fillAssigneeComboBox(assigneeComboBox, assignee);
        }
        connect(assigneeComboBox, &QComboBox::currentTextChanged,
                [this, taskID, assigneeComboBox]() {
                    QString newAssignee = assigneeComboBox->currentText();
                    onAssigneeChanged(taskID, newAssignee);
                });

        userStoriesTable->setItem(rowCount, 6, itemPriority);





    } else {
        qDebug() << "Table view not found or accessible.";
    }
}



//----------------------------------COMBO-BOX-INFO-----------------------------------------------
//----------------------------------COMBO-BOX-INFO-----------------------------------------------
//----------------------------------COMBO-BOX-INFO-----------------------------------------------

void pb_productbacklog_implementation::onStatusChanged(int taskID, const QString& status) {
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
    QString assignee = userStoriesTable->item(row, 5)->text();
    int priority = userStoriesTable->item(row, 6)->text().toInt();

    if (taskMap.contains(taskID)) {
        updateTaskInDatabase(taskID, title, description, status, assignee, priority);
    }
}

void pb_productbacklog_implementation::onAssigneeChanged(int taskID, const QString& newAssignee) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    if (!userStoriesTable) return;

    // Find the row for the taskID
    int row = -1;
    for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
        if (userStoriesTable->item(i, 0)->data(Qt::UserRole).toInt() == taskID) {
            row = i;
            break;
        }
    }
    if (row == -1) return; // Task ID not found

    // Retrieve other details of the task to update
    QString title = userStoriesTable->item(row, 2)->text();
    QString description = userStoriesTable->item(row, 3)->text();
    QString status;
    QWidget* widget = userStoriesTable->cellWidget(row, 4);
    if (widget) {
        QComboBox* comboBox = qobject_cast<QComboBox*>(widget);
        if (comboBox) {
            status = comboBox->currentText();
        }
    }
    int priority = userStoriesTable->item(row, 6)->text().toInt();

    // Update the task in the database
    updateTaskInDatabase(taskID, title, description, status, newAssignee, priority);
}

void pb_productbacklog_implementation::fillAssigneeComboBox(QComboBox* comboBox, const QString& currentAssignee) {
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open";
        return;
    }
    int PassedProjectID = parentBoard->getProjectId(); // Get the project ID
    QSqlQuery query;
    query.prepare("SELECT CONCAT(U.FirstName, ' ', U.LastName) AS FullName "
                  "FROM User AS U "
                  "INNER JOIN Project_has_User AS PHU ON U.idUser = PHU.User_idUser "
                  "INNER JOIN Project AS P ON PHU.Project_idProject = P.idProject "
                  "WHERE P.idProject = :ProjectID"); // Updated line
    query.bindValue(":ProjectID", PassedProjectID);
    if (!query.exec()) {
        qDebug() << "Query failed: " << query.lastError();
        return;
    }

    while (query.next()) {
        QString fullName = query.value(0).toString();
        qDebug() << "Adding to combo box:" << fullName; // Debug output
        comboBox->addItem(fullName);
    }
    // Set the current assignee if available
    if (!currentAssignee.isEmpty()) {
        int index = comboBox->findText(currentAssignee);
        if (index != -1) {
            comboBox->setCurrentIndex(index);
        }
    }
}

//----------------------------------COMBO-BOX-INFO-----------------------------------------------



















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

    if (taskMap.contains(taskID)) {
        QString title = userStoriesTable->item(row, 2)->text();
        QString description = userStoriesTable->item(row, 3)->text();
        QString status;
        QWidget* widget = userStoriesTable->cellWidget(row, 4);
        if (widget) {
            QComboBox* comboBox = qobject_cast<QComboBox*>(widget);
            if (comboBox) {
                status = comboBox->currentText();
            }
        }
        QString assignee = userStoriesTable->item(row, 5)->text();
        int priority = userStoriesTable->item(row, 6)->text().toInt();

        if (!status.isEmpty()) {
            updateTaskInDatabase(taskID, title, description, status, assignee, priority);
        } else {
            qDebug() << "Status is empty for Task ID:" << taskID;
        }
    }
}



void pb_productbacklog_implementation::updateTaskInDatabase(int taskID, const QString& title, const QString& description, const QString& status, QString assignee, int priority) {
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
}



//------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------
//Creation of Tasks
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
    QTableWidget* table = parentBoard->getUserStoriesTableView();
    int PassedProjectID = parentBoard->getProjectId();

    qDebug() << "Project ID in TASKPB - TASKSB: " << PassedProjectID;
    if (!table) {
        qDebug() << "Task table view not found or accessible.";
        return;
    }
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels({"ID", "Title", "Description", "Status", "Assignee", "Priority", "ProductBacklog ID"});

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
    query.prepare("INSERT INTO scrummy.TaskPB(Title, Description, Status, Priority, Assignee, ProductBacklog_idProductBacklog, ProductBacklog_Project_idProject) "
                  "VALUES (:title, :description, :status, :priority, :assignee, :productBacklogId, :projectId)");
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":status", status);
    query.bindValue(":priority", priority);
    query.bindValue(":assignee", assignee);
    query.bindValue(":productBacklogId", productBacklogId);
    query.bindValue(":projectId", PassedProjectID);
    if (!query.exec()) {
        qDebug() << "Failed to insert data into TaskPB table:" << query.lastError().text();
        dbobj.close();
        return;
    }
    qDebug() << "Data inserted into TaskPB table successfully!";





   //-----------------START-----------------------------Copy Of the Task in the Sprint Table



    QSqlQuery queryUser(dbobj);
    queryUser.prepare("SELECT idUser FROM User WHERE Username = :username");
    queryUser.bindValue(":username", assignee);

    int assigneeId = 0;
    if (queryUser.exec()) {
        if (queryUser.next()) {
            assigneeId = queryUser.value(0).toInt();
        }
    } else {
        qDebug() << "Failed to retrieve user ID:" << queryUser.lastError().text();
        return;
    }




    QSqlQuery query1(dbobj);
    query1.prepare("INSERT INTO scrummy.TaskSB(Title, Description, Status, Priority, Assignee, SprintBacklog_idSprintBacklog, SprintBacklog_Sprint_idSprint, SprintBacklog_Sprint_Project_idProject) "
                   "VALUES (:title, :description, :status, :priority, :assignee, :sprintBacklogId, :sprintId, :projectId)");
    query1.bindValue(":title", title);
    query1.bindValue(":description", description);
    query1.bindValue(":status", status);
    query1.bindValue(":priority", priority);
    query1.bindValue(":assignee", assigneeId);
    query1.bindValue(":sprintBacklogId", 1);
    query1.bindValue(":sprintId", SelectedSprint);
    query1.bindValue(":projectId", PassedProjectID);

    if (!query1.exec()) {
        qDebug() << "Failed to insert data into TaskSB table:" << query1.lastError().text();
        dbobj.close();
        return;
    }
    qDebug() << "Data inserted into TaskSB table successfully!";
    dbobj.close();

    //-----------------END-----------------------------Copy Of the Task in the Sprint Table





    int rowCount = table->rowCount();
    table->insertRow(rowCount);

    QTableWidgetItem* itemID = new QTableWidgetItem(query.lastInsertId().toString());
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
        query.prepare("SELECT idUserStoryPB, Title, Description, Status, Priority, Assignee FROM scrummy.UserStoryPB WHERE ProductBacklog_Project_idProject = :projectID");
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
                UserStories_Added_In_Table("User Story", title, description, status, assignee, priority, storyID);
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

void pb_productbacklog_implementation::UserStories_Added_In_Table(const QString& type_pb, const QString& storyName, const QString& description, const QString& status, int assignee, int priority, int storyID) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    userStoriesTable->setColumnCount(7);
    userStoriesTable->setHorizontalHeaderLabels({"ID", "Type", "Title", "Description", "Status", "Assignee", "Priority"});
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
        QTableWidgetItem* itemPriority = new QTableWidgetItem(QString::number(priority));
        QTableWidgetItem* itemAssignee = new QTableWidgetItem(QString::number(assignee));

        type->setFlags(type->flags() & ~Qt::ItemIsEditable);
        itemStoryID->setFlags(itemStoryID->flags() & ~Qt::ItemIsEditable);

        userStoriesTable->setItem(rowCount, 1, type);
        userStoriesTable->setItem(rowCount, 2, itemStoryName);
        userStoriesTable->setItem(rowCount, 3, itemDescription);


        QComboBox* statusComboBox = new QComboBox();
        statusComboBox->addItems({"ToDo", "InProgress", "Blocked", "Done"});
        statusComboBox->setCurrentText(status);
        userStoriesTable->setCellWidget(rowCount, 4, statusComboBox);

        // Correct the connection to use the overload of currentIndexChanged that passes the current text
        connect(statusComboBox, &QComboBox::currentTextChanged,
                [this, storyID, statusComboBox](const QString &newStatus) {
                    // Since storyID is captured by value, it is the correct ID for the row
                    onUserStoryStatusChanged(storyID, newStatus);
                });

        userStoriesTable->setItem(rowCount, 5, itemPriority);
        userStoriesTable->setItem(rowCount, 6, itemAssignee);
        /*
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


void pb_productbacklog_implementation::onUserStoryStatusChanged(int storyID, const QString& newStatus) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    if (!userStoriesTable) return;

    // Find the row for the storyID. This assumes storyID is unique.
    int row = -1;
    for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
        if (userStoriesTable->item(i, 0)->data(Qt::UserRole).toInt() == storyID) {
            row = i;
            break;
        }
    }
    if (row == -1) return; // storyID not found

    // Retrieve the rest of the details from the row
    QString title = userStoriesTable->item(row, 2)->text();
    QString description = userStoriesTable->item(row, 3)->text();
    int priority = userStoriesTable->item(row, 5)->text().toInt();
    int assignee = userStoriesTable->item(row, 6)->text().toInt();

    updateUserStoryInDatabase(storyID, title, description, newStatus, priority, assignee);
}


void pb_productbacklog_implementation::updateUserStoryInDatabase(int storyID, const QString& title, const QString& description, const QString& status, int priority, int assignee) {
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open";
        return;
    }

    QSqlQuery query;
    query.prepare("UPDATE scrummy.UserStoryPB SET Title = ?, Description = ?, Status = ?, Priority = ?, Assignee = ? WHERE idUserStoryPB = ?");
    query.addBindValue(title);
    query.addBindValue(description);
    query.addBindValue(status);
    query.addBindValue(priority);
    query.addBindValue(assignee);
    query.addBindValue(storyID);

    if (!query.exec()) {
        qDebug() << "Update failed for User Story ID:" << storyID << " Error:" << query.lastError();
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

    qDebug() << "Attempting to update User Story ID:" << storyID;

    if (storyMap.contains(storyID)) {
        QString title = userStoriesTable->item(row, 2)->text();
        QString description = userStoriesTable->item(row, 3)->text();
        // ...
        QString status;
        QWidget* widget = userStoriesTable->cellWidget(row, 4);
        if (widget) {
            QComboBox* comboBox = qobject_cast<QComboBox*>(widget);
            if (comboBox) {
                status = comboBox->currentText();
            }
        }
        int priority = userStoriesTable->item(row, 5)->text().toInt();
        int assignee = userStoriesTable->item(row, 6)->text().toInt();
        qDebug() << "Updating User Story: ID:" << storyID
                 << " Title:" << title
                 << " Description:" << description
                 << " Status:" << status
                 << " Priority:" << priority
                 << " Assignee:" << assignee;
        updateUserStoryInDatabase(storyID, title, description, status, priority, assignee);
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

    if (title.isEmpty() || description.isEmpty() || priorityText.isEmpty() || status.isEmpty()) {
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
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels({"ID", "Type", "Title", "Description", "Status", "Priority", "Assignee"});

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

    QTableWidgetItem* itemID = new QTableWidgetItem(query.lastInsertId().toString());
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
                QString sprintTitle = query.value(0).toString();
            }

        } else {
            qDebug() << "Failed to retrieve Sprint Data : " << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - pb_productbacklog_implementation class - ! - Sprint Data";
    }

}
