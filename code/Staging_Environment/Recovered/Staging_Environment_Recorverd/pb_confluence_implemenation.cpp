#include "pb_confluence_implemenation.h"
#include "parentboard.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QDebug> // Include qDebug for debugging
#include "parentboard.h"
#include <QTableView>
#include "qmessagebox.h"
#include <QSqlQuery>
#include <QSqlError>

PB_Confluence_Implemenation::PB_Confluence_Implemenation(parentboard* parentBoardInstance)
{
    parentBoard = parentBoardInstance;
    parentBoard->getCreationBox_Confluence()->setVisible(false);
    parentBoard->get_InputTitle_2()->setVisible(false);
    parentBoard->get_InputGroup_Confluence_Heading()->setVisible(false);
    parentBoard->get_Confluence_NameText()->setVisible(false);
    parentBoard->get_Confluence_HeadingText()->setVisible(false);
    parentBoard->get_Confluence_GroupText()->setVisible(false);
    parentBoard->get_Button_Create_Confluence()->setVisible(false);
    parentBoard->getuserTaskTreeWidget_2()->setVisible(true);

}

void PB_Confluence_Implemenation::HideCreationSection()
{
    QTreeWidget* ConfluenceTable = parentBoard->getuserTaskTreeWidget_2();
    ConfluenceTable->setGeometry(10, 75, 1250, 550);
    parentBoard->getCreationBox_Confluence()->setVisible(false);
    parentBoard->get_InputTitle_2()->setVisible(false);
    parentBoard->get_InputGroup_Confluence_Heading()->setVisible(false);
    parentBoard->get_Confluence_NameText()->setVisible(false);
    parentBoard->get_Confluence_HeadingText()->setVisible(false);
    parentBoard->get_Confluence_GroupText()->setVisible(false);
    parentBoard->get_Button_Create_Confluence()->setVisible(false);
    parentBoard->getuserTaskTreeWidget_2()->setVisible(true);


}

void PB_Confluence_Implemenation::ShowCreateWindow_Page(){

    parentBoard->getCreationBox_Confluence()->setVisible(true);
    parentBoard->get_InputTitle_2()->setVisible(true);
    parentBoard->get_InputGroup_Confluence_Heading()->setVisible(true);
    parentBoard->get_Confluence_NameText()->setVisible(true);
    parentBoard->get_Confluence_HeadingText()->setVisible(true);
    parentBoard->get_Confluence_GroupText()->setVisible(true);
    //LowerButtons
    parentBoard->get_Button_CreatePage_Confluence()->setVisible(true);
    parentBoard->get_Button_Create_Confluence()->setVisible(false);

    QComboBox* GroupComboBox= parentBoard->get_InputGroup_Confluence_Heading();
    GroupComboBox->clear();

    // Retrieve the GroupName values from the database
    int PassedProjectID = parentBoard->getProjectId();  // Assuming you have the project ID available here

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (dbobj.isOpen() && dbobj.isValid()) {
        QSqlQuery query(dbobj);
        query.prepare("SELECT GroupName FROM ConfluenceGroup WHERE Project_idProject = :Project_idProject");
        query.bindValue(":Project_idProject", PassedProjectID);

        if (!query.exec()) {
            QMessageBox::critical(nullptr, "Database Error", query.lastError().text());
        } else {
            while (query.next()) {
                QString groupName = query.value(0).toString();
                GroupComboBox->addItem(groupName);
            }
            if (GroupComboBox->count() == 0) {
                QMessageBox::information(nullptr, "No Groups Found", "No groups found for this project.");
            }
        }
    } else {
        QMessageBox::critical(nullptr, "Database Error", "Cannot connect to the database.");
    }
}
void PB_Confluence_Implemenation::CreatePageFunction(){
    QTextEdit* Title = parentBoard->get_InputTitle_2();
    QComboBox* GroupComboBox = parentBoard->get_InputGroup_Confluence_Heading();
    int PassedProjectID = parentBoard->getProjectId();  // Assuming you have the project ID available here

    // Get the current selected value from GroupComboBox
    QString selectedGroupName = GroupComboBox->currentText();

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (dbobj.isOpen() && dbobj.isValid()) {
        // Begin a transaction
        dbobj.transaction();

        QSqlQuery query(dbobj);
        // Prepare the query to get the idGroup based on the GroupName
        query.prepare("SELECT idGroup FROM ConfluenceGroup WHERE GroupName = :GroupName AND Project_idProject = :ProjectID");
        query.bindValue(":GroupName", selectedGroupName);
        query.bindValue(":ProjectID", PassedProjectID);

        if (query.exec() && query.next()) {
            int idGroup = query.value(0).toInt();

            // Prepare the query to insert a new page
            QSqlQuery insertQuery(dbobj);
            insertQuery.prepare("INSERT INTO Page (PageName, Content, ConfluenceGroup_idGroup, ConfluenceGroup_Project_idProject) VALUES (:PageName, :Content, :idGroup, :ProjectID)");
            insertQuery.bindValue(":PageName", Title->toPlainText());
            insertQuery.bindValue(":Content", "");
            insertQuery.bindValue(":idGroup", idGroup);
            insertQuery.bindValue(":ProjectID", PassedProjectID);

            // Execute the insert query
            if (insertQuery.exec()) {
                // Commit the transaction if the insert was successful
                dbobj.commit();
            } else {
                // Rollback the transaction in case of an error
                dbobj.rollback();
            }
        } else {
            // Handle the error if the SELECT query didn't work
            qDebug() << "Error getting idGroup from ConfluenceGroup: " << query.lastError().text();
            // Optionally rollback or handle the transaction
            dbobj.rollback();
        }
    } else {
        qDebug() << "Database not open or not valid";
    }
}



void PB_Confluence_Implemenation::ShowCreateWindow(){
    QTreeWidget* ConfluenceTable = parentBoard->getuserTaskTreeWidget_2();
    ConfluenceTable->setGeometry(10, 75, 800, 550);
    parentBoard->getCreationBox_Confluence()->setVisible(true);
    parentBoard->get_InputTitle_2()->setVisible(true);
    parentBoard->get_InputGroup_Confluence_Heading()->setVisible(false);
    parentBoard->get_Confluence_NameText()->setVisible(true);
    parentBoard->get_Confluence_HeadingText()->setVisible(true);
    parentBoard->get_Confluence_GroupText()->setVisible(false);
    parentBoard->get_Button_Create_Confluence()->setVisible(true);
    QComboBox* GroupInput = parentBoard->get_InputGroup_Confluence_Heading();
    //LowerButtons
    parentBoard->get_Button_CreatePage_Confluence()->setVisible(false);
    parentBoard->get_Button_Create_Confluence()->setVisible(true);

}



void PB_Confluence_Implemenation::CreateGroupFunction(){
    GroupName = parentBoard->get_InputTitle_2()->toPlainText();
    int PassedProjectID = parentBoard->getProjectId();

    if (GroupName.isEmpty()) {
        QMessageBox::warning(nullptr, "Required Fields", "Please fill up all the required fields.");
    } else {
        DatabaseManager database;
        QSqlDatabase dbobj = database.getDatabase();

        if (dbobj.isOpen() && dbobj.isValid()) {
            // Start a transaction
            dbobj.transaction();

            // Insert into ConfluenceGroup table
            QSqlQuery query(dbobj);
            query.prepare("INSERT INTO ConfluenceGroup (GroupName, Project_idProject) VALUES (:GroupName, :Project_idProject)");
            query.bindValue(":GroupName", GroupName);
            query.bindValue(":Project_idProject", PassedProjectID);

            if (!query.exec()) {
                QMessageBox::critical(nullptr, "Database Error", query.lastError().text());
                dbobj.rollback(); // Rollback transaction on failure
                return;
            }
            /*
            // Get the last inserted idGroup
            QVariant lastGroupId = query.lastInsertId();

            // Insert into Page table
            query.prepare("INSERT INTO Page (PageName, Content, ConfluenceGroup_idGroup, ConfluenceGroup_Project_idProject) "
                          "VALUES (:PageName, :Content, :ConfluenceGroup_idGroup, :ConfluenceGroup_Project_idProject)");
            query.bindValue(":PageName", GroupName);
            query.bindValue(":Content", "");
            query.bindValue(":ConfluenceGroup_idGroup", lastGroupId);
            query.bindValue(":ConfluenceGroup_Project_idProject", PassedProjectID);

            if (!query.exec()) {
                QMessageBox::critical(nullptr, "Failed to insert data into Page table", query.lastError().text());
                dbobj.rollback(); // Rollback transaction on failure
                return;
            }
        */

            // Commit the transaction
            dbobj.commit();
            QMessageBox::information(nullptr, "Success", "The group and page have been added successfully.");
        } else {
            QMessageBox::critical(nullptr, "Database Error", "Cannot connect to the database.");
        }
    }

    // Hide UI elements after insertion
    QTreeWidget* ConfluenceTable = parentBoard->getuserTaskTreeWidget_2();
    ConfluenceTable->setGeometry(10, 75, 1250, 550);
    parentBoard->get_InputGroup_Confluence_Heading()->setVisible(false);
    parentBoard->getCreationBox_Confluence()->setVisible(false);
    parentBoard->get_InputTitle_2()->setVisible(false);
    parentBoard->get_InputGroup_Confluence_Heading()->setVisible(false);
    parentBoard->get_Confluence_NameText()->setVisible(false);
    parentBoard->get_Confluence_HeadingText()->setVisible(false);
    parentBoard->get_Confluence_GroupText()->setVisible(false);
    parentBoard->get_Button_Create_Confluence()->setVisible(false);
}







void PB_Confluence_Implemenation::ConfluenceTableChange_Dectection(QTreeWidgetItem *item, int column) {
    qDebug() << "ConfluenceTableChange_Dectection Function called";


}
