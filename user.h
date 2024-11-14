#ifndef USER_H
#define USER_H
#include "qregularexpression.h"
#include <QMainWindow>
#include <flight.h>
#include <flightsearch.h>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <qfile.h>
#include <QFileSystemWatcher>
#include <QTextStream>
class FlightTicket {
public:
    // 构造函数：接受一个 Flight 对象和一个日期
    FlightTicket(const Flight& f, int date1) : flight(f), date(date1) {}

    // 获取航班信息（返回引用，避免复制）


    // 设置航班信息
    void setFlight(const Flight& f) {
        flight = f;
    }

    // 获取日期
    int getDate() const {
        return date;
    }

    // 设置日期
    void setDate(int date1) {
        date = date1;
    }
    Flight getFlight() const { return flight; }
    int getFlightDate() const { return date; }

    // 获取详细信息
    QString getInfo() const {
        // 假设 Flight 类有一个 `getInfo()` 函数来返回航班的详细信息
        QString flightInfo = flight.getInfo(); // 获取航班信息
        return QString("Flight Info: %1, Date: %2").arg(flightInfo).arg(date);
    }

private:
    Flight flight;  // 存储航班信息
    int date;       // 存储具体日期
};

class User {
public:
    // 构造函数
    User(const QString& name, const QString& idCard, const FlightTicket& flightTicket)
        : name(name), idCard(idCard), f(flightTicket) {}

    // 获取姓名
    QString getName() const { return name; }

    // 获取身份证号
    QString getIdCard() const { return idCard; }

    // 获取航班号
    QString getFlightNumber() const { return f.getFlight().flightNumber; }

    // 获取日期
    int getFlightDate() const { return f.getDate(); }
    FlightTicket getFlightTicket() const { return f; }

    // 返回用户信息
    QString getUserInfo() const {
        return "Name: " + name + "\n" +
               "ID Card: " + idCard + "\n" +
               "Flight Number: " + f.getFlight().flightNumber + "\n" +
               "Flight Date: " + QString::number(f.getDate()) + "\n" +
               "Flight Info: " + f.getFlight().getInfo();
    }
    QString getUserInfoTxt() const {
        return "Name: " + name + "\n" +
               "ID Card: " + idCard + "\n" +
               "Flight Number: " + f.getFlight().flightNumber + "\n" +
               "Flight Date: " + QString::number(f.getDate()) + "\n" +
               "Flight Info: " + f.getFlight().getInfoTxt();
    }

private:
    QString name;           // 用户姓名
    QString idCard;         // 身份证号
    FlightTicket f;         // 航班票信息
};



class UserManager {
public:
    // 添加用户
    void addUser(const User& user) {
        // 检查用户列表中是否已经有相同的身份证号和航班信息
        for (const auto& existingUser : users) {
            if (existingUser.getIdCard() == user.getIdCard() &&
                existingUser.getFlightNumber() == user.getFlightNumber() &&
                existingUser.getFlightDate() == user.getFlightDate()) {
                qDebug() << "User with this ID card and flight information already exists. Not adding.";
                return;  // 如果已经有相同用户，不再添加
            }
        }
        // 如果没有重复用户，则添加新用户
        users.append(user);
    }

    // 获取所有用户信息
    void printAllUsers() const {
        for (const auto& user : users) {
            qDebug() << user.getUserInfo();
        }
    }

    // 根据身份证号查找用户
    User* findUserByIdCard(const QString& idCard) {
        for (auto& user : users) {
            if (user.getIdCard() == idCard) {
                return &user; // 返回找到的用户
            }
        }
        return nullptr; // 未找到
    }
    // 返回所有用户
    const QList<User>& getAllUsers() const {
        return users;
    }

    // 删除用户的函数
    void removeUser(const QString& idCard) {
        for (int i = 0; i < users.size(); ++i) {
            if (users[i].getIdCard() == idCard) {
                users.removeAt(i); // 从列表中删除用户
                qDebug() << "User removed: " << idCard;
                break;
            }
        }
    }
    bool isEmpty() const {
        return users.isEmpty();  // QList::isEmpty() 检查容器是否为空
    }

    // 将用户信息保存到文本文件
    void saveUsersToFileApp(const QString& filename) const;
    void saveUsersToFileWri(const QString& filename) const;
    void clearUsers();


    // 从文件加载用户信息



private:
    QList<User> users; // 存放用户的列表
};

QVector<FlightTicket> createFlightSchedule(const std::vector<QString>& cities, const Flight& firstFlight, const FlightSchedule& flightSchedule, int startDate);
QVector<User> loadUsersFromFile(const QString& filename);
void setupFileWatcher(const QString &filename);





#endif // USER_H
