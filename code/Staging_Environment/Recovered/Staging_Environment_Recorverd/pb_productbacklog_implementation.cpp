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

//Fetch the Sprints from the Sprint table
#include <QFont>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QMessageBox>

pb_productbacklog_implementation::pb_productbacklog_implementation(parentboard* parentBoardInstance) {
    // Initialize any necessary variables or connections
    parentBoard = parentBoardInstance;

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
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();

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



void pb_productbacklog_implementation::Show_CreateSection(){
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


    parentBoard->getButton_CreateUserStory()->setVisible(true);
    parentBoard->getButton_CreateTask()->setVisible(false);

    parentBoard->get_BL_SprintDropDown()->setVisible(false);
    parentBoard->get_SelecteSprint()->setVisible(false);

    QTextBrowser* Create_Header = parentBoard->getCreate_Header();
    Create_Header->setAlignment(Qt::AlignCenter);  // Align text to center
    Create_Header->setHtml("<html><head/><body><p style='font-size:12pt; text-align:center;'>Create User Stories</p></body></html>");

}

void pb_productbacklog_implementation::Show_CreateSection_Tasks(){

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
                int assignee = query.value(4).toInt();
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

void pb_productbacklog_implementation::Tasks_Added_In_Table(const QString& type_pb, const QString& taskName, const QString& description, const QString& status, int assignee, int priority, int taskID) {
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
    userStoriesTable->setColumnCount(7); // Include an additional column for Task ID
    userStoriesTable->setHorizontalHeaderLabels({"ID", "Type", "Title", "Description", "Status", "Assignee", "Priority"});
    userStoriesTable->setColumnHidden(0, true);
    userStoriesTable->setColumnHidden(6, true);

    QHeaderView* header = userStoriesTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    if (userStoriesTable) {
        int rowCount = userStoriesTable->rowCount();
        userStoriesTable->insertRow(rowCount);

        QTableWidgetItem* itemTaskID = new QTableWidgetItem();
        itemTaskID->setData(Qt::UserRole, QVariant(taskID));
        itemTaskID->setText(QString::number(taskID)); // Set the text for the item
        userStoriesTable->setItem(rowCount, 0, itemTaskID);


        QTableWidgetItem* type = new QTableWidgetItem(type_pb);
        QTableWidgetItem* itemTaskName = new QTableWidgetItem(taskName);
        QTableWidgetItem* itemDescription = new QTableWidgetItem(description);
        QTableWidgetItem* itemStatus = new QTableWidgetItem(status);
        QTableWidgetItem* itemAssignee = new QTableWidgetItem(QString::number(assignee));
        QTableWidgetItem* itemPriority = new QTableWidgetItem(QString::number(priority));

        type->setFlags(type->flags() & ~Qt::ItemIsEditable);
        itemTaskID->setFlags(itemTaskID->flags() & ~Qt::ItemIsEditable); // Make the Task ID column non-editable

        userStoriesTable->setItem(rowCount, 0, itemTaskID); // Task ID
        userStoriesTable->setItem(rowCount, 1, type);
        userStoriesTable->setItem(rowCount, 2, itemTaskName);
        userStoriesTable->setItem(rowCount, 3, itemDescription);
        userStoriesTable->setItem(rowCount, 4, itemStatus);
        userStoriesTable->setItem(rowCount, 5, itemAssignee);
        userStoriesTable->setItem(rowCount, 6, itemPriority);
    } else {
        qDebug() << "Table view not found or accessible.";
    }
}


//EDIT FUNCTIONALITY
void pb_productbacklog_implementation::onTableItemChanged(QTableWidgetItem* item) {
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

    // Retrieve the task ID from the first column
    int taskID = userStoriesTable->item(row, 0)->data(Qt::UserRole).toInt();
    qDebug() << "Task ID to update:" << taskID;

    if (taskMap.contains(taskID)) {
        // Retrieve the current values from all columns of the row

        QString title = userStoriesTable->item(row, 2)->text();
        QString description = userStoriesTable->item(row, 3)->text();
        QString status = userStoriesTable->item(row, 4)->text();
        int assignee = userStoriesTable->item(row, 5)->text().toInt();
        int priority = userStoriesTable->item(row, 6)->text().toInt();

        // Call the update function with all values
        updateTaskInDatabase(taskID, title, description, status, assignee, priority);
    } else {
        qDebug() << "Task ID not found in taskMap";
    }
}
void pb_productbacklog_implementation::updateTaskInDatabase(int taskID, const QString& title, const QString& description, const QString& status, int assignee, int priority) {
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
    QTableWidget* table = parentBoard->getUserStoriesTableView(); // Assuming there's a method to get the task table view
    int PassedProjectID = parentBoard->getProjectId();

    qDebug() << "Project ID in TASKPB - TASKSB: " << PassedProjectID;
    //Getting the assignee value from the database
    if (!table) {
        qDebug() << "Task table view not found or accessible.";
        return;
    }
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels({"ID", "Title", "Description", "Status", "Priority", "Assignee", "ProductBacklog ID"});

    QHeaderView* header = table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();
    if (!dbobj.isOpen()) {
        qDebug() << "Connection Not Established - pb_productbacklog_implmentation!";
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
    query.bindValue(":productBacklogId", 1);  // Assuming 2 is the correct value
    query.bindValue(":projectId", PassedProjectID);



    if (!query.exec()) {
        qDebug() << "Failed to insert data into TaskPB table:" << query.lastError().text();
        dbobj.close();
        return;
    }
    qDebug() << "Data inserted into TaskPB table successfully!";
    dbobj.close();


    //Copy Of the Task in the Sprint Table
    /*
    QSqlQuery query1(dbobj);
    query1.prepare("INSERT INTO scrummy.TaskSB(Title, Description, Status, Priority, Assignee, ProductBacklog_idProductBacklog, ProductBacklog_Project_idProject)"
                  "VALUES (:title, :description, :status, :priority, :assignee, 2, 2)");
    query1.bindValue(":title", title);
    query1.bindValue(":description", description);
    query1.bindValue(":status", status);
    query1.bindValue(":priority", priority);
    query1.bindValue(":assignee", assignee);

    if (!query1.exec()) {
        qDebug() << "Failed to insert data into TaskSB table:" << query1.lastError().text();
        dbobj.close();
        return;
    }
    qDebug() << "Data inserted into TaskPB table successfully!";
    dbobj.close();
    */





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
    userStoriesTable->setHorizontalHeaderLabels({"ID", "Type", "Title", "Description", "Status", "Priority", "Assignee"});
    userStoriesTable->setColumnHidden(0, true);
    userStoriesTable->setColumnHidden(6, true);
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
        QTableWidgetItem* itemStatus = new QTableWidgetItem(status);
        QTableWidgetItem* itemPriority = new QTableWidgetItem(QString::number(priority));
        QTableWidgetItem* itemAssignee = new QTableWidgetItem(QString::number(assignee));

        type->setFlags(type->flags() & ~Qt::ItemIsEditable);
        itemStoryID->setFlags(itemStoryID->flags() & ~Qt::ItemIsEditable);

        userStoriesTable->setItem(rowCount, 1, type);
        userStoriesTable->setItem(rowCount, 2, itemStoryName);
        userStoriesTable->setItem(rowCount, 3, itemDescription);
        userStoriesTable->setItem(rowCount, 4, itemStatus);
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
        QString status = userStoriesTable->item(row, 4)->text();
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
