/********************************************************************************
** Form generated from reading UI file 'issuecreation.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ISSUECREATION_H
#define UI_ISSUECREATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IssueCreation
{
public:
    QWidget *centralwidget;
    QPushButton *backButton;
    QTextEdit *descriptionTextEdit;
    QLabel *descriptionLabel;
    QLabel *nameLabel;
    QTextEdit *nameTextBox;
    QTextBrowser *display_registration;
    QLabel *commentsLabel;
    QTextEdit *commentTextEdit;
    QComboBox *priorityComboBox;
    QLabel *priorityLabel;
    QPushButton *createButton;
    QLabel *typeLabel;
    QCheckBox *taskCheck;
    QCheckBox *userStoryCheck;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *IssueCreation)
    {
        if (IssueCreation->objectName().isEmpty())
            IssueCreation->setObjectName("IssueCreation");
        IssueCreation->resize(800, 600);
        centralwidget = new QWidget(IssueCreation);
        centralwidget->setObjectName("centralwidget");
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(670, 20, 121, 41));
        descriptionTextEdit = new QTextEdit(centralwidget);
        descriptionTextEdit->setObjectName("descriptionTextEdit");
        descriptionTextEdit->setGeometry(QRect(60, 290, 301, 211));
        descriptionTextEdit->setFrameShape(QFrame::NoFrame);
        descriptionLabel = new QLabel(centralwidget);
        descriptionLabel->setObjectName("descriptionLabel");
        descriptionLabel->setGeometry(QRect(60, 270, 71, 16));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        descriptionLabel->setFont(font);
        nameLabel = new QLabel(centralwidget);
        nameLabel->setObjectName("nameLabel");
        nameLabel->setGeometry(QRect(60, 210, 71, 21));
        nameLabel->setFont(font);
        nameTextBox = new QTextEdit(centralwidget);
        nameTextBox->setObjectName("nameTextBox");
        nameTextBox->setGeometry(QRect(100, 210, 261, 31));
        nameTextBox->setFrameShape(QFrame::NoFrame);
        display_registration = new QTextBrowser(centralwidget);
        display_registration->setObjectName("display_registration");
        display_registration->setGeometry(QRect(60, 20, 221, 51));
        commentsLabel = new QLabel(centralwidget);
        commentsLabel->setObjectName("commentsLabel");
        commentsLabel->setGeometry(QRect(440, 340, 71, 16));
        commentsLabel->setFont(font);
        commentTextEdit = new QTextEdit(centralwidget);
        commentTextEdit->setObjectName("commentTextEdit");
        commentTextEdit->setGeometry(QRect(440, 360, 301, 81));
        commentTextEdit->setFrameShape(QFrame::NoFrame);
        priorityComboBox = new QComboBox(centralwidget);
        priorityComboBox->addItem(QString());
        priorityComboBox->addItem(QString());
        priorityComboBox->addItem(QString());
        priorityComboBox->addItem(QString());
        priorityComboBox->addItem(QString());
        priorityComboBox->setObjectName("priorityComboBox");
        priorityComboBox->setGeometry(QRect(440, 230, 131, 24));
        priorityLabel = new QLabel(centralwidget);
        priorityLabel->setObjectName("priorityLabel");
        priorityLabel->setGeometry(QRect(440, 210, 71, 16));
        priorityLabel->setFont(font);
        createButton = new QPushButton(centralwidget);
        createButton->setObjectName("createButton");
        createButton->setGeometry(QRect(440, 460, 191, 41));
        typeLabel = new QLabel(centralwidget);
        typeLabel->setObjectName("typeLabel");
        typeLabel->setGeometry(QRect(440, 270, 71, 21));
        typeLabel->setFont(font);
        taskCheck = new QCheckBox(centralwidget);
        taskCheck->setObjectName("taskCheck");
        taskCheck->setGeometry(QRect(560, 300, 77, 22));
        userStoryCheck = new QCheckBox(centralwidget);
        userStoryCheck->setObjectName("userStoryCheck");
        userStoryCheck->setGeometry(QRect(450, 300, 77, 22));
        IssueCreation->setCentralWidget(centralwidget);
        menubar = new QMenuBar(IssueCreation);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        IssueCreation->setMenuBar(menubar);
        statusbar = new QStatusBar(IssueCreation);
        statusbar->setObjectName("statusbar");
        IssueCreation->setStatusBar(statusbar);

        retranslateUi(IssueCreation);

        QMetaObject::connectSlotsByName(IssueCreation);
    } // setupUi

    void retranslateUi(QMainWindow *IssueCreation)
    {
        IssueCreation->setWindowTitle(QCoreApplication::translate("IssueCreation", "MainWindow", nullptr));
        backButton->setText(QCoreApplication::translate("IssueCreation", "Back", nullptr));
        descriptionTextEdit->setHtml(QCoreApplication::translate("IssueCreation", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Add a description...</p></body></html>", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("IssueCreation", "Description", nullptr));
        nameLabel->setText(QCoreApplication::translate("IssueCreation", "Name", nullptr));
        nameTextBox->setHtml(QCoreApplication::translate("IssueCreation", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Add a Name...</p></body></html>", nullptr));
        display_registration->setHtml(QCoreApplication::translate("IssueCreation", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:22pt; font-weight:700;\">Issue Creation</span></p></body></html>", nullptr));
        commentsLabel->setText(QCoreApplication::translate("IssueCreation", "Comments", nullptr));
        commentTextEdit->setHtml(QCoreApplication::translate("IssueCreation", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Add comments...</p></body></html>", nullptr));
        priorityComboBox->setItemText(0, QCoreApplication::translate("IssueCreation", "Lowest", nullptr));
        priorityComboBox->setItemText(1, QCoreApplication::translate("IssueCreation", "Low", nullptr));
        priorityComboBox->setItemText(2, QCoreApplication::translate("IssueCreation", "Medium", nullptr));
        priorityComboBox->setItemText(3, QCoreApplication::translate("IssueCreation", "High", nullptr));
        priorityComboBox->setItemText(4, QCoreApplication::translate("IssueCreation", "Highest", nullptr));

        priorityLabel->setText(QCoreApplication::translate("IssueCreation", "Priority", nullptr));
        createButton->setText(QCoreApplication::translate("IssueCreation", "Create Issue", nullptr));
        typeLabel->setText(QCoreApplication::translate("IssueCreation", "Type", nullptr));
        taskCheck->setText(QCoreApplication::translate("IssueCreation", "Task", nullptr));
        userStoryCheck->setText(QCoreApplication::translate("IssueCreation", "User Story", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IssueCreation: public Ui_IssueCreation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ISSUECREATION_H
