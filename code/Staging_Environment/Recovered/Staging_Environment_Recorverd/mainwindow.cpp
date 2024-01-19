#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include "databasemanager.h"
#include "qsqlerror.h"
#include "qsqlquery.h"
#include "registration_window.h"
#include "settings.h"
#include "issuecreation.h"
#include "parentboard.h"
#include "adminstrator.h"
#include <QCryptographicHash>
#include "parentboard.h"
#include "teammember_projectswindow.h"
#include "teammember_projectswindow.h"
#include <QGraphicsBlurEffect>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QPixmap>
#include <QGraphicsBlurEffect>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPainter>


// Constructor of MainWindow Class
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->input_password->setEchoMode(QLineEdit::Password);

    QLabel bg_main;
    QPixmap pix("qrc:/MainWindowbg.png");

    if (!pix.isNull()) {
        // Create a blur effect
        QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect();
        blurEffect->setBlurRadius(30); // Increased blur radius for visibility

        // Create a scene and a pixmap item
        QGraphicsScene scene;
        scene.setSceneRect(pix.rect()); // Set the scene size to the pixmap size

        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pix);
        item->setGraphicsEffect(blurEffect);
        scene.addItem(item);

        // Render the scene with the blur effect into a new pixmap
        QPixmap blurred(pix.size());
        blurred.fill(Qt::transparent); // Ensure the pixmap is transparent
        QPainter painter(&blurred);
        scene.render(&painter, QRectF(), QRectF(0, 0, pix.width(), pix.height()));
        painter.end();

        // Set the blurred pixmap as the background
        bg_main.setPixmap(blurred);
    } else {
        // Handle the case where the image failed to load
        qDebug() << "Failed to load the image.";
    }



    //Buttons on the mainwindow
    // Using the connect function to call the openRegistrationWindow() function
    connect(ui->registerbutton_main, SIGNAL(clicked()), this, SLOT(openRegistrationWindow()));
    connect(ui->signIn_Button, SIGNAL(clicked()), this, SLOT(userEncryptedLogin()));
    connect(ui->settingsbutton_main, SIGNAL(clicked()), this, SLOT(openSettings()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(closeApp()));
    //temporary
    connect(ui->parentboardButton, SIGNAL(clicked()), this, SLOT(openParentBoard()));
    //temporary
    connect(ui->adminButton, SIGNAL(clicked()), this, SLOT(adminLogin()));

    connect(ui->signIn_Button, SIGNAL(clicked()), this, SLOT(onSignInButtonClicked()));

    ui->backlog_test->setVisible(false);
    ui->parentboardButton->setVisible(false);
    ui->adminButton->setVisible(false);
    ui->settingsbutton_main->setVisible(false);


}

void MainWindow::onSignInButtonClicked() {
    TeamMember_ProjectsWindow* TeamMember_ProjectsWindowObj = new  TeamMember_ProjectsWindow; // Add this line
    TeamMember_ProjectsWindowObj->~TeamMember_ProjectsWindow();
}


void MainWindow::openIssueWindow()
{
    hide();
    IssueCreation* openIssueWindow = new IssueCreation;
    openIssueWindow->showMaximized();
    ui->~MainWindow();
}

// Function that opens the registration_window
void MainWindow::openRegistrationWindow()
{
    // qDebug() << "Register button clicked.";

    // To close the MainWindow screen when the registration window is opened
    hide();

    // Create an instance of the registration window
    registration_window* registrationWindow = new registration_window;
    registrationWindow->showMaximized();
    ui->~MainWindow();
}

// Function that opens the settings_windows
void MainWindow::openSettings()
{
    hide();
    Settings* settingWindow = new Settings;
    settingWindow -> showMaximized();
    ui->~MainWindow();
}
void MainWindow::closeApp()
{
    QApplication::quit(); // This will close the application.
}

// Why is this defined here ? - Wesley
void Settings::goBackToMainWindow()
{
    hide(); // Hide the settings window
    MainWindow* mainWindow = new MainWindow; // Create a new instance of the main window
    mainWindow->showMaximized(); // Show the main window
}

//temporary - Cosmin
void MainWindow::openParentBoard()
{
    // qDebug() << "Project Selected";
    // To close the MainWindow screen when the parentboard window is opened
    hide();
    // Create an instance of the parentboard window
    parentboard* parentBoard = new parentboard;
    parentBoard->showMaximized();
    ui->~MainWindow();
}
// temporary - Cosmin
void MainWindow::adminLogin()
{
    // qDebug() << "Administrator button clicked.";
    // To close the MainWindow screen when the admininstrator window is opened
    hide();

    // Create an instance of the parentboard window
    adminstrator* adminLogin = new adminstrator;
    adminLogin->showMaximized();
    ui->~MainWindow();
}

void MainWindow::TeamMember_ProjectsWin() {
    // qDebug() << "Administrator button clicked.";
    // To close the MainWindow screen when the administrator window is opened
    hide();

    TeamMember_ProjectsWindow* TeamMemberobj = new TeamMember_ProjectsWindow;
    TeamMemberobj->setUsername(Pass_inputUsername); // Set the username before using the object
    TeamMemberobj->ProjectRetrieval(); // Call the retrieval function to use the username
    TeamMemberobj->showMaximized();

    ui->~MainWindow(); // Consider using delete ui; instead of directly calling the destructor
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
    if(event->modifiers() == (Qt::ControlModifier | Qt::AltModifier) && event->key() == Qt::Key_D) {
        ui->adminButton->setVisible(true);
    } else {
        //QMainWindow::keyPressEvent(event); // Call base class method for other key events
    }
}


void MainWindow::userEncryptedLogin()
{
    inputUsername = ui->input_username->text();

    QString inputPassword = ui->input_password->text();

    // Hash the input password using SHA-256
    QByteArray passwordData = inputPassword.toUtf8();
    QByteArray hashedInputPassword = QCryptographicHash::hash(passwordData, QCryptographicHash::Sha256).toHex();

    // Database operations to verify hashed passwords
    DatabaseManager database;
    QSqlDatabase dbobj = database.getDatabase();

    if (dbobj.isOpen()) {
        QSqlQuery query(dbobj);
        query.prepare("SELECT password FROM User WHERE username = :username");
        query.bindValue(":username", inputUsername);

        if (query.exec()) {
            if (query.next()) {
                QString storedHash = query.value(0).toString();
                qDebug() << "Input Hash: " << hashedInputPassword;
                qDebug() << "Stored Hash: " << storedHash;

                if (hashedInputPassword == storedHash.toUtf8()) {
                    qDebug() << "Password is correct.";
                    Pass_inputUsername = inputUsername; // Store the username
                    this->deleteLater();
                    Pass_inputUsername = inputUsername; // Store the username
                    TeamMember_ProjectsWin();
                } else {
                    qDebug() << "Password is incorrect.";
                }
            }
        } else {
            qDebug() << "Failed to retrieve user data:" << query.lastError().text();
        }
        dbobj.close();
    } else {
        qDebug() << "Connection Not Established - Login class!";
    }
}


// Destructor to avoid memory leak problems
MainWindow::~MainWindow()
{
    delete ui;
}
QLineEdit* MainWindow::getInput_Username(){
    return ui->input_username;
}

QLineEdit* MainWindow::getInput_Password(){
    return ui->input_password;
}


QString MainWindow::PassUsername(){
    return inputUsername;
}

void MainWindow::setPassUsername(const QString& username) {
    Pass_inputUsername = username; // Should be using the passed 'username', not 'inputUsername'
}


//Getter Functions to make the .ui components public

