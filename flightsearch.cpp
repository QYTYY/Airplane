#include "flightsearch.h"
#include "ui_flightsearch.h"
#include <flight.h>
FlightSearch::FlightSearch(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FlightSearch)
{
    ui->setupUi(this);
   //读 excel表格
   /* if (readExcelFile("C:\\Users\\24085\\OneDrive\\Desktop\\plane\\untitled\\flight.xlsx", FS)) {
        FS.displayFlights();
    } else {
        qWarning() << "Error reading the Excel file.";
    }*/
    readExcelFile("C:\\Users\\24085\\OneDrive\\Desktop\\plane\\untitled\\flight.xlsx", FS);

      auto F = FS.getFlights();
    for(const auto& flight : F){
        G.addFlight(flight);
    }
}

FlightSearch::~FlightSearch()
{
    delete ui;
}

void FlightSearch::on_pushButton_released()
{    //清空
     ui->shuchu->clear();

    auto decity = ui->departure->toPlainText();
    auto arcity = ui->arrive->toPlainText();

    QVector<Flight> flightsToCity = FS.findFlightsByCity(decity,arcity);

    //判断是否为空
    if(flightsToCity.isEmpty()){
        ui->shuchu->append("抱歉，目前没有航班可以直达，请您选择转机试试");
    }else{
    for (const auto& flight : flightsToCity) {
        qDebug() << "Found flight:" << flight.flightNumber;
        auto info = flight.getInfo();

        ui->shuchu->append(info);
    }
    }

}



void FlightSearch::on_pushButton_2_released()
{
    ui->shuchu->clear();

    auto decity = ui->departure->toPlainText();
    auto arcity = ui->arrive->toPlainText();

    QVector<Flight> flightsToCity = FS.findFlightsByCity(decity,arcity);
    //判断是否为空
    if(flightsToCity.isEmpty()){
        ui->shuchu->append("抱歉，目前没有航班可以直达，请您选择转机试试");
    }else{
    //按飞行时间排序
    std::sort(flightsToCity.begin(), flightsToCity.end(), [](const Flight& a, const Flight& b) {
        return a.getFlightDurationInMsecs() < b.getFlightDurationInMsecs();
    });

    for (const auto& flight : flightsToCity) {
        qDebug() << "Found flight:" << flight.flightNumber;
        auto info = flight.getInfo();

        ui->shuchu->append(info);
    }
    }
}





void FlightSearch::on_pushButton_3_released()
{
    ui->shuchu->clear();

    auto decity = ui->departure->toPlainText();
    auto arcity = ui->arrive->toPlainText();

    QVector<Flight> flightsToCity = FS.findFlightsByCity(decity,arcity);
    //判断是否为空
    if(flightsToCity.isEmpty()){
        ui->shuchu->append("抱歉，目前没有航班可以直达，请您选择转机试试");
    }else{
    //按准点率排序
    std::sort(flightsToCity.begin(), flightsToCity.end(), [](const Flight& a, const Flight& b) {
        return a.getOnTimeRate() > b.getOnTimeRate();
    });

    for (const auto& flight : flightsToCity) {
        qDebug() << "Found flight:" << flight.flightNumber;
        auto info = flight.getInfo();


        ui->shuchu->append(info);
    }
    }
}

//dijisitela
void FlightSearch::on_pushButton_4_released()
{
    //清空
    ui->shuchu->clear();

    auto decity = ui->departure->toPlainText();
    auto arcity = ui->arrive->toPlainText();

    std::vector<QString> path = G.dijkstra(decity, arcity);
    for (const auto& city : path) {
        ui->shuchu->append(city);
    }
     for (size_t i = 0; i < path.size() - 1; i++) {
        QString qs = path[i]+ "->" +path[i+1];
        ui->shuchu->append(qs);
         decity = path[i];
         arcity = path[i+1];
        QVector<Flight> flightsToCity = FS.findFlightsByCity(decity,arcity);

         for (const auto& flight : flightsToCity) {
             qDebug() << "Found flight:" << flight.flightNumber;
             auto info = flight.getInfo();


             ui->shuchu->append(info);
         }
     }
 }




 void FlightSearch::on_zhuanji_duratime_released()
    {
        //清空
        ui->shuchu->clear();

        auto decity = ui->departure->toPlainText();
        auto arcity = ui->arrive->toPlainText();

        std::vector<QString> path = G.dijkstra(decity, arcity);
        for (const auto& city : path) {
            ui->shuchu->append(city);
        }
        for (size_t i = 0; i < path.size() - 1; i++) {
            QString qs = path[i]+ "->" +path[i+1];
            ui->shuchu->append(qs);
            decity = path[i];
            arcity = path[i+1];
            QVector<Flight> flightsToCity = FS.findFlightsByCity(decity,arcity);
           //按飞行时间排序
            std::sort(flightsToCity.begin(), flightsToCity.end(), [](const Flight& a, const Flight& b) {
                return a.getFlightDurationInMsecs() < b.getFlightDurationInMsecs();
            });

            for (const auto& flight : flightsToCity) {
                qDebug() << "Found flight:" << flight.flightNumber;
                auto info = flight.getInfo();


                ui->shuchu->append(info);
            }
        }
    }


    void FlightSearch::on_zhuanji_rate_released()
    {
        //清空
        ui->shuchu->clear();

        auto decity = ui->departure->toPlainText();
        auto arcity = ui->arrive->toPlainText();

        std::vector<QString> path = G.dijkstra(decity, arcity);
        for (const auto& city : path) {
            ui->shuchu->append(city);
        }
        for (size_t i = 0; i < path.size() - 1; i++) {
            QString qs = path[i]+ "->" +path[i+1];
            ui->shuchu->append(qs);
            decity = path[i];
            arcity = path[i+1];
            QVector<Flight> flightsToCity = FS.findFlightsByCity(decity,arcity);
            //按准点率排序
            std::sort(flightsToCity.begin(), flightsToCity.end(), [](const Flight& a, const Flight& b) {
                return a.getOnTimeRate() > b.getOnTimeRate();
            });
            for (const auto& flight : flightsToCity) {
                qDebug() << "Found flight:" << flight.flightNumber;
                auto info = flight.getInfo();


                ui->shuchu->append(info);
            }
        }
    }

