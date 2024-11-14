/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionFlight_enquiry;
    QAction *action;
    QAction *actionRefund_a_ticket;
    QAction *actionMy_ticket;
    QAction *actionMy_voyage_records;
    QWidget *centralwidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menubar;
    QMenu *menufile;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionFlight_enquiry = new QAction(MainWindow);
        actionFlight_enquiry->setObjectName("actionFlight_enquiry");
        action = new QAction(MainWindow);
        action->setObjectName("action");
        actionRefund_a_ticket = new QAction(MainWindow);
        actionRefund_a_ticket->setObjectName("actionRefund_a_ticket");
        actionMy_ticket = new QAction(MainWindow);
        actionMy_ticket->setObjectName("actionMy_ticket");
        actionMy_voyage_records = new QAction(MainWindow);
        actionMy_voyage_records->setObjectName("actionMy_voyage_records");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 0, 801, 581));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 799, 579));
        scrollArea->setWidget(scrollAreaWidgetContents);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menufile = new QMenu(menubar);
        menufile->setObjectName("menufile");
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menufile->menuAction());
        menubar->addAction(menu->menuAction());
        menufile->addSeparator();
        menufile->addAction(actionFlight_enquiry);
        menufile->addAction(action);
        menu->addAction(actionMy_ticket);
        menu->addAction(actionMy_voyage_records);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionFlight_enquiry->setText(QCoreApplication::translate("MainWindow", "Flight enquiry", nullptr));
        action->setText(QCoreApplication::translate("MainWindow", "Book a flight ticket", nullptr));
        actionRefund_a_ticket->setText(QCoreApplication::translate("MainWindow", "Refund a ticket", nullptr));
        actionMy_ticket->setText(QCoreApplication::translate("MainWindow", "My ticket", nullptr));
        actionMy_voyage_records->setText(QCoreApplication::translate("MainWindow", "My voyage records", nullptr));
        menufile->setTitle(QCoreApplication::translate("MainWindow", "\344\270\273\350\217\234\345\215\225", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\210\221\347\232\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
