/********************************************************************************
** Form generated from reading UI file 'parentboard.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARENTBOARD_H
#define UI_PARENTBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_parentboard
{
public:
    QLabel *label;
    QLabel *logo;
    QStackedWidget *stackedWidget;
    QWidget *taskboardPage;
    QLabel *selectorT;
    QLabel *selectorbarT;
    QLabel *toplabel;
    QPushButton *newtaskButton;
    QComboBox *sprintDropdown;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *backlogPage;
    QLabel *selectorB;
    QLabel *selectorbarB;
    QScrollArea *scrollAreaB;
    QWidget *scrollAreaWidgetContents_3;
    QLabel *toplabelB;
    QComboBox *sprintDropdownB;
    QPushButton *newissueButton;
    QWidget *sprintsPage;
    QLabel *selectorS;
    QLabel *selectorbarS;
    QWidget *confluencePage;
    QLabel *selectorC;
    QLabel *selectorbarC;
    QPushButton *exitButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *taskboardButton;
    QPushButton *backlogButton;
    QPushButton *sprintsButton;
    QPushButton *confluenceButton;

    void setupUi(QWidget *parentboard)
    {
        if (parentboard->objectName().isEmpty())
            parentboard->setObjectName("parentboard");
        parentboard->resize(1280, 720);
        parentboard->setMinimumSize(QSize(1280, 720));
        parentboard->setMaximumSize(QSize(1280, 720));
        label = new QLabel(parentboard);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 1280, 60));
        label->setMinimumSize(QSize(1280, 60));
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgb(200, 200, 200);\n"
"}"));
        logo = new QLabel(parentboard);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(20, 20, 150, 20));
        logo->setMinimumSize(QSize(150, 20));
        logo->setMaximumSize(QSize(150, 20));
        logo->setPixmap(QPixmap(QString::fromUtf8("../../../../../../../Wireframes/psd/Logo.svg")));
        logo->setScaledContents(true);
        logo->setAlignment(Qt::AlignCenter);
        logo->setIndent(0);
        stackedWidget = new QStackedWidget(parentboard);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 60, 1280, 1020));
        stackedWidget->setMinimumSize(QSize(1280, 1020));
        stackedWidget->setMaximumSize(QSize(1280, 1020));
        taskboardPage = new QWidget();
        taskboardPage->setObjectName("taskboardPage");
        selectorT = new QLabel(taskboardPage);
        selectorT->setObjectName("selectorT");
        selectorT->setGeometry(QRect(0, 0, 1280, 5));
        selectorT->setMinimumSize(QSize(100, 5));
        selectorT->setMaximumSize(QSize(1280, 5));
        selectorT->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgb(150, 150, 150);\n"
"}"));
        selectorbarT = new QLabel(taskboardPage);
        selectorbarT->setObjectName("selectorbarT");
        selectorbarT->setGeometry(QRect(190, 0, 100, 5));
        selectorbarT->setMinimumSize(QSize(100, 5));
        selectorbarT->setMaximumSize(QSize(999999, 5));
        selectorbarT->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgb(0, 255, 44);\n"
"}"));
        toplabel = new QLabel(taskboardPage);
        toplabel->setObjectName("toplabel");
        toplabel->setGeometry(QRect(0, 5, 1280, 60));
        toplabel->setMinimumSize(QSize(1280, 5));
        toplabel->setMaximumSize(QSize(1280, 60));
        toplabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
"font: 13pt \"Arial\";\n"
"background-color: rgb(200, 200, 200);\n"
"color: rgb(0, 0, 0);\n"
"}"));
        newtaskButton = new QPushButton(taskboardPage);
        newtaskButton->setObjectName("newtaskButton");
        newtaskButton->setGeometry(QRect(1190, 15, 80, 40));
        newtaskButton->setMinimumSize(QSize(80, 40));
        newtaskButton->setMaximumSize(QSize(80, 40));
        newtaskButton->setAutoFillBackground(false);
        newtaskButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font: 13pt \"Arial\";\n"
"background-color: rgb(100, 100, 100);\n"
"color: rgb(255, 255, 255);\n"
"}"));
        sprintDropdown = new QComboBox(taskboardPage);
        sprintDropdown->addItem(QString());
        sprintDropdown->addItem(QString());
        sprintDropdown->addItem(QString());
        sprintDropdown->setObjectName("sprintDropdown");
        sprintDropdown->setGeometry(QRect(10, 15, 250, 40));
        sprintDropdown->setMinimumSize(QSize(250, 40));
        sprintDropdown->setAutoFillBackground(false);
        sprintDropdown->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"font: 15pt \"Arial\";\n"
"background-color: rgb(100, 100, 100);\n"
"color: rgb(255, 255, 255);\n"
"}\n"
""));
        scrollArea = new QScrollArea(taskboardPage);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 65, 1280, 955));
        scrollArea->setMinimumSize(QSize(1280, 955));
        scrollArea->setMaximumSize(QSize(1280, 955));
        scrollArea->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font: 13pt \"Arial\";\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"}"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1278, 953));
        scrollArea->setWidget(scrollAreaWidgetContents);
        stackedWidget->addWidget(taskboardPage);
        backlogPage = new QWidget();
        backlogPage->setObjectName("backlogPage");
        selectorB = new QLabel(backlogPage);
        selectorB->setObjectName("selectorB");
        selectorB->setGeometry(QRect(0, 0, 1280, 5));
        selectorB->setMinimumSize(QSize(100, 5));
        selectorB->setMaximumSize(QSize(1280, 5));
        selectorB->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgb(150, 150, 150);\n"
"}"));
        selectorbarB = new QLabel(backlogPage);
        selectorbarB->setObjectName("selectorbarB");
        selectorbarB->setGeometry(QRect(290, 0, 100, 5));
        selectorbarB->setMinimumSize(QSize(100, 5));
        selectorbarB->setMaximumSize(QSize(999999, 5));
        selectorbarB->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgb(0, 255, 44);\n"
"}"));
        scrollAreaB = new QScrollArea(backlogPage);
        scrollAreaB->setObjectName("scrollAreaB");
        scrollAreaB->setGeometry(QRect(0, 65, 1280, 955));
        scrollAreaB->setMinimumSize(QSize(1280, 955));
        scrollAreaB->setMaximumSize(QSize(1280, 955));
        scrollAreaB->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font: 13pt \"Arial\";\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"}"));
        scrollAreaB->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 1278, 953));
        scrollAreaB->setWidget(scrollAreaWidgetContents_3);
        toplabelB = new QLabel(backlogPage);
        toplabelB->setObjectName("toplabelB");
        toplabelB->setGeometry(QRect(0, 5, 1280, 60));
        toplabelB->setMinimumSize(QSize(1280, 60));
        toplabelB->setMaximumSize(QSize(1280, 60));
        toplabelB->setStyleSheet(QString::fromUtf8("QLabel {\n"
"font: 13pt \"Arial\";\n"
"background-color: rgb(200, 200, 200);\n"
"color: rgb(0, 0, 0);\n"
"}"));
        sprintDropdownB = new QComboBox(backlogPage);
        sprintDropdownB->addItem(QString());
        sprintDropdownB->addItem(QString());
        sprintDropdownB->setObjectName("sprintDropdownB");
        sprintDropdownB->setGeometry(QRect(10, 15, 250, 40));
        sprintDropdownB->setMinimumSize(QSize(250, 40));
        sprintDropdownB->setAutoFillBackground(false);
        sprintDropdownB->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"font: 15pt \"Arial\";\n"
"background-color: rgb(100, 100, 100);\n"
"color: rgb(255, 255, 255);\n"
"}\n"
""));
        newissueButton = new QPushButton(backlogPage);
        newissueButton->setObjectName("newissueButton");
        newissueButton->setGeometry(QRect(1190, 15, 80, 40));
        newissueButton->setMinimumSize(QSize(80, 40));
        newissueButton->setMaximumSize(QSize(80, 40));
        newissueButton->setAutoFillBackground(false);
        newissueButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font: 13pt \"Arial\";\n"
"background-color: rgb(100, 100, 100);\n"
"color: rgb(255, 255, 255);\n"
"}"));
        stackedWidget->addWidget(backlogPage);
        sprintsPage = new QWidget();
        sprintsPage->setObjectName("sprintsPage");
        selectorS = new QLabel(sprintsPage);
        selectorS->setObjectName("selectorS");
        selectorS->setGeometry(QRect(0, 0, 1280, 5));
        selectorS->setMinimumSize(QSize(100, 5));
        selectorS->setMaximumSize(QSize(1280, 5));
        selectorS->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgb(150, 150, 150);\n"
"}"));
        selectorbarS = new QLabel(sprintsPage);
        selectorbarS->setObjectName("selectorbarS");
        selectorbarS->setGeometry(QRect(390, 0, 100, 5));
        selectorbarS->setMinimumSize(QSize(100, 5));
        selectorbarS->setMaximumSize(QSize(999999, 5));
        selectorbarS->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgb(0, 255, 44);\n"
"}"));
        stackedWidget->addWidget(sprintsPage);
        confluencePage = new QWidget();
        confluencePage->setObjectName("confluencePage");
        selectorC = new QLabel(confluencePage);
        selectorC->setObjectName("selectorC");
        selectorC->setGeometry(QRect(0, 0, 1280, 5));
        selectorC->setMinimumSize(QSize(100, 5));
        selectorC->setMaximumSize(QSize(1280, 5));
        selectorC->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgb(150, 150, 150);\n"
"}"));
        selectorbarC = new QLabel(confluencePage);
        selectorbarC->setObjectName("selectorbarC");
        selectorbarC->setGeometry(QRect(490, 0, 100, 5));
        selectorbarC->setMinimumSize(QSize(100, 5));
        selectorbarC->setMaximumSize(QSize(999999, 5));
        selectorbarC->setStyleSheet(QString::fromUtf8("QLabel {\n"
"background-color: rgb(0, 255, 44);\n"
"}"));
        stackedWidget->addWidget(confluencePage);
        exitButton = new QPushButton(parentboard);
        exitButton->setObjectName("exitButton");
        exitButton->setGeometry(QRect(1190, 10, 80, 40));
        exitButton->setMinimumSize(QSize(80, 40));
        exitButton->setMaximumSize(QSize(80, 40));
        exitButton->setAutoFillBackground(false);
        exitButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font: 13pt \"Arial\";\n"
"background-color: rgb(100, 100, 100);\n"
"color: rgb(255, 255, 255);\n"
"}"));
        widget = new QWidget(parentboard);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 591, 61));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalLayout->setContentsMargins(190, 0, 0, 0);
        taskboardButton = new QPushButton(widget);
        taskboardButton->setObjectName("taskboardButton");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(taskboardButton->sizePolicy().hasHeightForWidth());
        taskboardButton->setSizePolicy(sizePolicy);
        taskboardButton->setMinimumSize(QSize(100, 60));
        taskboardButton->setMaximumSize(QSize(100, 60));
        taskboardButton->setAutoFillBackground(false);
        taskboardButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font: 13pt \"Arial\";\n"
"background-color: rgb(100, 100, 100);\n"
"color: rgb(255, 255, 255);\n"
"}"));
        taskboardButton->setAutoDefault(false);
        taskboardButton->setFlat(false);

        horizontalLayout->addWidget(taskboardButton);

        backlogButton = new QPushButton(widget);
        backlogButton->setObjectName("backlogButton");
        sizePolicy.setHeightForWidth(backlogButton->sizePolicy().hasHeightForWidth());
        backlogButton->setSizePolicy(sizePolicy);
        backlogButton->setMinimumSize(QSize(100, 60));
        backlogButton->setMaximumSize(QSize(100, 60));
        backlogButton->setAutoFillBackground(false);
        backlogButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font: 13pt \"Arial\";\n"
"background-color: rgb(100, 100, 100);\n"
"color: rgb(255, 255, 255);\n"
"}"));
        backlogButton->setAutoDefault(false);
        backlogButton->setFlat(false);

        horizontalLayout->addWidget(backlogButton);

        sprintsButton = new QPushButton(widget);
        sprintsButton->setObjectName("sprintsButton");
        sizePolicy.setHeightForWidth(sprintsButton->sizePolicy().hasHeightForWidth());
        sprintsButton->setSizePolicy(sizePolicy);
        sprintsButton->setMinimumSize(QSize(100, 60));
        sprintsButton->setMaximumSize(QSize(100, 60));
        sprintsButton->setAutoFillBackground(false);
        sprintsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font: 13pt \"Arial\";\n"
"background-color: rgb(100, 100, 100);\n"
"color: rgb(255, 255, 255);\n"
"}"));
        sprintsButton->setAutoDefault(false);
        sprintsButton->setFlat(false);

        horizontalLayout->addWidget(sprintsButton);

        confluenceButton = new QPushButton(widget);
        confluenceButton->setObjectName("confluenceButton");
        sizePolicy.setHeightForWidth(confluenceButton->sizePolicy().hasHeightForWidth());
        confluenceButton->setSizePolicy(sizePolicy);
        confluenceButton->setMinimumSize(QSize(100, 60));
        confluenceButton->setMaximumSize(QSize(100, 60));
        confluenceButton->setAutoFillBackground(false);
        confluenceButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"font: 13pt \"Arial\";\n"
"background-color: rgb(100, 100, 100);\n"
"color: rgb(255, 255, 255);\n"
"}"));
        confluenceButton->setAutoDefault(false);
        confluenceButton->setFlat(false);

        horizontalLayout->addWidget(confluenceButton);


        retranslateUi(parentboard);

        taskboardButton->setDefault(false);
        backlogButton->setDefault(false);
        sprintsButton->setDefault(false);
        confluenceButton->setDefault(false);


        QMetaObject::connectSlotsByName(parentboard);
    } // setupUi

    void retranslateUi(QWidget *parentboard)
    {
        parentboard->setWindowTitle(QCoreApplication::translate("parentboard", "Form", nullptr));
        label->setText(QString());
        logo->setText(QString());
        selectorT->setText(QString());
        selectorbarT->setText(QString());
        toplabel->setText(QString());
        newtaskButton->setText(QCoreApplication::translate("parentboard", "New Task", nullptr));
        sprintDropdown->setItemText(0, QCoreApplication::translate("parentboard", "All Sprints", nullptr));
        sprintDropdown->setItemText(1, QCoreApplication::translate("parentboard", " Sprint 1 Name", nullptr));
        sprintDropdown->setItemText(2, QCoreApplication::translate("parentboard", "Sprint 2 Name", nullptr));

        selectorB->setText(QString());
        selectorbarB->setText(QString());
        toplabelB->setText(QString());
        sprintDropdownB->setItemText(0, QCoreApplication::translate("parentboard", " Sprint 1 Name", nullptr));
        sprintDropdownB->setItemText(1, QCoreApplication::translate("parentboard", "Sprint 2 Name", nullptr));

        newissueButton->setText(QCoreApplication::translate("parentboard", "New Issue", nullptr));
        selectorS->setText(QString());
        selectorbarS->setText(QString());
        selectorC->setText(QString());
        selectorbarC->setText(QString());
        exitButton->setText(QCoreApplication::translate("parentboard", "Exit", nullptr));
        taskboardButton->setText(QCoreApplication::translate("parentboard", "Taskboard", nullptr));
        backlogButton->setText(QCoreApplication::translate("parentboard", "Backlog", nullptr));
        sprintsButton->setText(QCoreApplication::translate("parentboard", "Sprints", nullptr));
        confluenceButton->setText(QCoreApplication::translate("parentboard", "Confluence", nullptr));
    } // retranslateUi

};

namespace Ui {
    class parentboard: public Ui_parentboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARENTBOARD_H
