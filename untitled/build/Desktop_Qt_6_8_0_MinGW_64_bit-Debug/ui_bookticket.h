/********************************************************************************
** Form generated from reading UI file 'bookticket.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOOKTICKET_H
#define UI_BOOKTICKET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BookTicket
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTextEdit *departure;
    QLabel *label_2;
    QTextEdit *arrive;
    QLabel *label_3;
    QTextEdit *plane_num;
    QPushButton *pushButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QMenuBar *menubar;

    void setupUi(QMainWindow *BookTicket)
    {
        if (BookTicket->objectName().isEmpty())
            BookTicket->setObjectName("BookTicket");
        BookTicket->resize(800, 600);
        centralwidget = new QWidget(BookTicket);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 91, 51));
        label->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        departure = new QTextEdit(centralwidget);
        departure->setObjectName("departure");
        departure->setGeometry(QRect(110, 10, 111, 41));
        departure->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(250, 0, 91, 51));
        label_2->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        arrive = new QTextEdit(centralwidget);
        arrive->setObjectName("arrive");
        arrive->setGeometry(QRect(360, 10, 121, 41));
        arrive->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 70, 91, 41));
        label_3->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        plane_num = new QTextEdit(centralwidget);
        plane_num->setObjectName("plane_num");
        plane_num->setGeometry(QRect(90, 70, 171, 41));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(570, 10, 91, 41));
        pushButton->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(0, 120, 801, 461));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 799, 459));
        scrollArea->setWidget(scrollAreaWidgetContents);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(370, 60, 151, 51));
        pushButton_2->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(560, 60, 211, 51));
        pushButton_3->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        BookTicket->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BookTicket);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        BookTicket->setMenuBar(menubar);

        retranslateUi(BookTicket);

        QMetaObject::connectSlotsByName(BookTicket);
    } // setupUi

    void retranslateUi(QMainWindow *BookTicket)
    {
        BookTicket->setWindowTitle(QCoreApplication::translate("BookTicket", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("BookTicket", "\345\207\272\345\217\221\345\237\216\345\270\202\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("BookTicket", "\345\210\260\350\276\276\345\237\216\345\270\202\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("BookTicket", "\350\210\252\347\217\255\345\217\267\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("BookTicket", "\346\237\245\350\257\242\350\210\252\347\217\255", nullptr));
        pushButton_2->setText(QCoreApplication::translate("BookTicket", "\350\275\254\346\234\272\350\207\252\345\212\250\350\256\242\347\245\250", nullptr));
        pushButton_3->setText(QCoreApplication::translate("BookTicket", "\346\237\245\347\234\213\350\207\252\345\212\250\350\256\242\347\245\250\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BookTicket: public Ui_BookTicket {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOOKTICKET_H
