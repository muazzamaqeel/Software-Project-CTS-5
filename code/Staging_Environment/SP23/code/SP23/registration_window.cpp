#include "registration_window.h"
#include "ui_registration_window.h"
#include <QPixmap>
#include "mainwindow.h"
#include <QDebug> // Include this for debugging output

// Constructor for the registration window
registration_window::registration_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registration_window)
{
    ui->setupUi(this); // Set up the user interface
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
    hide(); // Hide the registration window
    MainWindow* mainWindow = new MainWindow; // Create a new instance of the main window
    mainWindow->showMaximized(); // Show the main window
}

// Function to store user input values and display them for testing
void registration_window::storeInputValues() {
    // Capture user input from various fields
    firstName = ui->input_firstname->text();
    lastName = ui->input_lastname->text();
    password = ui->input_password->text();
    role = ui->input_role->text();
    username = ui->input_username->text();

    // Print the captured values to the console for testing
    qDebug() << "First Name: " << firstName;
    qDebug() << "Last Name: " << lastName;
    qDebug() << "Password: " << password;
    qDebug() << "Role: " << role;
    qDebug() << "Username: " << username;
}
