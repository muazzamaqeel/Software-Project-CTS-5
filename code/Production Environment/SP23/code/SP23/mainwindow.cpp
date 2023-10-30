#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include "registration_window.h"


//Constructor of MainWindow Class
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //For Background
    QPixmap pix("C:/programming/SP23/1.jpg");
    ui->bg_main->setPixmap(pix);

    //Using the connect function to call the openRegistrationWindow() function
    connect(ui->registerbutton_main, SIGNAL(clicked()), this, SLOT(openRegistrationWindow()));
}

//Function that opens the registration_window
void MainWindow::openRegistrationWindow()
{
    //qDebug() << "Register button clicked.";

    //Took a while to do this, but this is the way to close the MainWindow screen when the registeration window is opened
    close();

    // Create an instance of the registration window
    registration_window* registrationWindow = new registration_window;
    registrationWindow->showMaximized();
}

//Destructor to avoid memory leak problems
MainWindow::~MainWindow()
{
    delete ui;
}
