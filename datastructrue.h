#ifndef DATASTRUCTRUE_H
#define DATASTRUCTRUE_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <utility>

using namespace std;

class Datastructrue
{
public:
    Datastructrue();
};

//航班类
class Flight {
public:
    std::string airline;
    std::string flightNumber;
    std::string departureTime;
    std::string arrivalTime;
    double ticketPrice;
    double discount;
    bool isFullyBooked;

    Flight() : airline(""), flightNumber(""), departureTime(""), arrivalTime(""),
        ticketPrice(0.0), discount(0.0), isFullyBooked(false) {}

    Flight(std::string a, std::string f, std::string dT, std::string aT, double price, double disc, bool booked)
        : airline(a), flightNumber(f), departureTime(dT), arrivalTime(aT),
        ticketPrice(price), discount(disc), isFullyBooked(booked) {}
};



// 优先队列类
template<typename T>
class PriorityQueue {
private:
    std::vector<std::pair<double, T>> heap; // 存储优先级和对应的值
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void push(double priority, T value);
    T pop();
    bool isEmpty() const { return heap.empty(); }
};

template<typename T>
void PriorityQueue<T>::push(double priority, T value) {
    heap.emplace_back(priority, value);
    heapifyUp(heap.size() - 1);
}

template<typename T>
T PriorityQueue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Priority Queue is empty");
    }
    T topValue = heap.front().second;
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return topValue;

}

template<typename T>
void PriorityQueue<T>::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index].first >= heap[parent].first) break;
        swap(heap[index], heap[parent]);
        index = parent;
    }
}

template<typename T>
void PriorityQueue<T>::heapifyDown(int index) {
    int size = heap.size();
    while (index < size) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size && heap[left].first < heap[smallest].first) {
            smallest = left;
        }
        if (right < size && heap[right].first < heap[smallest].first) {
            smallest = right;
        }
        if (smallest == index) break;
        swap(heap[index], heap[smallest]);
        index = smallest;
    }
}


// 邻接表节点
class AdjListNode {
public:
    std::string cityName;
    Flight flight;

    AdjListNode() : cityName(""), flight() {}

    AdjListNode(std::string name, Flight f) : cityName(name), flight(f) {}
};

// 图结构类
class Graph {
public:
    vector<std::string> cities; // 存储城市名称
    vector<std::vector<AdjListNode>> adjList; // 存储航班信息

    void addCity(const std::string& cityName) {
        cities.push_back(cityName);
        adjList.resize(cities.size());
    }

    void addEdge(const std::string& departureCity, const std::string& destinationCity, const Flight& flight) {
        int departureIndex = findCityIndex(departureCity);
        int destinationIndex = findCityIndex(destinationCity);
        if (departureIndex != -1 && destinationIndex != -1) {
            adjList[departureIndex].emplace_back(destinationCity, flight);
        }
    }

    int findCityIndex(const std::string& city) const {
        for (size_t i = 0; i < cities.size(); ++i) {
            if (cities[i] == city) return i;
        }
        return -1; // 未找到城市
    }

    const std::vector<AdjListNode>& getNeighbors(const std::string& city) const {
        int index = findCityIndex(city);
        if (index != -1) return adjList[index];
        throw std::runtime_error("City not found");
    }

    bool hasCity(const std::string& city) const {
        return findCityIndex(city) != -1;
    }
};

// 航线网络类
class FlightNetwork {
public:
    Graph graph;

    FlightNetwork() {}

    void addCity(const std::string& cityName) {
        graph.addCity(cityName);
    }

    void addFlight(const std::string& departureCity, const std::string& destinationCity, const Flight& flight) {
        graph.addEdge(departureCity, destinationCity, flight);
    }

    void queryFlights(const std::string& departureCity, const std::string& arrivalCity, const std::string& condition, std::vector<Flight>& results) {
        PriorityQueue<Flight> pq;

        if (graph.hasCity(departureCity)) {
            const auto& neighbors = graph.getNeighbors(departureCity);
            for (const auto& entry : neighbors) {
                if (entry.cityName == arrivalCity) {
                    pq.push(entry.flight.ticketPrice, entry.flight);
                }
            }
        }

        while (!pq.isEmpty()) {
            results.push_back(pq.pop());
        }

        if (condition == "费用最少") {
            sort(results.begin(), results.end(), [](const Flight& a, const Flight& b) {
                return a.ticketPrice < b.ticketPrice;
            });
        }
        else if (condition == "时间最短") {
            sort(results.begin(), results.end(), [](const Flight& a, const Flight& b) {
                return a.departureTime < b.departureTime;
            });
        }
    }

    void displayAllFlights() {
        cout << "所有航班信息:\n";
        for (size_t i = 0; i < graph.cities.size(); ++i) {
            const auto& city = graph.cities[i];
            for (const auto& adj : graph.adjList[i]) {
                cout << "起点城市: " << city
                     << ", 航班号: " << adj.flight.flightNumber
                     << ", 目的城市: " << adj.cityName
                     << ", 航空公司: " << adj.flight.airline
                     << ", 起飞时间: " << adj.flight.departureTime
                     << ", 到达时间: " << adj.flight.arrivalTime
                     << ", 票价: " << adj.flight.ticketPrice
                     << ", 票价折扣: " << adj.flight.discount
                     << ", 是否满仓: " << (adj.flight.isFullyBooked ? "是" : "否") << endl;
            }
        }
    }
};

// 订单类
class Order {
public:
    string orderID;
    string passengerName;
    Flight flight;
    int ticketCount;
    double totalPrice;

    Order() : orderID(""), passengerName(""), flight(), ticketCount(0), totalPrice(0.0) {}

    Order(string id, string name, Flight f, int count)
        : orderID(id), passengerName(name), flight(f), ticketCount(count) {
        totalPrice = (f.ticketPrice - f.ticketPrice * f.discount) * count;
    }

    void displayOrder() {
        cout << "订单编号: " << orderID << endl;
        cout << "乘机人: " << passengerName << endl;
        cout << "航班信息: " << flight.flightNumber << ", 航空公司: " << flight.airline
             << ", 票价: " << flight.ticketPrice << ", 折扣: " << flight.discount
             << ", 机票数量: " << ticketCount << ", 总价格: " << totalPrice << endl;
    }
};

// 退改票管理类
class TicketManagement {
public:
    vector<Order> orders;

    TicketManagement() {}

    void addOrder(const Order& order) {
        orders.push_back(order);
    }

    void refundTicket(const string& orderID) {
        auto it = find_if(orders.begin(), orders.end(), [&orderID](const Order& order) {
            return order.orderID == orderID;
        });
        if (it != orders.end()) {
            orders.erase(it);
            cout << "成功退票，订单编号: " << orderID << endl;
        }
        else {
            cout << "未找到订单编号: " << orderID << endl;
        }
    }

    void changeFlight(const string& orderID, Flight newFlight, int newTicketCount) {
        auto it = find_if(orders.begin(), orders.end(), [&orderID](const Order& order) {
            return order.orderID == orderID;
        });
        if (it != orders.end()) {
            Order& order = *it;
            order.flight = newFlight;
            order.ticketCount = newTicketCount;
            order.totalPrice = (newFlight.ticketPrice - newFlight.ticketPrice * newFlight.discount) * newTicketCount;
            cout << "成功改签，新的航班信息:\n";
            order.displayOrder();
        }
        else {
            cout << "未找到订单编号: " << orderID << endl;
        }
    }
};


#endif // DATASTRUCTRUE_H
