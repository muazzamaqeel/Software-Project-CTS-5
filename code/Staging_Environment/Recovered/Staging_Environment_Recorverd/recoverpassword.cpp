#include "recoverpassword.h"
#include "QtGui/qscreen.h"
#include "ui_recoverpassword.h"
#include "databasemanager.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

/**
 * @brief RecoverPassword::RecoverPassword
 * Constructor for the RecoverPassword class.
 * Sets up the UI, centers the window on the screen, and connects the save button to the changePassword() slot.
 * @param parent The parent widget.
 */
RecoverPassword::RecoverPassword(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RecoverPassword)
{
    ui->setupUi(this);

    centerOnScreen();

    // Connect the save button's click signal to a slot
    connect(ui->Save_Button, SIGNAL(clicked()), this, SLOT(changePassword()));
}

/**
 * @brief RecoverPassword::~RecoverPassword
 * Destructor for the RecoverPassword class.
 */
RecoverPassword::~RecoverPassword()
{
    delete ui;
}

/**
 * @brief RecoverPassword::changePassword
 * Slot called when the save button is clicked.
 * Retrieves user input, hashes passwords, validates input, and updates the password in the database if successful.
 */
void RecoverPassword::changePassword()
{
    QString inputUsername = ui->Input_UserName->text();
    QString currentPassword = ui->Input_UserName->text();
    QString newPassword = ui->Input_NewPass->text();
    QString repeatPassword = ui->Input_RepeatPass->text();

    // Hash the current and new passwords
    QByteArray currentPasswordHash = QCryptographicHash::hash(currentPassword.toUtf8(), QCryptographicHash::Sha256).toHex();
    QByteArray newPasswordHash = QCryptographicHash::hash(newPassword.toUtf8(), QCryptographicHash::Sha256).toHex();

    // Check if the new password and repeat password match
    if (newPassword != repeatPassword)
    {
        QMessageBox::critical(this, "Error", "New password and repeat password do not match.");
        return;
    }

    // Check if the username and current password are correct
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (dbobj.isOpen())
    {
        QSqlQuery query(dbobj);
        query.prepare("SELECT password FROM User WHERE username = :username");
        query.bindValue(":username", inputUsername);

        if (query.exec())
        {
            if (query.next())
            {
                QString storedHash = query.value(0).toString();

                if (currentPasswordHash == storedHash.toUtf8())
                {
                    // Update the password in the database
                    query.prepare("UPDATE User SET password = :newPassword WHERE username = :username");
                    query.bindValue(":newPassword", newPasswordHash);
                    query.bindValue(":username", inputUsername);

                    if (query.exec())
                    {
                        QMessageBox::information(this, "Success", "Password changed successfully.");
                        ui->Input_UserName->clear();
                        ui->Current_UserName->clear();
                        ui->Input_NewPass->clear();
                        ui->Input_RepeatPass->clear();
                    }
                    else
                    {
                        QMessageBox::critical(this, "Error", "Failed to update password in the database.");
                    }
                }
                else
                {
                    QMessageBox::critical(this, "Error", "Current password is incorrect.");
                }
            }
            else
            {
                QMessageBox::critical(this, "Error", "Username not found.");
            }
        }
        else
        {
            QMessageBox::critical(this, "Error", "Failed to retrieve user data:" + query.lastError().text());
        }
        dbobj.close();
    }
    else
    {
        QMessageBox::critical(this, "Error", "Connection Not Established.");
    }
}

/**
 * @brief RecoverPassword::centerOnScreen
 * Centers the window on the screen.
 */
void RecoverPassword::centerOnScreen()
{
    // Center the window on the screen
    QScreen *screenProject = QApplication::primaryScreen();
    QRect mainScreenGeometry = screenProject->availableGeometry();
    move(mainScreenGeometry.center() - rect().center());
}
