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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectCreation
{
public:
    QMenuBar *menubar;
    QWidget *centralwidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ProjectCreation)
    {
        if (ProjectCreation->objectName().isEmpty())
            ProjectCreation->setObjectName("ProjectCreation");
        ProjectCreation->resize(800, 600);
        menubar = new QMenuBar(ProjectCreation);
        menubar->setObjectName("menubar");
        ProjectCreation->setMenuBar(menubar);
        centralwidget = new QWidget(ProjectCreation);
        centralwidget->setObjectName("centralwidget");
        ProjectCreation->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ProjectCreation);
        statusbar->setObjectName("statusbar");
        ProjectCreation->setStatusBar(statusbar);

        retranslateUi(ProjectCreation);

        QMetaObject::connectSlotsByName(ProjectCreation);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectCreation)
    {
        ProjectCreation->setWindowTitle(QCoreApplication::translate("ProjectCreation", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectCreation: public Ui_ProjectCreation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTCREATION_H
