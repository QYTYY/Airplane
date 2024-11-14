/********************************************************************************
** Form generated from reading UI file 'voya.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOYA_H
#define UI_VOYA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_voya
{
public:

    void setupUi(QWidget *voya)
    {
        if (voya->objectName().isEmpty())
            voya->setObjectName("voya");
        voya->resize(1510, 1250);
        voya->setMinimumSize(QSize(1510, 1250));
        voya->setMaximumSize(QSize(1510, 1250));

        retranslateUi(voya);

        QMetaObject::connectSlotsByName(voya);
    } // setupUi

    void retranslateUi(QWidget *voya)
    {
        voya->setWindowTitle(QCoreApplication::translate("voya", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class voya: public Ui_voya {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOYA_H
