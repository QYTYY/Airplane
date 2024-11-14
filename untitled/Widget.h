#ifndef WIDGET_H
#define WIDGET_H

#include "student.h"
#include <QWidget>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void loadData(const QString& filename);
    QList<Student*> m_students;

private slots:

    void on_pushButton_4_released();

    void on_login_released();


private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
