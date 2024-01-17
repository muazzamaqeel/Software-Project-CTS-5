#include "pb_team_implemenation.h"
#include <QCoreApplication>
#include "databasemanager.h"
#include "qheaderview.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include <QDebug>

pb_team_implemenation::pb_team_implemenation(parentboard* parentBoardInstance, QSqlDatabase& databaseInstance)
{
    parentBoard = parentBoardInstance;
    database3 = databaseInstance;

}
void pb_team_implemenation::on_createuser_clicked()
{
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();
    parentBoard->isTeamTableActive = true;
    QSqlQuery query(dbobj);

    int userId;
    int projectID = parentBoard->getProjectId();
    QString userEmail = parentBoard->getInputEmail()->text().trimmed();
    qDebug() << "TEAM: The user Email:" << userEmail;

    if (dbobj.isOpen()) {

        query.prepare("SELECT idUser FROM User WHERE User.Email = :userEmail");
        query.bindValue(":userEmail", userEmail);
        qDebug() << "Query prepared";

        if (!query.exec())
        {
            qDebug() << "Query execution error: " << query.lastError().text();
            return;
        }
        while (query.next())
        {
            userId = query.value(0).toInt();
            qDebug() << "TEAM: The user ID: " << userId;
            qDebug() << "TEAM: " << query.lastQuery();
        }
    } else {
        qDebug() << "Failed to open database: " << dbobj.lastError().text();
        return;
    }

    AddUserToProject(userId);
}

void pb_team_implemenation::UserRetrieval()
{

    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();
    if (parentBoard->isTeamTableActive)
    {
        return;
    }
    parentBoard->isTeamTableActive = true;
    QSqlQuery query(dbobj);
    QStringList roleList;

    roleList << "Product Owner";
    roleList << "Team Member";
    roleList << "Scrum Master";

    int projectID = parentBoard->getProjectId();

    if (dbobj.isOpen()) {

        query.prepare("SELECT User.FirstName, User.LastName, User.Email, User_Role_Project.Role_idRole FROM User "
                      "INNER JOIN User_Role_Project ON User.idUser = User_Role_Project.User_idUser "
                      "INNER JOIN Project ON Project.idProject = User_Role_Project.Project_idProject "
                      "WHERE User_Role_Project.Project_idProject = :projectID");
        query.bindValue(":projectID", projectID);
        qDebug() << "Query prepared";

        if (!query.exec())
        {
            qDebug() << "Query execution error: " << query.lastError().text();
            return;
        }

        while (query.next())
        {
            QString firstName = query.value(0).toString();
            QString lastName = query.value(1).toString();
            QString email = query.value(2).toString();
            QString role1 = query.value(3).toString();

            QComboBox* roleComboBox = new QComboBox();
            roleComboBox->addItems(roleList);
            QString role = role1.back();
            int role2 = role.toInt();
            if(role2 == 1)
                role = "Scrum Master";
            if(role2 == 2)
                role = "Project Owner";
            if(role2 == 3)
                role = "Team Member";
            roleComboBox->setCurrentText(role);
            AddRowUser(firstName,lastName, email, *roleComboBox);
        }
    } else {
        qDebug() << "Failed to open database: " << dbobj.lastError().text();
    }
}

void pb_team_implemenation::AddRowUser(const QString& firstNameInput, const QString& lastNameInput,
                   const QString& emailInput, QComboBox& roleInput)
{

    QTableWidget* teamTable = parentBoard->getTeamTableView();
    QHeaderView* header = teamTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    if(teamTable)
    {
        int rowSize = teamTable->rowCount();
        teamTable->insertRow(rowSize);
        QTableWidgetItem* firstName = new QTableWidgetItem(firstNameInput);
        QTableWidgetItem* lastName = new QTableWidgetItem(lastNameInput);
        QTableWidgetItem* email = new QTableWidgetItem(emailInput);

        email->setFlags(email->flags() & ~Qt::ItemIsEditable);

        teamTable->setItem(rowSize, 0, firstName);
        teamTable->setItem(rowSize, 1, lastName);
        teamTable->setItem(rowSize, 2, email);
        teamTable->setCellWidget(rowSize, 3, &roleInput);
        connect(&roleInput, &QComboBox::currentTextChanged,
                [this](const QString &newStatus) {
                    onRoleChanged(newStatus);
                });
    }

}

void pb_team_implemenation::ShowUserProperties()
{
    parentBoard->getCreateUserButton()->setVisible(true);
    parentBoard->getDisplayFirstName()->setVisible(true);
    parentBoard->getDisplayRole()->setVisible(true);
    parentBoard->getInputEmail()->setVisible(true);
    parentBoard->getComboBoxRole()->setVisible(true);
}

void pb_team_implemenation::AddUserToProject(int userId){
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();
    parentBoard->isTeamTableActive = true;
    QSqlQuery query(dbobj);

    QString userRoleString = parentBoard->getDisplayRole()->toPlainText();
    int userRole;
    if(userRoleString.trimmed() =="Team Member")
        userRole = 3;
    else if(userRoleString.trimmed() == "Scrum Master")
        userRole = 1;
    else
        userRole = 2;
    int projectID = parentBoard->getProjectId();
    qDebug() << "TEAM: The user ID:" << userId;
    if (dbobj.isOpen()) {
        query.prepare("INSERT INTO User_Role_Project(User_idUser, Project_idProject, Role_idRole) VALUES"
                      "(:userId, :projectID, :userRole)");
        query.bindValue(":projectID", projectID);
        query.bindValue(":userId", userId);
        query.bindValue(":userRole", userRole);
        qDebug() << "Query prepared";

        if (!query.exec())
        {
            qDebug() << "Query execution error: " << query.lastError().text();
            return;
        }

    } else {
        qDebug() << "Failed to open database: " << dbobj.lastError().text();
    }

    QStringList roleList;

    roleList << "Product Owner";
    roleList << "Team Member";
    roleList << "Scrum Master";

    if (dbobj.isOpen()) {
        query.prepare("SELECT User.FirstName, User.LastName, User.Email, User_Role_Project.Role_idRole FROM User "
                      "INNER JOIN User_Role_Project ON User.idUser = User_Role_Project.User_idUser "
                      "INNER JOIN Project ON Project.idProject = User_Role_Project.Project_idProject "
                      "WHERE User_Role_Project.Project_idProject = :projectID AND idUser = :userId");
        query.bindValue(":userId", userId);
        query.bindValue(":projectID", projectID);
        qDebug() << "Query prepared";

        if (!query.exec())
        {
            qDebug() << "Query execution error: " << query.lastError().text();
            return;
        }
        while (query.next())
        {
            QString firstName = query.value(0).toString();
            QString lastName = query.value(1).toString();
            QString email = query.value(2).toString();
            QString role1 = query.value(3).toString();

            QComboBox* roleComboBox = new QComboBox();
            roleComboBox->addItems(roleList);
            roleComboBox->setCurrentText(role1);
            QString role = role1.back();
            int role2 = role.toInt();
            qDebug() << "Role as String: " << role1 << "   Role as int:" << role2;
            if(role2 == 1)
                role = "Scrum Master";
            if(role2 == 2)
                role = "Project Owner";
            if(role2 == 3)
                role = "Team Member";
            AddRowUser(firstName,lastName, email, *roleComboBox);
        }
    } else {
        qDebug() << "Failed to open database: " << dbobj.lastError().text();
        dbobj.close();
    }
    dbobj.close();
}

void pb_team_implemenation::HideUserProperties()
{
    parentBoard->getCreateUserButton()->setVisible(false);
    parentBoard->getDisplayFirstName()->setVisible(false);
    parentBoard->getDisplayRole()->setVisible(false);
    parentBoard->getInputEmail()->setVisible(false);
    parentBoard->getComboBoxRole()->setVisible(false);
}

void pb_team_implemenation::on_teamTab_opened()
{
    QTableWidget* teamTable = parentBoard->getTeamTableView();
    teamTable->setColumnCount(4);
    teamTable->setHorizontalHeaderLabels({"First Name", "Last name", "E-Mail", "Role"});

    QHeaderView* header = teamTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    int rowSize = teamTable->rowCount();
    teamTable->insertRow(rowSize);

    //QTableWidgetItem* userFirstName = new QTableWidgetItem()
}

void pb_team_implemenation::onRoleChanged(const QString& role)
{
    int userId;
    int projectID = parentBoard->getProjectId();
    QTableWidget* teamTable = parentBoard->getTeamTableView();
    if(!teamTable)
        return;
    QItemSelectionModel *select = teamTable->selectionModel();
    int selectedRow = select->selectedIndexes().first().row();
    qDebug() << "TEAM: selected row:" << selectedRow;

    QString userEmail = teamTable->item(selectedRow, 2)->text();
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();
    QSqlQuery query(dbobj);

    int roleId;

    if(role == "Team Member")
        roleId = 3;
    else if(role == "Scrum Master")
        roleId = 2;
    else
        roleId = 1;

    if (dbobj.isOpen()) {
        query.prepare("SELECT idUser FROM User WHERE User.Email = :userEmail");
        query.bindValue(":userEmail", userEmail);
        qDebug() << "TEAM: Email fetch query prepared" << userEmail;

        if (!query.exec())
        {
            qDebug() << "Query execution error: " << query.lastError().text();
            return;
            dbobj.close();
        }
        while(query.next())
        {
            userId = query.value(0).toInt();
            qDebug() << "TEAM: user ID:" << userId;
            qDebug() << "TEAM: project ID:" << projectID;
        }
        /*else{
            qDebug() << "Query execution error: " << query.lastError().text();
            return;
        }*/

        query.prepare("UPDATE User_Role_Project SET Role_idRole = :userRole WHERE Project_idProject = :projectID "
                      "AND User_idUser = :userId");
        query.bindValue(":userRole", roleId);
        query.bindValue(":userId", userId);
        query.bindValue(":projectID", projectID);
        if (!query.exec())
        {
            qDebug() << "Query execution error: " << dbobj.lastError().text();
            return;
            dbobj.close();
        }else
            qDebug() << "TEAM: User role updated!";

    }else {
        qDebug() << "Failed to open database: " << dbobj.lastError().text();
        return;
        dbobj.close();
    }

}


