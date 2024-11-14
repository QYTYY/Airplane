#include "flight.h"
QString Flight::calculateFlightDuration() {
    // departureTime 和 arrivalTime 是 QString 类型的成员变量
    QTime depTime = QTime::fromString(departureTime, "HH:mm");
    QTime arrTime = QTime::fromString(arrivalTime, "HH:mm");

    if (!depTime.isValid() || !arrTime.isValid()) {
        qWarning() << "Invalid time format!";
        return "0";
    }

    int durationInMsecs = depTime.msecsTo(arrTime);
    if (durationInMsecs < 0) {
        durationInMsecs += 24 * 60 * 60 * 1000; // 处理跨天情况
    }

    int hours = durationInMsecs / (1000 * 60 * 60);
    int minutes = (durationInMsecs / (1000 * 60)) % 60;

    return QString("%1小时%2分钟").arg(hours).arg(minutes);
}
int Flight::getFlightDurationInMsecs() const {
    QTime depTime = QTime::fromString(departureTime, "HH:mm");
    QTime arrTime = QTime::fromString(arrivalTime, "HH:mm");

    if (!depTime.isValid() || !arrTime.isValid()) {
        return 0; // 返回 0 表示无效时间
    }

    int durationInMsecs = depTime.msecsTo(arrTime);
    if (durationInMsecs < 0) {
        durationInMsecs += 24 * 60 * 60 * 1000; // 处理跨天情况
    }

    return durationInMsecs;
}
QString Flight::getDepartureTime() const {
    QTime depTime = QTime::fromString(departureTime, "HH:mm");

    if (!depTime.isValid()) {
        return QString(); // 返回空字符串表示无效时间
    }

    return depTime.toString("HH:mm");
}


double Flight::getOnTimeRate() const {
    // 将字符串中的 "%" 替换为空
    QString rateStr = avgDelay;
    rateStr.replace("%", ""); // 使用 replace 方法

    // 将字符串转换为 double
    bool ok;
    double rate = rateStr.toDouble(&ok) / 100.0; // 转换并除以100
    return ok ? rate : 0.0; // 如果转换失败，返回 0.0
}

QString Flight::getInfo()  const{
    QString scheduleStr;
    for (int i = 0; i < 7; ++i) {
        scheduleStr += (schedule[i] ? "1" : "0");
        if (i < 6) scheduleStr += ", ";
    }

    QString info;
    info += "Departure City: " + departureCity + " ";
    info += "Arrival City: " + arrivalCity + " ";
    info += "Distance (km): " + QString::number(distanceKm) + " ";
    info += "Flight Number: " + flightNumber + " ";
    info += "Airline: " + airline + " ";
    info += "Aircraft Model: " + aircraftModel + " ";
    info += "Average Delay: " + avgDelay + " ";
    info += "Average Delay Time: " + delayTime + " ";
    info += "Schedule (Mon-Sun): " + scheduleStr + " ";
    info += "Valid From: " + validFrom + " ";
    info += "Valid To: " + validTo + " ";
    info += "Departure Airport: " + departureAirport + " ";
    info += "Arrival Airport: " + arrivalAirport + " ";
    info += "Departure Time: " + departureTime + " ";
    info += "Arrival Time: " + arrivalTime + " ";
    info += "Flight Duration: " + flightDuration; // 输出飞行时间
    return info;
}
QString Flight::getInfoTxt() const {
    QString scheduleStr;
    for (int i = 0; i < 7; ++i) {
        scheduleStr += (schedule[i] ? "1" : "0");
        if (i < 6) scheduleStr += ", ";
    }

    QString info;
    info += "Departure City: " + departureCity + ":";
    info += "Departure Latitude: " + QString::number(departureLat) + ":";
    info += "Departure Longitude: " + QString::number(departureLon) + ":";
    info += "Arrival City: " + arrivalCity + ":";
    info += "Arrival Latitude: " + QString::number(arrivalLat) + ":";
    info += "Arrival Longitude: " + QString::number(arrivalLon) + ":";
    info += "Distance (km): " + QString::number(distanceKm) + ":";
    info += "Flight Number: " + flightNumber + ":";
    info += "Airline: " + airline + ":";
    info += "Aircraft Model: " + aircraftModel + ":";
    info += "Average Delay: " + avgDelay + ":";
    info += "Average Delay Time: " + delayTime + ":";
    info += "Schedule (Mon-Sun): " + scheduleStr + ":";
    info += "Valid From: " + validFrom + ":";
    info += "Valid To: " + validTo + ":";
    info += "Departure Airport: " + departureAirport + ":";
    info += "Arrival Airport: " + arrivalAirport + ":";
    info += "Departure Time: " + departureTime + ":";
    info += "Arrival Time: " + arrivalTime + ":";
    info += "Flight Duration: " + flightDuration;

    return info;
}

bool readExcelFile(const QString& filePath, FlightSchedule& schedule) {
    QXlsx::Document xlsx(filePath);
    if (!xlsx.load()) {
        qWarning() << "Failed to load the Excel file!";
        return false;
    }

    // 从第二行开始读取数据（第一行为标题行）
    for (int row = 2; row <= xlsx.dimension().lastRow(); ++row) {
        QString depCity = xlsx.read(row, 1).toString();        // 出发城市
        double depLat = xlsx.read(row, 2).toDouble();          // 出发城市y
        double depLon = xlsx.read(row, 3).toDouble();          // 出发城市x
        QString arrCity = xlsx.read(row, 4).toString();        // 到达城市
        double arrLat = xlsx.read(row, 5).toDouble();          // 到达城市y
        double arrLon = xlsx.read(row, 6).toDouble();          // 到达城市x
        int distKm = xlsx.read(row, 7).toInt();                // 里程（公里）
        QString flightNum = xlsx.read(row, 8).toString();      // 航班班次
        QString airln = xlsx.read(row, 9).toString();          // 航空公司
        QString model = xlsx.read(row, 10).toString();         // 机型
        QString depTime = xlsx.read(row, 11).toString().left(5);       // 起飞时间
        QString arrTime = xlsx.read(row, 12).toString().left(5);       // 降落时间
        QString depAirport = xlsx.read(row, 13).toString();     // 起飞机场
        double depAirportLat = xlsx.read(row, 14).toDouble();  // 起飞机场y
        double depAirportLon = xlsx.read(row, 15).toDouble();  // 起飞机场x
        QString arrAirport = xlsx.read(row, 16).toString();     // 降落机场
        double arrAirportLat = xlsx.read(row, 17).toDouble();  // 降落机场y
        double arrAirportLon = xlsx.read(row, 18).toDouble();  // 降落机场x
        QString onTimeRate = xlsx.read(row, 19).toString();    // 准点率
        QString avgDelay = xlsx.read(row, 20).toString();      // 平均误点时间

        // 读取每周班期信息
        bool weekSchedule[7];
        QString daysOfWeek[7] = {"周一", "周二", "周三", "周四", "周五", "周六", "周日"};

        for (int i = 0; i < 7; ++i) {
            QString scheduleStr = xlsx.read(row, 21 + i).toString().trimmed(); // 去掉前后空格

            // 去掉“周一”、“周二”等前缀
            scheduleStr.remove(daysOfWeek[i]);
            if(scheduleStr.contains("没有班期")){
                weekSchedule[i] = false;
            }else{
                weekSchedule[i] = true;
            }

        }

        QString validFrom = xlsx.read(row, 28).toString();     // 航班有效期开始
        QString validTo = xlsx.read(row, 29).toString();       // 航班有效期结束

        // 创建 Flight 对象并添加到 FlightSchedule
        Flight flight(depCity, depLat, depLon, arrCity, arrLat, arrLon, distKm,
                      flightNum, airln, model, onTimeRate, avgDelay,weekSchedule, validFrom, validTo,
                      depAirport, arrAirport, depTime, arrTime);
        schedule.addFlight(flight);
    }
    return true;
}
void Graph::addFlight(const Flight& flight) {
    flights[flight.departureCity].append(flight); // 直接添加 Flight 对象
    cities.insert(flight.departureCity);          // 添加出发城市
    cities.insert(flight.arrivalCity);            // 添加到达城市
}
QList<Flight> Graph::findFlightsFromCity(const QString& city) const {
    if (flights.contains(city)) {
        return flights[city]; // 返回指定城市的航班列表
    }
    return QList<Flight>(); // 返回空列表，如果没有找到航班
}
void Graph::printAllFlights() const {
    for (const auto& depCity : flights.keys()) {
        qDebug() << "From:" << depCity;
        for (const auto& flight : flights[depCity]) {
            qDebug() << "  To:" << flight.arrivalCity;
        }
    }
}
void Graph::printAllCities() const {
    qDebug() << "Cities in the graph:";
    for (const auto& city : cities) {
        qDebug() << city;
    }

}
std::vector<QString> Graph::dijkstra(const QString& startCity, const QString& endCity) const {
    if (!cities.contains(startCity) || !cities.contains(endCity)) {
        qDebug() << "Start or end city not found in the graph.";
        return {}; // 返回空路径
    }

    std::map<QString, double> distances; // 存储最短距离
    std::map<QString, QString> predecessors; // 存储前驱城市
    QSet<QString> visited; // 存储已访问城市
    using Pair = std::pair<double, QString>;
    auto cmp = [](Pair left, Pair right) { return left.first > right.first; };
    std::priority_queue<Pair, std::vector<Pair>, decltype(cmp)> queue(cmp); // 优先队列

    // 初始化
    for (const auto& city : cities) {
        distances[city] = std::numeric_limits<double>::infinity(); // 设置为无穷大
    }
    distances[startCity] = 0; // 起始城市距离为0
    queue.push({0, startCity});

    while (!queue.empty()) {
        auto [currentDistance, currentCity] = queue.top();
        queue.pop();

        if (visited.contains(currentCity)) continue; // 如果已访问，则跳过
        visited.insert(currentCity);

        for (const auto& flight : flights[currentCity]) {
            double newDistance = currentDistance + flight.distanceKm; // 计算新距离
            if (newDistance < distances[flight.arrivalCity]) {
                distances[flight.arrivalCity] = newDistance; // 更新最短距离
                predecessors[flight.arrivalCity] = currentCity; // 更新前驱城市
                queue.push({newDistance, flight.arrivalCity});
            }
        }
    }

    // 回溯路径
    std::vector<QString> path;
    for (QString city = endCity; !city.isEmpty(); city = predecessors[city]) {
        path.push_back(city);
    }
    std::reverse(path.begin(), path.end()); // 反转路径

    if (path.empty() || path.front() != startCity) {
        qDebug() << "No path found from" << startCity << "to" << endCity;
        return {}; // 返回空路径
    }

    return path; // 返回路径
}


