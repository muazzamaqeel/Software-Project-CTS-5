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
