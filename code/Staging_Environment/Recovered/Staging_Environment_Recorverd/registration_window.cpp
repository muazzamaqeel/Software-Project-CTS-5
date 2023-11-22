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

// Constructor for the registration window
registration_window::registration_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registration_window)
{
    ui->setupUi(this); // Set up the user interface
    ui->display_error->setVisible(false); // Initially hide the error message
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
    QString selectedOption = ui->comboBox_role->currentText(); // Get the text of the selected item

    // Capture user input from various fields
    firstName = ui->input_firstname->text();
    lastName = ui->input_lastname->text();
    password = ui->input_password->text();
    email = ui->input_email->text();
    username = ui->input_username->text();

    int roleid = -1;

    if (selectedOption == "Product Owner") {
        roleid =2;

    } else if (selectedOption == "Scrum Master") {

        roleid =1;
    } else if (selectedOption == "Team") {

        roleid =3;
    }else{
        qDebug() << "Error with the combobox";
    }

    qDebug() << "Role ID: " << roleid;


    QString error = "";

    // Check for missing fields
    if(firstName.isEmpty() || lastName.isEmpty()|| password.isEmpty() || email.isEmpty() || username.isEmpty()){
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
            error += "<font color='red'>Role is missing. </font>\n";
        }
        if (username.isEmpty()) {
            error += "<font color='red'>Username is missing. </font>\n";
        }

        // Display error message in the error text object
        ui->display_error->setText(error);

        // Show the error message
        ui->display_error->setVisible(true);
    } else {
        // Hide the error message if there are no missing fields
        ui->display_error->setVisible(false);

        // Create a DatabaseManager object and attempt to establish a database connection
        DatabaseManager database;
        QSqlDatabase dbobj = database.getDatabase();

        if (dbobj.isOpen()) {
            qDebug() << "Connection Established - Registration class!";

            // Prepare the SQL query to insert data into the User table
            QSqlQuery query(dbobj);

            // Construct the SQL command
            QString insertQuery = "INSERT INTO User (firstname, lastname, password, email, username, Role_idRole) "
                                  "VALUES (:firstname, :lastname, :password, :email, :username, :roleid)";

            // Prepare the query with the command
            query.prepare(insertQuery);

            // Bind values to the query placeholders
            query.bindValue(":firstname", firstName);
            query.bindValue(":lastname", lastName);
            query.bindValue(":password", password);
            query.bindValue(":email", email);
            query.bindValue(":username", username);
            query.bindValue(":email", email);
            query.bindValue(":roleid", roleid);



            // Execute the query
            if (query.exec()) {
                qDebug() << "Data inserted into User table successfully!";
            } else {
                qDebug() << "Failed to insert data into User table:" << query.lastError().text();
            }

            dbobj.close(); // Close the database connection
        } else {
            qDebug() << "Connection Not Established - Registration class!";
        }
    }
}
