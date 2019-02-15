/********************************************************************************
** Form generated from reading UI file 'taskGUI.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TASKGUI_H
#define UI_TASKGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_taskGUIClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *taskGUIClass)
    {
        if (taskGUIClass->objectName().isEmpty())
            taskGUIClass->setObjectName(QString::fromUtf8("taskGUIClass"));
        taskGUIClass->resize(600, 400);
        menuBar = new QMenuBar(taskGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        taskGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(taskGUIClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        taskGUIClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(taskGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        taskGUIClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(taskGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        taskGUIClass->setStatusBar(statusBar);

        retranslateUi(taskGUIClass);

        QMetaObject::connectSlotsByName(taskGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *taskGUIClass)
    {
        taskGUIClass->setWindowTitle(QApplication::translate("taskGUIClass", "taskGUI", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class taskGUIClass: public Ui_taskGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TASKGUI_H
