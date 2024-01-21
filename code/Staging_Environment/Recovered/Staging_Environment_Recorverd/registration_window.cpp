#include "registration_window.h"
#include "ui_registration_window.h"
#include "databasemanager.h" // Custom database manager class
#include <QPixmap>
#include "mainwindow.h"
#include <QDebug>
#include <QtSql/QSqlDatabase>
#include <QDebug>
#include <iostream>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QtSql/QSqlQuery>
#include <sstream>
#include <iomanip>
#include <QCryptographicHash>
#include <QGraphicsBlurEffect>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QKeyEvent>

// Constructor for the registration window
registration_window::registration_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registration_window)
{
    ui->setupUi(this); // Set up the user interface
    ui->display_error->setVisible(false); // Initially hide the error message
    ui->display_role->setVisible(false);
    ui->comboBox_role->setVisible(false);



    // For Background
    QPixmap pix("C:/programming/GIT-REPO-SP23/softwareproject/code/Staging_Environment/Recovered/Staging_Environment_Recorverd/assets/MainWindowbg.jpg");
    // Create a blur effect
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect;
    blurEffect->setBlurRadius(10); // Adjust the blur radius as needed

    // Create a scene and pixmap item
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(pix);
    item.setGraphicsEffect(blurEffect);

    // Render the scene to a new QPixmap
    scene.addItem(&item);
    QPixmap blurredPixmap(pix.size());
    blurredPixmap.fill(Qt::transparent);
    QPainter painter(&blurredPixmap);
    scene.render(&painter);

    // Set the blurred pixmap as the background
    ui->bg_main->setPixmap(blurredPixmap);




    connect(ui->back, SIGNAL(clicked()), this, SLOT(FromRegToMainWindow())); // Connect the "back" button to go back
    connect(ui->next, SIGNAL(clicked()), this, SLOT(storeInputValues())); // Connect the "next" button to store input values
}

// Destructor
registration_window::~registration_window()
{
    delete ui; // Clean up the user interface
}

// Function to close the application (not currently used in the code)
void registration_window::closeApp()
{
    QApplication::quit();
}

// Function to switch from the registration window to the main window
void registration_window::FromRegToMainWindow()
{

    MainWindow* mainWindow = new MainWindow; // Create a new instance of the main window
    hide(); // Hide the registration window
    mainWindow->showMaximized(); // Show the main window
    ui->~registration_window();
}



// Function to store user input values and display them for testing
void registration_window::storeInputValues() {
    // Capture user input from various fields
    firstName = ui->input_firstname->text();
    lastName = ui->input_lastname->text();
    password = ui->input_password->text();
    email = ui->input_email->text();
    username = ui->input_username->text();
    QString selectedOption = ui->comboBox_role->currentText();

    int roleid = -1;
    if (selectedOption == "Product Owner") {
        roleid = 2;
    } else if (selectedOption == "Scrum Master") {
        roleid = 1;
    } else if (selectedOption == "Team") {
        roleid = 3;
    } else {
        qDebug() << "Error with the combobox";
    }

    QString error = "";
    if (firstName.isEmpty() || lastName.isEmpty() || password.isEmpty() || email.isEmpty() || username.isEmpty()) {
        if (firstName.isEmpty()) {
            error += "<font color='red'>First Name is missing. </font>\n";
        }
        if (lastName.isEmpty()) {
            error += "<font color='red'>Last Name is missing. </font>\n";
        }
        if (password.isEmpty()) {
            error += "<font color='red'>Password is missing. </font>\n";
        }
        if (email.isEmpty()) {
            error += "<font color='red'>Email is missing. </font>\n";
        }
        if (username.isEmpty()) {
            error += "<font color='red'>Username is missing. </font>\n";
        }
        ui->display_error->setText(error);
        ui->display_error->setVisible(true);
    } else {
        ui->display_error->setVisible(false);

        // Hash the password using QCryptographicHash (SHA-256)
        QByteArray passwordData = password.toUtf8();
        QByteArray hashedPassword = QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256).toHex();

        DatabaseManager database;
        QSqlDatabase dbobj = database.getDatabase();

        if (dbobj.isOpen()) {
            QSqlQuery query(dbobj);
            query.prepare("SELECT Email FROM User");
            if (query.exec()) {
                qDebug() << "Emails fetched!";
            }

            if (!query.exec())
            {
                qDebug() << "Query execution error: " << query.lastError().text();
                return;
            }
            while (query.next())
            {
                if(query.value(0).toString() == email){
                    error += "<font color='red'>Email already registered. </font>\n";
                    ui->display_error->setText(error);
                    ui->display_error->setVisible(true);
                    return;
                }
            }

            query.prepare("INSERT INTO User (firstname, lastname, password, email, username) "
                          "VALUES (:firstname, :lastname, :password, :email, :username)");
            query.bindValue(":firstname", firstName);
            query.bindValue(":lastname", lastName);
            query.bindValue(":password", hashedPassword); // using hashed password
            query.bindValue(":email", email);
            query.bindValue(":username", username);

            if (query.exec()) {
                qDebug() << "Data inserted into User table successfully!";
            } else {
                qDebug() << "Failed to insert data into User table:" << query.lastError().text();
            }
            dbobj.close();
        } else {
            qDebug() << "Connection Not Established - Registration class!";
        }
    }
    FromRegToMainWindow();
}
