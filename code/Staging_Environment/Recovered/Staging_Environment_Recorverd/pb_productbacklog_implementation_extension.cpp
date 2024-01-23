#include "pb_productbacklog_implementation_extension.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QDebug> // Include qDebug for debugging
#include <QTableView>
#include "databasemanager.h"
#include "qheaderview.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include <QRegularExpression>
#include <QFont>
#include <QString>
#include <QMap>
#include <QVariant>
#include <QMessageBox>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
pb_productbacklog_implementation_Extension::pb_productbacklog_implementation_Extension(parentboard* parentBoardInstance) {

    parentBoard = parentBoardInstance;
    QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
}


void pb_productbacklog_implementation_Extension::deleteUserStory(int storyID) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open";
        return;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM scrummy.UserStoryPB WHERE idUserStoryPB = :storyID");
    query.bindValue(":storyID", storyID);

    if (!query.exec()) {
        qDebug() << "Failed to delete User Story ID:" << storyID << " Error:" << query.lastError().text();
    } else {
        qDebug() << "User Story ID:" << storyID << " deleted successfully";

        // Update the UI by removing the row from the table
        QTableWidget* userStoriesTable = parentBoard->getUserStoriesTableView();
        if (userStoriesTable) {
            for (int i = 0; i < userStoriesTable->rowCount(); ++i) {
                if (userStoriesTable->item(i, 0)->data(Qt::UserRole).toInt() == storyID) {
                    userStoriesTable->removeRow(i);
                    break;
                }
            }
        }
    }
}


void pb_productbacklog_implementation_Extension::Send_UserStory_ToSprint(int taskID, const QString& title, const QString& description, const QString& status, int priority, const QString& assigneeId, const QString& selectedSprint){
    DatabaseManager database;

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
    query.prepare("INSERT INTO UserStoryPB(Title, Description, Status, Priority, Assignee, ProductBacklog_idProductBacklog, ProductBacklog_Project_idProject, AssignedSprint) "
                  "VALUES (:title, :description, :status, :priority, :assignee, :productBacklogId, :projectId, :assignedSprint)");
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":status", status);
    query.bindValue(":priority", priority);
    query.bindValue(":assignee", assigneeId);
    query.bindValue(":productBacklogId", productBacklogId);
    query.bindValue(":projectId", PassedProjectID);
    query.bindValue(":assignedSprint", selectedSprint);


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
    int SameValueTaskPB = lastInsertId.toInt(); // This will be used for UserStorySB


    //Add Task To a UserStorySB"
    //Add Task To a UserStorySB"
    //Add Task To a UserStorySB"

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
        query1.prepare("INSERT INTO scrummy.UserStorySB(idUserStorySB, Title, Description, Status, Priority, Assignee, SprintBacklog_idSprintBacklog, SprintBacklog_Sprint_idSprint, SprintBacklog_Sprint_Project_idProject) "
                       "VALUES (:idUserStory, :title, :description, :status, :priority, :assignee, :sprintBacklogId, :sprintId, :projectId)");
        query1.bindValue(":idUserStory", SameValueTaskPB);  // Replace with the appropriate value for idUserStory
        query1.bindValue(":title", title);
        query1.bindValue(":description", description);
        query1.bindValue(":status", status);
        query1.bindValue(":priority", priority);
        query1.bindValue(":assignee", userId);
        query1.bindValue(":sprintBacklogId", idSprintBacklog);
        query1.bindValue(":sprintId", Sprint_idSprint);
        query1.bindValue(":projectId", PassedProjectID);


        if (!query1.exec()) {
            qDebug() << "Failed to insert data into UserStorySB table:" << query1.lastError().text();
            dbobj.close();
            return;
        }
        qDebug() << "Data inserted into UserStorySB table successfully!";
        dbobj.close();
    }
}



void pb_productbacklog_implementation_Extension::deleteTaskFromDatabase(int taskID) {

    qDebug() << "deleteTaskFromDatabasedeleteTaskFromDatabasedeleteTaskFromDatabase";

    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "Database is not open";
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM scrummy.UserStoryPB WHERE idUserStoryPB = ?");
    query.addBindValue(taskID);

    if (!query.exec()) {
        qDebug() << "Delete failed: " << query.lastError();
    } else {
        qDebug() << "Delete successful for task ID:" << taskID;
    }

    //Also Gets Deleted in
    QSqlQuery query1;
    query.prepare("DELETE FROM scrummy.UserStorySB WHERE idUserStorySB = ?");
    query.addBindValue(taskID);

    if (!query.exec()) {
        qDebug() << "Delete failed: " << query.lastError();
    } else {
        qDebug() << "Delete successful for task ID:" << taskID;
    }
}

