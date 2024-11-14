#ifndef VOYA_H
#define VOYA_H

#include <QWidget>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFileSystemWatcher>
#include <QVector>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGraphicsPixmapItem>
#include <QWheelEvent>
#include <flight.h>
#include <user.h>
#include <QFileSystemWatcher>
namespace Ui {
class voya;
}

class voya : public QWidget
{
    Q_OBJECT

public:
    explicit voya(QWidget *parent = nullptr);
    ~voya();
    void initializeMap();
    QPointF convertLatLonToSceneCoordinates(double lat, double lon);  // 经纬度转为场景坐标
    // 添加飞行路径的函数声明
    void addFlightPath(const QPointF& from, const QPointF& to);
    void wheelEvent(QWheelEvent* event);
    QPair<QPointF, QPointF> convertFlightCoordinatesToScene(const Flight& flight);
    void drawArrow(const QPointF& from, const QPointF& to);
    void onUsersFileChanged();
    void updateFlightPaths();
    void loadUsers();

private:
    Ui::voya *ui;
    QGraphicsView* mapView;
    QGraphicsScene* mapScene;
    QGraphicsPixmapItem* mapItem;
    UserManager UM;
};

#endif // VOYA_H
