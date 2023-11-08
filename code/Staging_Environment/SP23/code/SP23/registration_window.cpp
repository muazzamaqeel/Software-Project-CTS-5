#include "registration_window.h"
#include "ui_registration_window.h"
#include <QPixmap>
#include "mainwindow.h"

registration_window::registration_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::registration_window)
{
    ui->setupUi(this);
    connect(ui->back, SIGNAL(clicked()), this, SLOT(FromRegToMainWindow())); // Connect the button to the local slot
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
    MainWindow* mainWindow = new MainWindow; // Create a new instance of the main window
    mainWindow->showMaximized(); // Show the main window
}
