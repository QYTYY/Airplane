/********************************************************************************
** Form generated from reading UI file 'flight.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLIGHT_H
#define UI_FLIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_flight
{
public:
    QPushButton *pushButton;
    QToolButton *toolButton;

    void setupUi(QWidget *flight)
    {
        if (flight->objectName().isEmpty())
            flight->setObjectName("flight");
        flight->resize(960, 960);
        flight->setMinimumSize(QSize(960, 960));
        flight->setMaximumSize(QSize(960, 960));
        pushButton = new QPushButton(flight);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(70, 90, 56, 18));
        toolButton = new QToolButton(flight);
        toolButton->setObjectName("toolButton");
        toolButton->setGeometry(QRect(80, 170, 20, 18));

        retranslateUi(flight);

        QMetaObject::connectSlotsByName(flight);
    } // setupUi

    void retranslateUi(QWidget *flight)
    {
        flight->setWindowTitle(QCoreApplication::translate("flight", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("flight", "PushButton", nullptr));
        toolButton->setText(QCoreApplication::translate("flight", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class flight: public Ui_flight {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLIGHT_H
