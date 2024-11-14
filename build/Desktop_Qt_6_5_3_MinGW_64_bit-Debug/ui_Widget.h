/********************************************************************************
** Form generated from reading UI file 'Widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QStackedWidget *stackedWidget;
    QWidget *menu;
    QPushButton *login;
    QLabel *label;
    QPushButton *pushButton_4;
    QTextEdit *username;
    QTextEdit *password;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *register_2;
    QPushButton *pushButton_3;
    QWidget *page;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(960, 640);
        Widget->setMinimumSize(QSize(960, 640));
        Widget->setMaximumSize(QSize(960, 640));
        Widget->setStyleSheet(QString::fromUtf8("	QStackWidget#menu\n"
"{\n"
"	background-image: url(:/image/background.png);}"));
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 960, 640));
        stackedWidget->setMinimumSize(QSize(960, 640));
        stackedWidget->setMaximumSize(QSize(960, 640));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/plane.png);"));
        menu = new QWidget();
        menu->setObjectName("menu");
        menu->setStyleSheet(QString::fromUtf8("background-image: url(:/new/prefix1/image/plane.png);"));
        login = new QPushButton(menu);
        login->setObjectName("login");
        login->setGeometry(QRect(390, 410, 181, 41));
        label = new QLabel(menu);
        label->setObjectName("label");
        label->setGeometry(QRect(180, 20, 611, 111));
        label->setStyleSheet(QString::fromUtf8("font: 48pt \"Microsoft YaHei UI\";"));
        pushButton_4 = new QPushButton(menu);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setGeometry(QRect(390, 480, 181, 41));
        username = new QTextEdit(menu);
        username->setObjectName("username");
        username->setGeometry(QRect(340, 250, 281, 51));
        username->setStyleSheet(QString::fromUtf8("font: 20pt \"Microsoft YaHei UI\";"));
        password = new QTextEdit(menu);
        password->setObjectName("password");
        password->setGeometry(QRect(340, 320, 281, 51));
        password->setStyleSheet(QString::fromUtf8("font: 20pt \"Microsoft YaHei UI\";"));
        label_2 = new QLabel(menu);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(270, 250, 71, 51));
        label_2->setStyleSheet(QString::fromUtf8("font: 20pt \"Microsoft YaHei UI\";"));
        label_3 = new QLabel(menu);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(270, 320, 71, 51));
        label_3->setStyleSheet(QString::fromUtf8("font: 20pt \"Microsoft YaHei UI\";"));
        stackedWidget->addWidget(menu);
        register_2 = new QWidget();
        register_2->setObjectName("register_2");
        pushButton_3 = new QPushButton(register_2);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(360, 250, 75, 23));
        stackedWidget->addWidget(register_2);
        page = new QWidget();
        page->setObjectName("page");
        stackedWidget->addWidget(page);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        login->setText(QCoreApplication::translate("Widget", "\347\231\273\345\275\225/\346\263\250\345\206\214", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\350\210\252\347\217\255\346\237\245\350\257\242\344\270\216\347\245\250\345\212\241\347\256\241\347\220\206", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Widget", "\351\200\200\345\207\272", nullptr));
        username->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:20pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        password->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:20pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:9pt;\"><br /></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\350\264\246\345\217\267\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\345\257\206\347\240\201\357\274\232", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Widget", "\345\217\221\345\260\204\347\202\271\345\217\221\345\260\204\347\202\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
