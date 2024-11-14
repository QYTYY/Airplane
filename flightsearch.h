#ifndef FLIGHTSEARCH_H
#define FLIGHTSEARCH_H

#include <QMainWindow>
#include <flight.h>
namespace Ui {
class FlightSearch;
}

class FlightSearch : public QMainWindow
{
    Q_OBJECT

public:
    explicit FlightSearch(QWidget *parent = nullptr);
    ~FlightSearch();
    FlightSchedule FS;
    Graph G;

private slots:
    void on_pushButton_released();


    void on_pushButton_2_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_zhuanji_duratime_released();

    void on_zhuanji_rate_released();

private:
    Ui::FlightSearch *ui;
};

#endif // FLIGHTSEARCH_H
