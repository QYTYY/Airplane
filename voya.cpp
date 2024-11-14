#include "voya.h"
#include "ui_voya.h"

voya::voya(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::voya)
{
    ui->setupUi(this);
    loadUsers();
    // 监控 users.txt 文件
    QFileSystemWatcher *fileWatcher = new QFileSystemWatcher(this);
    fileWatcher->addPath("C:\\Users\\24085\\OneDrive\\Desktop\\plane\\untitled\\users.txt");

    // 连接文件更改信号和槽，以便重新加载用户数据
    connect(fileWatcher, &QFileSystemWatcher::fileChanged, this, &voya::onUsersFileChanged);
    qDebug()<<"画画的用户："<<UM.getAllUsers().size();
    initializeMap();
    updateFlightPaths();
}

voya::~voya()
{
    delete ui;
}
void voya::initializeMap() {
    // 创建一个QGraphicsView和QGraphicsScene来显示地图
    mapScene = new QGraphicsScene(this);
    mapView = new QGraphicsView(mapScene, this);

    mapView->setGeometry(0, 20, 1510, 1250); // 设置地图视图的位置和大小
    mapView->setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿

    // 加载地图图像
    mapItem = new QGraphicsPixmapItem(QPixmap("C:\\Users\\24085\\OneDrive\\Desktop\\plane\\untitled\\map.jpg"));
    mapScene->addItem(mapItem);
    mapScene->setSceneRect(mapItem->boundingRect());  // 设置场景的边界

    // 启用缩放功能
    mapView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mapView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mapView->setRenderHint(QPainter::Antialiasing);

    // 可缩放功能
    mapView->setDragMode(QGraphicsView::ScrollHandDrag);  // 可以拖动地图
    mapView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);  // 缩放中心为鼠标位置
}
QPointF voya::convertLatLonToSceneCoordinates(double lat, double lon) {
    // 定义地图左上角和右下角的经纬度
    double latTop = 53.55;
    double lonLeft = 73.4;
    double latBottom = 18.0;
    double lonRight = 135.0;

    // 场景的宽度和高度
    double sceneWidth = mapItem->pixmap().width();
    double sceneHeight = mapItem->pixmap().height();

    // 计算x和y坐标
    double x = (lon - lonLeft) / (lonRight - lonLeft) * sceneWidth+40;
    double y = (latTop - lat) / (latTop - latBottom) * sceneHeight;

    return QPointF(x, y);
}

// 添加飞行记录到地图上
void voya::addFlightPath(const QPointF& from, const QPointF& to) {
    // 创建一条从 'from' 到 'to' 的线
    QGraphicsLineItem* line = new QGraphicsLineItem(QLineF(from, to));

    // 设置线的颜色和宽度
    QPen pen(Qt::blue, 2);
    line->setPen(pen);

    // 将线条添加到地图场景
    this->mapScene->addItem(line);
    // 绘制箭头
    drawArrow(from, to);
}
void voya::wheelEvent(QWheelEvent* event) {
    // 设置缩放因子
    qreal scaleFactor = 1.1;

    // 判断滚轮的方向，向上滚动放大，向下滚动缩小
    if (event->angleDelta().y() > 0) {
        // 放大
        mapView->scale(scaleFactor, scaleFactor);
    } else {
        // 缩小
        mapView->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    // 防止滚动事件传递到其他组件，造成其他控件的滚动
    event->accept();
}
QPair<QPointF, QPointF> voya::convertFlightCoordinatesToScene(const Flight& flight) {
    // 转换出发地坐标
    QPointF departurePoint = convertLatLonToSceneCoordinates(flight.departureLat, flight.departureLon);

    // 转换到达地坐标
    QPointF arrivalPoint = convertLatLonToSceneCoordinates(flight.arrivalLat, flight.arrivalLon);

    // 返回出发地和到达地坐标的QPointF对
    return QPair<QPointF, QPointF>(departurePoint, arrivalPoint);
}

// 绘制箭头
void voya::drawArrow(const QPointF& from, const QPointF& to) {

    // Create the main line for the arrow
    QLineF line(from, to);

    // Define the arrowhead size and calculate the angle of the line
    double arrowSize = 10;
    double angle = std::atan2(-line.dy(), line.dx()); // Correct angle for line orientation

    // Calculate the points for the arrowhead
    QPointF arrowP1 = line.p2() - QPointF(std::cos(angle + M_PI / 6) * arrowSize,
                                          std::sin(angle + M_PI / 6) * arrowSize);
    QPointF arrowP2 = line.p2() - QPointF(std::cos(angle - M_PI / 6) * arrowSize,
                                          std::sin(angle - M_PI / 6) * arrowSize);

    // Draw the line and the arrowhead
    QGraphicsLineItem* lineItem = new QGraphicsLineItem(line);
    QPen pen(Qt::blue, 2);
    lineItem->setPen(pen);
    mapScene->addItem(lineItem);

    // Create the arrowhead as a polygon and set its color
    QPolygonF arrowHead;
    arrowHead << line.p2() << arrowP1 << arrowP2;
    QGraphicsPolygonItem* arrow = new QGraphicsPolygonItem(arrowHead);
    arrow->setBrush(Qt::blue);

    // Add the arrowhead to the scene
    mapScene->addItem(arrow);
}
// 从文件加载用户数据并更新用户管理器 UM
void voya::loadUsers()
{
    UM.clearUsers(); // 清除现有用户数据（如果需要）
    QVector<User> u = loadUsersFromFile("C:\\Users\\24085\\OneDrive\\Desktop\\plane\\untitled\\users.txt");
    for (auto &us : u) {
        UM.addUser(us);
    }
    qDebug() << "画画的用户：" << UM.getAllUsers().size();
}
// 槽函数：当 users.txt 文件更改时触发
void voya::onUsersFileChanged()
{
    qDebug() << "users.txt 文件已修改，重新加载用户数据...";
    loadUsers();
    updateFlightPaths();
}
// 更新所有用户的航线
void voya::updateFlightPaths()
{
    for (auto u : UM.getAllUsers()) {
        QPair<QPointF, QPointF> pair;
        pair = convertFlightCoordinatesToScene(u.getFlightTicket().getFlight());
        qDebug() << pair;
        addFlightPath(pair.first, pair.second);
    }
}
