#include "Widget.h"
#include "ui_Widget.h"
#include <QKeyEvent>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QString>
#include <student.h>
#include <QList>
#include <mainwindow.h>
#include <QMessageBox>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
   loadData("D:\\数据结构课设\\plane\\untitled\\user.txt");
}
Widget::~Widget()
{
    delete ui;
}

void Widget::loadData(const QString &filename)
{
    QFile file(filename);
    //打开文件
    if(!file.open(QIODevice::ReadOnly)){
        qInfo()<<"open file failed";
            return;
    }
    //读取数据
    while(!file.atEnd()){
        auto lineData = file.readLine().trimmed();
        auto s = new Student;
        s->username = lineData;
         lineData = file.readLine().trimmed();
        s->password = lineData;
        m_students.push_back(s);

    }

}

void Widget::on_pushButton_4_released()
{
    close();//关闭窗口
}




void Widget::on_login_released()
{

    int re=0;

    auto username = ui->username->toPlainText();
    auto password = ui->password->toPlainText();

    //用户名不能为空
    if(username.isEmpty()){
        QMessageBox::information(this, "提示", "用户名不能为空！");
        return;
    }
    //密码不能为空
    if(password.isEmpty()){
       QMessageBox::information(this, "提示", "密码不能为空！");
        return;
    }

    //验证用户名和密码是否正确
    for(auto s : m_students){
        QString str = s->username;
        if(username==str){
            re=1;
            QString pas = s->password;
            if(pas==password){
                QMessageBox::information(this, "提示", "登录成功！");
                this->close();
                MainWindow* f = new MainWindow();
                f->show();
            }
            break;
        }
    }

    if(re == 0) {
        QFile file("D:\\数据结构课设\\plane\\untitled\\user.txt");
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            qInfo() << "Open file failed: " << file.errorString();
            return;
        }

        QTextStream out(&file);
        QString pas = password;
        QString us = username;
        out << us << "\n" << pas << "\n";
        QMessageBox::information(this, "提示", "注册成功！");
        file.close();
        this->loadData("D:\\数据结构课设\\plane\\untitled\\user.txt");
        //this->close();
        //flight *f = new flight();
        //f->show();
    }

}










