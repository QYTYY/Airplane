#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <flightsearch.h>
#include <bookticket.h>
#include <refund.h>
#include <flight.h>
#include <flightsearch.h>
#include <user.h>
#include <QFileSystemWatcher>
#include <QTextStream>
#include <voya.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FlightSearch* f;
    BookTicket* b;
    refund* r;
    voya* v;
    UserManager UM;
   QFileSystemWatcher *fileWatcher;  // 文件监控
    bool isFileChanged;


private slots:
    void connectflightsearch();

private slots:
    void connectbookticket();

private slots:
    void connectrefund();
private slots:
    void connectmyTicket();
private slots:
    void onFileChanged();
    void connectmyvoya();

};
#endif //MAINWINDOW_H
