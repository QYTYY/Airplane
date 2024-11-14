#ifndef BOOKTICKET_H
#define BOOKTICKET_H

#include <QMainWindow>
#include <flight.h>
#include <flightsearch.h>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <user.h>
namespace Ui {
class BookTicket;
}

class BookTicket : public QMainWindow
{
    Q_OBJECT

public:
    explicit BookTicket(QWidget *parent = nullptr);
    ~BookTicket();
    FlightSchedule FS;
    Graph G;
    UserManager UM;
    QVector<FlightTicket> sche ;

private slots:
    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_pushButton_3_released();

private:
    Ui::BookTicket *ui;
};

#endif // BOOKTICKET_H
