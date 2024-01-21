#ifndef PB_TEAM_IMPLEMENATION_H
#define PB_TEAM_IMPLEMENATION_H
#include <string>
#include <QString>
#include <QLineEdit>
#include "parentboard.h"
#include <QWidget>
#include <QStandardItemModel>

class pb_team_implemenation: public QObject
{
    Q_OBJECT
public:
    QStandardItemModel *model;
    pb_team_implemenation(parentboard* parentBoardInstance, QSqlDatabase& databaseInstance);

public slots:
    void onRoleChanged(const QString& role);
    void on_teamTab_opened();
    void on_createuser_clicked();
    void UserRetrieval();
    void AddUserToProject(int userId);
    void HideUserProperties();
    void ShowUserProperties();
    void RemoveUser(QTableWidgetItem* item);
    void AddRowUser(const QString& firstNameInput,const QString& lastNameInput, const QString& emailInput, QComboBox& roleInput);
private:
        parentboard* parentBoard;
        QSqlDatabase database3;
};

#endif // PB_TEAM_IMPLEMENATION_H
