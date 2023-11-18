#include "parentboard.h"
#include "ui_parentboard.h"

#include "mainwindow.h"
#include "sprints.h"
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>

parentboard::parentboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::parentboard)
{
    ui->setupUi(this);

    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(goBackToMainWindow()));

    QPixmap pix("../softwareproject/code/Staging_Environment/Recovered/Staging_Environment_Recorverd/assets/Logo.svg");
    if (pix.isNull()) {
        qDebug() << "Failed to load Logo.svg";
    } else {
        qDebug() << "Loaded Logo.svg successfully";
        ui->logo->setPixmap(pix);
    }



}

parentboard::~parentboard()
{
    delete ui;
}

// Rest of your functions remain unchanged...

// Rest of your functions remain unchanged...



    void parentboard::on_taskboardButton_clicked()
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    
    void parentboard::on_backlogButton_clicked()
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    
    void parentboard::on_sprintsButton_clicked()
    {
            ui->stackedWidget->setCurrentIndex(2);




        ///Muazzam
        ///In order to open a window on top of another window
        // Sprints *sprintsWindow = new Sprints(this); // Assuming Sprint is a QDialog or QWidget
        // Set the sprint window as a modal to block interaction with parentboard window
        // sprintsWindow->setWindowModality(Qt::WindowModal);
        // Show the sprint window
        //sprintsWindow->show();
    
    }



    ///Cosmin

    // Settings button might not make it to the other windows besides MainWindow
    //void parentboard::openSettings()
    //{

    //        close();
    //        Settings* settingWindow = new Settings;
    //        settingWindow -> showMaximized();

    //}

    //void parentboard::goBackToParentBoard()
    //{
    //        hide(); // Hide the settings window
    //        parentboard* parentBoard = new parentboard;
    //        parentBoard->showMaximized();
    //}

    //to be replaced with the Projects window

void parentboard::on_confluenceButton_clicked()
{
        ui->stackedWidget->setCurrentIndex(3);
}



void parentboard::goBackToMainWindow()
{
        close(); // Hide the ParentBoard window
        MainWindow* mainWindow = new MainWindow; // Create a new instance of the main window
        mainWindow->showMaximized(); // Show the main window
}






