/********************************************************************************
** Form generated from reading UI file 'registration_window.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_WINDOW_H
#define UI_REGISTRATION_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registration_window
{
public:
    QWidget *centralwidget;
    QTextBrowser *display_password;
    QTextBrowser *display_registration;
    QTextBrowser *display_role;
    QTextBrowser *display_lastname;
    QTextBrowser *display_firstname;
    QTextBrowser *display_username;
    QLineEdit *input_firstname;
    QLineEdit *input_lastname;
    QLineEdit *input_username;
    QLineEdit *input_password;
    QLineEdit *input_role;
    QPushButton *back;
    QPushButton *next;
    QTextBrowser *display_error;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *registration_window)
    {
        if (registration_window->objectName().isEmpty())
            registration_window->setObjectName("registration_window");
        registration_window->resize(1280, 720);
        registration_window->setMinimumSize(QSize(1280, 720));
        registration_window->setMaximumSize(QSize(1280, 720));
        centralwidget = new QWidget(registration_window);
        centralwidget->setObjectName("centralwidget");
        display_password = new QTextBrowser(centralwidget);
        display_password->setObjectName("display_password");
        display_password->setGeometry(QRect(60, 320, 101, 41));
        display_registration = new QTextBrowser(centralwidget);
        display_registration->setObjectName("display_registration");
        display_registration->setGeometry(QRect(60, 100, 191, 51));
        display_role = new QTextBrowser(centralwidget);
        display_role->setObjectName("display_role");
        display_role->setGeometry(QRect(60, 370, 101, 41));
        display_lastname = new QTextBrowser(centralwidget);
        display_lastname->setObjectName("display_lastname");
        display_lastname->setGeometry(QRect(60, 220, 101, 41));
        display_firstname = new QTextBrowser(centralwidget);
        display_firstname->setObjectName("display_firstname");
        display_firstname->setGeometry(QRect(60, 170, 101, 41));
        display_username = new QTextBrowser(centralwidget);
        display_username->setObjectName("display_username");
        display_username->setGeometry(QRect(60, 270, 101, 41));
        input_firstname = new QLineEdit(centralwidget);
        input_firstname->setObjectName("input_firstname");
        input_firstname->setGeometry(QRect(180, 170, 211, 41));
        input_lastname = new QLineEdit(centralwidget);
        input_lastname->setObjectName("input_lastname");
        input_lastname->setGeometry(QRect(180, 220, 211, 41));
        input_username = new QLineEdit(centralwidget);
        input_username->setObjectName("input_username");
        input_username->setGeometry(QRect(180, 270, 211, 41));
        input_password = new QLineEdit(centralwidget);
        input_password->setObjectName("input_password");
        input_password->setGeometry(QRect(180, 320, 211, 41));
        input_role = new QLineEdit(centralwidget);
        input_role->setObjectName("input_role");
        input_role->setGeometry(QRect(180, 370, 211, 41));
        back = new QPushButton(centralwidget);
        back->setObjectName("back");
        back->setGeometry(QRect(140, 500, 121, 41));
        next = new QPushButton(centralwidget);
        next->setObjectName("next");
        next->setGeometry(QRect(270, 500, 121, 41));
        display_error = new QTextBrowser(centralwidget);
        display_error->setObjectName("display_error");
        display_error->setGeometry(QRect(60, 420, 331, 51));
        registration_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(registration_window);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 21));
        registration_window->setMenuBar(menubar);
        statusbar = new QStatusBar(registration_window);
        statusbar->setObjectName("statusbar");
        registration_window->setStatusBar(statusbar);

        retranslateUi(registration_window);

        QMetaObject::connectSlotsByName(registration_window);
    } // setupUi

    void retranslateUi(QMainWindow *registration_window)
    {
        registration_window->setWindowTitle(QCoreApplication::translate("registration_window", "MainWindow", nullptr));
        display_password->setHtml(QCoreApplication::translate("registration_window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Password</span></p></body></html>", nullptr));
        display_registration->setHtml(QCoreApplication::translate("registration_window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt; font-weight:700;\">Registration</span></p></body></html>", nullptr));
        display_role->setHtml(QCoreApplication::translate("registration_window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Role</span></p></body></html>", nullptr));
        display_lastname->setHtml(QCoreApplication::translate("registration_window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Last Name</span></p></body></html>", nullptr));
        display_firstname->setHtml(QCoreApplication::translate("registration_window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">First Name</span></p></body></html>", nullptr));
        display_username->setHtml(QCoreApplication::translate("registration_window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:11pt;\">Username</span></p></body></html>", nullptr));
        input_firstname->setText(QString());
        back->setText(QCoreApplication::translate("registration_window", "Back", nullptr));
        next->setText(QCoreApplication::translate("registration_window", "Next", nullptr));
        display_error->setHtml(QCoreApplication::translate("registration_window", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">    </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registration_window: public Ui_registration_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_WINDOW_H
