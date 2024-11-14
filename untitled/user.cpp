#include "user.h"


QVector<FlightTicket> createFlightSchedule(const std::vector<QString>& cities, const Flight& firstFlight, const FlightSchedule& flightSchedule, int startDate) {
    QVector<FlightTicket> scheduledTickets;  // 存储 FlightTicket 对象
    Flight ff = firstFlight;
    FlightTicket firstTicket(ff, startDate);  // 创建第一个 FlightTicket
    scheduledTickets.append(firstTicket);     // 添加第一个航班的 FlightTicket

    int nextDate = startDate;
    nextDate = nextDate % 7;  // 确保 nextDate 在 1 到 7 之间

    QTime lastArrivalTime;  // 保存上一个航班的到达时间

    // 从第二个城市开始
    for (int i = 1; i < cities.size() - 1; i++) {
        // 获取上一个航班的到达时间
        if (scheduledTickets.isEmpty()) {
            qDebug() << "No valid flights found for the schedule.";
            return scheduledTickets;
        }

        lastArrivalTime = QTime::fromString(scheduledTickets.last().getFlight().arrivalTime, "HH:mm");
        qDebug() << "Flight has valid arrive time:" << lastArrivalTime.toString();

        if (!lastArrivalTime.isValid()) {
            qDebug() << "Invalid arrival time for the first flight.";
            return scheduledTickets; // 返回空的航班列表
        }

        QString departureCity = cities[i];  // 当前出发城市
        QString arrivalCity = cities[i + 1];  // 当前到达城市

        qDebug() << "Searching flights from" << departureCity << "to" << arrivalCity;

        // 查找从 departureCity 到 arrivalCity 的航班
        QVector<Flight> flights = flightSchedule.findFlightsByCity(departureCity, arrivalCity);
        if (flights.isEmpty()) {
            qDebug() << "No flights found between" << departureCity << "and" << arrivalCity;
            continue;
        }

        qDebug() << "Found" << flights.size() << "flights between" << departureCity << "and" << arrivalCity;

        bool flightScheduled = false;  // 用于检查是否安排了一个有效航班

        while (!flightScheduled) {
            for (auto& flight : flights) {
                // 检查航班的出发时间
                QTime flightDepartureTime = QTime::fromString(flight.departureTime, "HH:mm");
                if (!flightDepartureTime.isValid()) {
                    qDebug() << "Invalid departure time for flight" << flight.flightNumber;
                    continue;
                }

                qDebug() << "Flight" << flight.flightNumber << "has valid departure time:" << flightDepartureTime.toString();

                bool isValidDay = true;

                // 计算时间间隔，并允许跨天飞行
                int arrivalSeconds = lastArrivalTime.hour() * 3600 + lastArrivalTime.minute() * 60; // 到达时间转换为秒
                int departureSeconds = flightDepartureTime.hour() * 3600 + flightDepartureTime.minute() * 60; // 出发时间转换为秒

                // 如果 departureSeconds 小于 arrivalSeconds，表示跨天，需要加上一天的秒数
                if (departureSeconds < arrivalSeconds) {
                    qDebug() << "跨天，调整日期";
                    isValidDay = false;
                    nextDate++;  // 跨天时，日期加1
                    if (nextDate > 7) {
                        nextDate = 1;  // 如果日期超过7，则重置为1（即星期一）
                    }
                }

                // 时间间隔大于两个小时（2 * 3600秒）
                if ((departureSeconds - arrivalSeconds) >= 2 * 3600 && isValidDay) {
                    qDebug() << "在同一天";
                    FlightTicket scheduledTicket(flight, nextDate);  // 创建一个新的 FlightTicket
                    scheduledTickets.append(scheduledTicket);  // 添加到 scheduledTickets 列表

                    lastArrivalTime = QTime::fromString(flight.arrivalTime, "HH:mm");  // 更新到达时间为当前航班的到达时间

                    flightScheduled = true;  // 标记已成功安排航班

                    // 如果飞机起飞和降落时间不在一天，日期要加1
                    QTime theFlightArrTime = QTime::fromString(flight.arrivalTime, "HH:mm");
                    int theArrSeconds = theFlightArrTime.hour() * 3600 + theFlightArrTime.minute() * 60;

                    if (theArrSeconds < departureSeconds) {
                        nextDate++;  // 跨天时，日期加1
                        if (nextDate > 7) {
                            nextDate = 1;  // 如果日期超过7，则重置为1（即星期一）
                        }
                    }
                    break;  // 找到一个符合条件的航班后跳出循环，继续检查下一个城市对
                } else {
                    int ti = departureSeconds + 24 * 3600;  // 加一天的秒数，处理跨天情况
                    if (!isValidDay && (ti - arrivalSeconds) >= 2 * 3600) {
                        qDebug() << "不在同一天";
                        FlightTicket scheduledTicket(flight, nextDate);  // 创建一个新的 FlightTicket
                        scheduledTickets.append(scheduledTicket);  // 添加到 scheduledTickets 列表

                        lastArrivalTime = QTime::fromString(flight.arrivalTime, "HH:mm");  // 更新到达时间为当前航班的到达时间
                        flightScheduled = true;  // 标记已成功安排航班

                        // 如果飞机起飞和降落时间不在一天，日期要加1
                        QTime theFlightArrTime = QTime::fromString(flight.arrivalTime, "HH:mm");
                        int theArrSeconds = theFlightArrTime.hour() * 3600 + theFlightArrTime.minute() * 60;
                        qDebug() << flightDepartureTime;
                        qDebug() << theFlightArrTime;
                        if (theArrSeconds < departureSeconds) {
                            qDebug() << "飞机跨天了";
                            nextDate++;  // 跨天时，日期加1
                            if (nextDate > 7) {
                                nextDate = 1;  // 如果日期超过7，则重置为1（即星期一）
                            }
                        }
                        break;  // 找到一个符合条件的航班后跳出循环，继续检查下一个城市对
                    }
                }
            }

            if (!flightScheduled) {
                qDebug() << "No valid flight scheduled between" << departureCity << "and" << arrivalCity;
            }
        }
    }

    qDebug() << "Flights successfully scheduled!";
    return scheduledTickets;  // 返回已安排的航班票列表
}








void UserManager::saveUsersToFileApp(const QString &filename) const
{

        QFile file(filename);
        if (!file.open(QIODevice::Append | QIODevice::Text)) { // 以写模式打开文件
            qDebug() << "Error: Could not open file for writing!";
            return;
        }

        QTextStream out(&file); // 使用 QTextStream 处理文本输出
        for (const auto& user : users) {
            // 获取用户信息及其航班信息
            QString userInfo = user.getUserInfoTxt();

            // 将用户信息写入文件，每个用户信息写入一行
            out << userInfo << "\n";
        }

        file.close(); // 关闭文件

}
void UserManager::saveUsersToFileWri(const QString &filename) const
{

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) { // 以写模式打开文件
        qDebug() << "Error: Could not open file for writing!";
        return;
    }

    QTextStream out(&file); // 使用 QTextStream 处理文本输出
    for (const auto& user : users) {
        // 获取用户信息及其航班信息
        QString userInfo = user.getUserInfoTxt();

        // 将用户信息写入文件，每个用户信息写入一行
        out << userInfo << "\n";
    }

    file.close(); // 关闭文件

}
void UserManager::clearUsers() {
    users.clear();
}
QVector<User> loadUsersFromFile(const QString &filename)
{
    QVector<User> users;  // 使用 QVector 存储所有用户
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error: Could not open file for reading!";
        return users;  // 返回空 QVector
    }

    QTextStream in(&file);
    QString line;
    User* currentUser = nullptr;
    QString name, idCard, flightNumber;
    int flightDate = 0;
    QString departureCity, arrivalCity;
    double departureLat = 0.0, departureLon = 0.0, arrivalLat = 0.0, arrivalLon = 0.0;
    int distanceKm = 0;
    QString airline, aircraftModel, avgDelay, delayTime;
    bool schedule[7] = {false};  // 默认为没有班期
    QString validFrom, validTo, departureAirport, arrivalAirport, departureTime, arrivalTime;

    while (!in.atEnd()) {
        line = in.readLine().trimmed();
        qDebug() << "Reading line: " << line;  // 输出读取的每一行

        // 解析用户信息
        if (line.startsWith("Name: ")) {
            // 完成当前用户的读取并加入列表
            if (currentUser) {
                users.append(*currentUser);  // 保存上一个用户
                // 输出用户信息
                qDebug() << "User Info - Name: " << currentUser->getName()
                         << ", ID Card: " << currentUser->getIdCard()
                         << ", Flight Number: " << currentUser->getFlightTicket().getFlight().flightNumber
                         << ", Flight Date: " << currentUser->getFlightTicket().getFlightDate();
            }
            name = line.mid(6);  // 提取姓名
            currentUser = nullptr;  // 清空当前用户
        }
        else if (line.startsWith("ID Card: ")) {
            idCard = line.mid(9);  // 提取身份证号
        }
        else if (line.startsWith("Flight Number: ")) {
            flightNumber = line.mid(15);  // 提取航班号
        }
        else if (line.startsWith("Flight Date: ")) {
            QString flightDateStr = line.mid(13).trimmed();  // 提取并去除前后空格
            qDebug() << "Raw Flight Date String: " << flightDateStr;  // 输出原始字符串

            // 尝试将字符串转换为整数
            bool isValidDate = false;
            int parsedDate = flightDateStr.toInt(&isValidDate);  // 转换为整数并验证
            qDebug()<<parsedDate;

            if (isValidDate && parsedDate >= 1 && parsedDate <= 7) {
                flightDate = parsedDate;  // 设置为有效的航班日期
                qDebug() << "Parsed Flight Date: " << flightDate;  // 打印解析后的日期
            } else {
                qDebug() << "Invalid Flight Date format or out of range!";  // 如果格式不正确或超出范围
                flightDate = -1;  // 设置无效日期
            }
        }
        else if (line.startsWith("Flight Info: ")) {
            QString flightInfo = line.mid(13);  // 提取航班信息

            // 假设 flightInfo 包含航班的各项细节，需要进一步解析
            QStringList flightInfoParts = flightInfo.split(":");
            if (flightInfoParts.size() >= 16) {
                for (int i = 0; i < flightInfoParts.size(); ++i) {
                    QString part = flightInfoParts[i].trimmed();
                    bool ok;
                    // 逐个字段读取
                    if (part.contains("Departure City")) {
                        departureCity = flightInfoParts[i + 1].trimmed();
                    } else if(part.contains("Departure Latitude")){
                        departureLat =flightInfoParts[i + 1].trimmed().toDouble(&ok);
                    }else if(part.contains("Departure Longitude")){
                        departureLon = flightInfoParts[i + 1].trimmed().toDouble(&ok);
                    }else if (part.contains("Arrival City")) {
                        arrivalCity = flightInfoParts[i + 1].trimmed();
                    } else if(part.contains("Arrival Latitude")){
                        arrivalLat = flightInfoParts[i + 1].trimmed().toDouble(&ok);
                    }else if(part.contains("Arrival Longitude")){
                        arrivalLon = flightInfoParts[i + 1].trimmed().toDouble(&ok);
                    }
                    else if (part.contains("Distance (km)")) {
                        distanceKm = flightInfoParts[i + 1].trimmed().toInt();
                    } else if (part.contains("Flight Number")) {
                        flightNumber = flightInfoParts[i + 1].trimmed();
                    } else if (part.contains("Airline")) {
                        airline = flightInfoParts[i + 1].trimmed();
                    } else if (part.contains("Aircraft Model")) {
                        aircraftModel = flightInfoParts[i + 1].trimmed();
                    } else if (part.contains("Average Delay")) {
                        avgDelay = flightInfoParts[i + 1].trimmed();
                    } else if (part.contains("Average Delay Time")) {
                        delayTime = flightInfoParts[i + 1].trimmed();
                    } else if (part.contains("Schedule (Mon-Sun)")) {
                        if (i + 1 < flightInfoParts.size()) {
                            QStringList scheduleParts = flightInfoParts[i + 1].trimmed().split(",");
                            for (int j = 0; j < scheduleParts.size(); ++j) {
                                schedule[j] = scheduleParts[j].trimmed() == "1";
                            }
                        }
                    } else if (part.contains("Valid From")) {
                        validFrom = flightInfoParts[i + 1].trimmed();
                    } else if (part.contains("Valid To")) {
                        validTo = flightInfoParts[i + 1].trimmed();
                    } else if (part.contains("Departure Airport")) {
                        departureAirport = flightInfoParts[i + 1].trimmed();
                    } else if (part.contains("Arrival Airport")) {
                        arrivalAirport = flightInfoParts[i + 1].trimmed();
                    } else if (part.startsWith("Departure Time")) {
                        departureTime = flightInfoParts[i + 1].trimmed()+":"+flightInfoParts[i + 2].trimmed();
                    } else if (part.contains("Arrival Time")) {
                        arrivalTime = flightInfoParts[i + 1].trimmed()+":"+flightInfoParts[i + 2].trimmed();
                    }
                }
            }

            // 构建 Flight 对象
            Flight flight(departureCity, departureLat, departureLon, arrivalCity, arrivalLat, arrivalLon,
                          distanceKm, flightNumber, airline, aircraftModel, avgDelay, delayTime,
                          schedule, validFrom, validTo, departureAirport, arrivalAirport, departureTime, arrivalTime);
            FlightTicket flightTicket(flight, flightDate);  // 构建 FlightTicket 对象

            // 创建 User 对象并保存
            currentUser = new User(name, idCard, flightTicket);
        }
    }

    // 加入最后一个用户并输出
    if (currentUser) {
        users.append(*currentUser);
        qDebug() << "User Info - Name: " << currentUser->getName()
                 << ", ID Card: " << currentUser->getIdCard()
                 << ", Flight : " << currentUser->getFlightTicket().getFlight().getInfo()
                 << ", Flight Date: " << currentUser->getFlightTicket().getFlightDate();
    }

    file.close();
    qDebug() << "Total users loaded:" << users.size();

    return users;
}




