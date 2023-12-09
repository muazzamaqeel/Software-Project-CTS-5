#include "pb_team_implemenation.h"
#include <QCoreApplication>
#include "databasemanager.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include <QDebug>

pb_team_implemenation::pb_team_implemenation(parentboard* parentBoardInstance)
{
    parentBoard = parentBoardInstance;
}
void pb_team_implemenation::on_createuser_clicked(){
    QLineEdit* firstNameField = parentBoard->getFirstNameField();
    firstNameField->setText(GetUserFirstName(28));
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
