#ifndef FLIGHT_H
#define FLIGHT_H
#include <QCoreApplication>
#include <QString>
#include <QVector>
#include <QDebug>
#include <iostream>
// QXlsx
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

#include <QString>
#include <QTime>
#include <QDateTime>
#include <QMap>
#include <QList>
#include <queue>
class Flight
{
public:
    QString departureCity; // 出发城市
    double departureLat;   // 出发城市纬度
    double departureLon;   // 出发城市经度
    QString arrivalCity;   // 到达城市
    double arrivalLat;     // 到达城市纬度
    double arrivalLon;     // 到达城市经度
    int distanceKm;        // 距离 (公里)
    QString flightNumber;  // 航班号
    QString airline;       // 航空公司
    QString aircraftModel; // 飞机型号
    QString avgDelay;      // 平均误点率
    QString delayTime;     // 误点时间
    bool schedule[7];      // 每周班期（周一到周日）
    QString validFrom;     // 有效起始日期
    QString validTo;       // 有效结束日期
    QString departureAirport; // 出发机场
    QString arrivalAirport;   // 到达机场
    QString departureTime;    // 出发时间
    QString arrivalTime;      // 到达时间
    QString flightDuration;   // 飞行时长

    Flight(
        const QString& depCity, double depLat, double depLon,
        const QString& arrCity, double arrLat, double arrLon,
        int distKm, const QString& flightNum, const QString& airln,
        const QString& model, const QString& delay, const QString& dt,
        bool weekSchedule[7], const QString& start, const QString& end,
        const QString& depAirport, const QString& arrAirport,
        const QString& depTime, const QString& arrTime
        ) : departureCity(depCity), departureLat(depLat), departureLon(depLon),
        arrivalCity(arrCity), arrivalLat(arrLat), arrivalLon(arrLon),
        distanceKm(distKm), flightNumber(flightNum), airline(airln),
        aircraftModel(model), avgDelay(delay), delayTime(dt), validFrom(start),
        validTo(end), departureAirport(depAirport), arrivalAirport(arrAirport),
        departureTime(depTime), arrivalTime(arrTime)
    {
        std::copy(weekSchedule, weekSchedule + 7, schedule);
        flightDuration = calculateFlightDuration(); // 计算飞行时间
    }


    // 计算飞行时长
    QString calculateFlightDuration();

    // 返回飞行时长的毫秒数
    int getFlightDurationInMsecs() const;

    // 返回航班的准点率
    double getOnTimeRate() const;

    // 返回航班信息
    QString getInfo() const;
    //返回到txt
    QString getInfoTxt() const;

    // 返回出发时间
    QString getDepartureTime() const;
};





class FlightSchedule {
public:
    void addFlight(const Flight& flight) {
        flights.append(flight);
    }

    QVector<Flight> findFlightsByCity(const QString& city1,const QString& city2) const {
        QVector<Flight> matchingFlights;
        for (const auto& flight : flights) {
            if (flight.departureCity == city1 && flight.arrivalCity == city2) {
                matchingFlights.append(flight);
            }
        }
        return matchingFlights;

    }
    QVector<Flight> getFlights() const { // 返回所有航班的函数
        return flights; // 直接返回 QVector<Flight>
    }
private:
    QVector<Flight> flights;
};

//读excel
bool readExcelFile(const QString& filePath, FlightSchedule& schedule);


class City {
public:
    QString name; // 城市名称
    double latitude; // 纬度
    double longitude; // 经度

    City(QString name, double lat, double lon)
        : name(name), latitude(lat), longitude(lon) {}
};
class Graph {
public:
    // 添加航班
    void addFlight(const Flight& flight);

    // 根据出发城市查找航班
    QList<Flight> findFlightsFromCity(const QString& city) const;

    // 打印所有航班信息
    void printAllFlights() const;

    // 打印所有城市
    void printAllCities() const;
    //距离最短；
    std::vector<QString> dijkstra(const QString& startCity, const QString& endCity) const;


private:
    QMap<QString, QList<Flight>> flights; // 存储以出发城市为键的航班列表
    QSet<QString> cities;                 // 存储城市集合，避免重复
};
#endif // FLIGHT_H

