/********************************************************************************
** Form generated from reading UI file 'refund.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REFUND_H
#define UI_REFUND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_refund
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *refund)
    {
        if (refund->objectName().isEmpty())
            refund->setObjectName("refund");
        refund->resize(800, 600);
        centralwidget = new QWidget(refund);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(300, 220, 75, 23));
        refund->setCentralWidget(centralwidget);
        menubar = new QMenuBar(refund);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        refund->setMenuBar(menubar);
        statusbar = new QStatusBar(refund);
        statusbar->setObjectName("statusbar");
        refund->setStatusBar(statusbar);

        retranslateUi(refund);

        QMetaObject::connectSlotsByName(refund);
    } // setupUi

    void retranslateUi(QMainWindow *refund)
    {
        refund->setWindowTitle(QCoreApplication::translate("refund", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("refund", "refund", nullptr));
    } // retranslateUi

};

namespace Ui {
    class refund: public Ui_refund {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REFUND_H
