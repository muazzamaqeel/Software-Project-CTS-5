#include "pb_team_implemenation.h"
#include <QCoreApplication>
#include "databasemanager.h"
#include "qheaderview.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include <QDebug>

pb_team_implemenation::pb_team_implemenation(parentboard* parentBoardInstance)
{
    parentBoard = parentBoardInstance;
}
void pb_team_implemenation::on_createuser_clicked()
{
    QLineEdit* firstNameField = parentBoard->getFirstNameField();
    firstNameField->setText(GetUserFirstName(28));
}

void pb_team_implemenation::UserRetrieval()
{

    if (parentBoard->isTeamTableActive)
    {
        return;
    }
    parentBoard->isTeamTableActive = true;
    DatabaseManager database;
    QSqlDatabase databaseInstance = database.getDatabase();
    QSqlQuery query(databaseInstance);

    int projectID = parentBoard->getProjectId();

    if (databaseInstance.isOpen()) {

        query.prepare("SELECT FirstName, LastName, Email, Role_idRole FROM User "
                      "INNER JOIN Project_has_User ON User.idUser = Project_has_User.User_idUser "
                      "INNER JOIN Project ON Project.idProject = Project_has_User.Project_idProject "
                      "WHERE Project_has_User.Project_idProject = :projectID");
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

            QString role = role1.back();
            int role2 = role.toInt();
            qDebug() << "Role as String: " << role1 << "   Role as int:" << role2;
            if(role2 == 1)
                role = "Scrum Master";
            if(role2 == 2)
                role = "Project Owner";
            if(role2 == 3)
                role = "Team Member";
            AddRowUser(firstName,lastName, email, role);
            qDebug() << "Row fetched: " << firstName << ", " << email << ", " << role2;
        }
    } else {
        qDebug() << "Failed to open database: " << databaseInstance.lastError().text();
    }
}

void pb_team_implemenation::AddRowUser(const QString& firstNameInput, const QString& lastNameInput,
                   const QString& emailInput, const QString& roleInput)
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
        QTableWidgetItem* role = new QTableWidgetItem(roleInput);

        email->setFlags(email->flags() & ~Qt::ItemIsEditable);
        role->setFlags(role->flags() & ~Qt::ItemIsEditable);

        teamTable->setItem(rowSize, 0, firstName);
        teamTable->setItem(rowSize, 1, lastName);
        teamTable->setItem(rowSize, 2, email);
        teamTable->setItem(rowSize, 3, role);
    }

}

void pb_team_implemenation::HideUserProperties()
{
    parentBoard->getCreateUserButton()->setVisible(false);
    parentBoard->getDisplayFirstName()->setVisible(false);
    parentBoard->getDisplayRole()->setVisible(false);
    parentBoard->getInputFirstName()->setVisible(false);
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
QString pb_team_implemenation::GetUserFirstName(int UserId)
{
    DatabaseManager database;
    QSqlDatabase databaseInstance = database.getDatabase();
    QString id = QString::number(UserId);
    QString FirstNameQuery = "SELECT FirstName FROM scrummy.User WHERE idUser= '" + id + "'";
    QString returnText = "";

    try{
        databaseInstance.isOpen();
        }
    catch(std::exception e){
        qDebug() << "Connection Not Established - Login class!";
        return "";
    }
    QSqlQuery query(databaseInstance);
    query.prepare(FirstNameQuery);
    try{
        query.exec();
    }
    catch(std::exception e){
        qDebug() << "Failed to retrieve user data:" << query.lastError().text();
        return "";
    }
    if(query.next()){
        returnText = query.value(0).toString();
    }
    return returnText;
}
