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
#include <QtWidgets/QLabel>
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
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_2;
    QLabel *label;
    QPushButton *pushButton_5;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ProjectCreation)
    {
        if (ProjectCreation->objectName().isEmpty())
            ProjectCreation->setObjectName("ProjectCreation");
        ProjectCreation->resize(1280, 720);
        ProjectCreation->setMinimumSize(QSize(1280, 720));
        ProjectCreation->setMaximumSize(QSize(1280, 720));
        centralwidget = new QWidget(ProjectCreation);
        centralwidget->setObjectName("centralwidget");
        textBrowser_2 = new QTextBrowser(centralwidget);
        textBrowser_2->setObjectName("textBrowser_2");
        textBrowser_2->setGeometry(QRect(130, 200, 121, 31));
        textBrowser_3 = new QTextBrowser(centralwidget);
        textBrowser_3->setObjectName("textBrowser_3");
        textBrowser_3->setGeometry(QRect(130, 80, 91, 41));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(250, 200, 181, 31));
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(130, 240, 181, 31));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(820, 90, 61, 31));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 150, 751, 41));
        QFont font;
        font.setBold(true);
        label->setFont(font);
        label->setFrameShape(QFrame::Box);
        label->setLineWidth(2);
        label->setMidLineWidth(7);
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(820, 160, 61, 16));
        lineEdit_3 = new QLineEdit(centralwidget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(130, 320, 181, 31));
        lineEdit_4 = new QLineEdit(centralwidget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(130, 280, 181, 31));
        ProjectCreation->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ProjectCreation);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 21));
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
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Key</p></body></html>", nullptr));
        textBrowser_3->setHtml(QCoreApplication::translate("ProjectCreation", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:700;\">Scrummy</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:6pt;\">Logo</span></p></body></html>", nullptr));
        lineEdit->setText(QCoreApplication::translate("ProjectCreation", "PROJECT1KEY", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("ProjectCreation", "Type Suggestive Text", nullptr));
        pushButton_2->setText(QCoreApplication::translate("ProjectCreation", "Back", nullptr));
        label->setText(QCoreApplication::translate("ProjectCreation", "Project Name 1", nullptr));
        pushButton_5->setText(QCoreApplication::translate("ProjectCreation", "Delete", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("ProjectCreation", "Notes Add Notes", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("ProjectCreation", "Master User 1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectCreation: public Ui_ProjectCreation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTCREATION_H
