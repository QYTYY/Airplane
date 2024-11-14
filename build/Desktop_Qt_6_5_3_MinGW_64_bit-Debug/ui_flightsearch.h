/********************************************************************************
** Form generated from reading UI file 'flightsearch.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLIGHTSEARCH_H
#define UI_FLIGHTSEARCH_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FlightSearch
{
public:
    QAction *flightDuration;
    QWidget *centralwidget;
    QTextEdit *departure;
    QTextEdit *arrive;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *shuchu;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *label_4;
    QPushButton *pushButton_4;
    QPushButton *zhuanji_duratime;
    QPushButton *zhuanji_rate;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FlightSearch)
    {
        if (FlightSearch->objectName().isEmpty())
            FlightSearch->setObjectName("FlightSearch");
        FlightSearch->resize(800, 600);
        flightDuration = new QAction(FlightSearch);
        flightDuration->setObjectName("flightDuration");
        centralwidget = new QWidget(FlightSearch);
        centralwidget->setObjectName("centralwidget");
        departure = new QTextEdit(centralwidget);
        departure->setObjectName("departure");
        departure->setGeometry(QRect(120, 10, 111, 41));
        departure->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        arrive = new QTextEdit(centralwidget);
        arrive->setObjectName("arrive");
        arrive->setGeometry(QRect(420, 10, 121, 41));
        arrive->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(170, 60, 81, 31));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 10, 81, 41));
        label->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(300, 10, 121, 41));
        label_2->setStyleSheet(QString::fromUtf8("font: 16pt \"Microsoft YaHei UI\";"));
        shuchu = new QTextEdit(centralwidget);
        shuchu->setObjectName("shuchu");
        shuchu->setGeometry(QRect(0, 150, 771, 421));
        shuchu->setStyleSheet(QString::fromUtf8("font: 10pt \"Microsoft YaHei UI\";"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 60, 81, 31));
        label_3->setStyleSheet(QString::fromUtf8("font: 14pt \"Microsoft YaHei UI\";"));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(310, 60, 91, 31));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(450, 60, 91, 31));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 100, 81, 31));
        label_4->setStyleSheet(QString::fromUtf8("font: 14pt \"Microsoft YaHei UI\";"));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(170, 100, 81, 31));
        zhuanji_duratime = new QPushButton(centralwidget);
        zhuanji_duratime->setObjectName("zhuanji_duratime");
        zhuanji_duratime->setGeometry(QRect(310, 100, 91, 31));
        zhuanji_rate = new QPushButton(centralwidget);
        zhuanji_rate->setObjectName("zhuanji_rate");
        zhuanji_rate->setGeometry(QRect(450, 100, 91, 31));
        FlightSearch->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(FlightSearch);
        statusbar->setObjectName("statusbar");
        FlightSearch->setStatusBar(statusbar);

        retranslateUi(FlightSearch);

        QMetaObject::connectSlotsByName(FlightSearch);
    } // setupUi

    void retranslateUi(QMainWindow *FlightSearch)
    {
        FlightSearch->setWindowTitle(QCoreApplication::translate("FlightSearch", "MainWindow", nullptr));
        flightDuration->setText(QCoreApplication::translate("FlightSearch", "in order of flightDuration", nullptr));
        pushButton->setText(QCoreApplication::translate("FlightSearch", "\346\214\211\346\227\266\351\227\264\345\205\210\345\220\216", nullptr));
        label->setText(QCoreApplication::translate("FlightSearch", "\345\207\272\345\217\221\345\237\216\345\270\202", nullptr));
        label_2->setText(QCoreApplication::translate("FlightSearch", "\345\210\260\350\276\276\345\237\216\345\270\202", nullptr));
        label_3->setText(QCoreApplication::translate("FlightSearch", "\347\233\264\351\243\236\346\237\245\350\257\242\357\274\232", nullptr));
        pushButton_2->setText(QCoreApplication::translate("FlightSearch", "\346\214\211\351\243\236\350\241\214\346\227\266\351\227\264", nullptr));
        pushButton_3->setText(QCoreApplication::translate("FlightSearch", "\346\214\211\345\207\206\347\202\271\347\216\207", nullptr));
        label_4->setText(QCoreApplication::translate("FlightSearch", "\350\275\254\346\234\272\346\237\245\350\257\242\357\274\232", nullptr));
        pushButton_4->setText(QCoreApplication::translate("FlightSearch", "\346\214\211\346\227\266\351\227\264\345\205\210\345\220\216", nullptr));
        zhuanji_duratime->setText(QCoreApplication::translate("FlightSearch", "\346\214\211\351\243\236\350\241\214\346\227\266\351\227\264", nullptr));
        zhuanji_rate->setText(QCoreApplication::translate("FlightSearch", "\346\214\211\345\207\206\347\202\271\347\216\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FlightSearch: public Ui_FlightSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLIGHTSEARCH_H
