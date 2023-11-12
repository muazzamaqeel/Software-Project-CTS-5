/********************************************************************************
** Form generated from reading UI file 'projectcreation.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTCREATION_H
#define UI_PROJECTCREATION_H

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

class Ui_ProjectCreation
{
public:
    QWidget *centralwidget;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_3;
    QLineEdit *lineEdit;
    QTextBrowser *textBrowser_4;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ProjectCreation)
    {
        if (ProjectCreation->objectName().isEmpty())
            ProjectCreation->setObjectName("ProjectCreation");
        ProjectCreation->resize(1193, 672);
        centralwidget = new QWidget(ProjectCreation);
        centralwidget->setObjectName("centralwidget");
        textBrowser_2 = new QTextBrowser(centralwidget);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setGeometry(QRect(130, 200, 121, 31));
        textBrowser_3 = new QTextBrowser(centralwidget);
        textBrowser_3->setObjectName("textBrowser_3");
        textBrowser_3->setGeometry(QRect(130, 80, 301, 51));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(250, 200, 181, 31));
        textBrowser_4 = new QTextBrowser(centralwidget);
        textBrowser_4->setObjectName("textBrowser_4");
        textBrowser_4->setGeometry(QRect(130, 230, 121, 31));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(250, 230, 181, 31));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(250, 260, 181, 31));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(250, 310, 181, 31));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(730, 310, 181, 31));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(730, 350, 181, 31));
        ProjectCreation->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ProjectCreation);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1193, 22));
        ProjectCreation->setMenuBar(menubar);
        statusbar = new QStatusBar(ProjectCreation);
        statusbar->setObjectName("statusbar");
        ProjectCreation->setStatusBar(statusbar);

        retranslateUi(ProjectCreation);

        QMetaObject::connectSlotsByName(ProjectCreation);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectCreation)
    {
        ProjectCreation->setWindowTitle(QCoreApplication::translate("ProjectCreation", "MainWindow", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("ProjectCreation", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Project Name</p></body></html>", nullptr));
        textBrowser_3->setHtml(QCoreApplication::translate("ProjectCreation", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">Scrummy</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:6pt;\">Logo</span></p></body></html>", nullptr));
        lineEdit->setText(QCoreApplication::translate("ProjectCreation", "Replace this text", nullptr));
        textBrowser_4->setHtml(QCoreApplication::translate("ProjectCreation", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Key</p></body></html>", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("ProjectCreation", "Replace this text", nullptr));
        pushButton->setText(QCoreApplication::translate("ProjectCreation", "Add Project", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ProjectCreation", "Back", nullptr));
        pushButton_3->setText(QCoreApplication::translate("ProjectCreation", "Settings", nullptr));
        pushButton_4->setText(QCoreApplication::translate("ProjectCreation", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectCreation: public Ui_ProjectCreation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTCREATION_H
