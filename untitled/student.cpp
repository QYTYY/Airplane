#include "student.h"
#include <QString>
#include <QDebug>
Student::Student() {

}

void Student::display()
{
    qInfo()<<username<<password;
}
