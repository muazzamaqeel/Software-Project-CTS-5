#include "registration_window.h"
#include "ui_registration_window.h"
#include <QPixmap>
#include "mainwindow.h"
#include <QDebug>


registration_window::registration_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registration_window)
{
    ui->setupUi(this);
    connect(ui->back, SIGNAL(clicked()), this, SLOT(FromRegToMainWindow())); // Connect the button to the local slot
    connect(ui->next, SIGNAL(clicked()), this, SLOT(storeInputValues()));

}

registration_window::~registration_window()
{
    delete ui;
}

void registration_window::closeApp()
{
    QApplication::quit();
}

void registration_window::FromRegToMainWindow()
{
    hide(); // Hide the registration window
    MainWindow* mainWindow = new MainWindow; // Creating a new instance of the main window
    mainWindow->showMaximized(); // Show the main window
}


void registration_window::storeInputValues() {
    firstName = ui->input_firstname->text();
    lastName = ui->input_lastname->text();
    password = ui->input_password->text();
    role = ui->input_role->text();
    username = ui->input_username->text();

    //Testing the functionality
    qDebug() << "First Name: " << firstName;
    qDebug() << "Last Name: " << lastName;
    qDebug() << "Password: " << password;
    qDebug() << "Role: " << role;
    qDebug() << "Username: " << username;

}

