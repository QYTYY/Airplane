#include "mainwindow.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    f = new FlightSearch;
    b = new BookTicket;
    r = new refund;

    // 初始化文件监控
    fileWatcher = new QFileSystemWatcher(this);
    QString filePath = "D:\\数据结构课设\\plane\\untitled\\users.txt";
    fileWatcher->addPath(filePath);
    isFileChanged = false;

    // 连接文件监控的信号到槽函数
    connect(fileWatcher, &QFileSystemWatcher::fileChanged, this, &MainWindow::onFileChanged);

    // 定义 fileWatcher
    QVector<User> u = loadUsersFromFile(filePath);
    for (auto us : u) {
        UM.addUser(us);
    }

    // 菜单切换链接
    connect(ui->actionFlight_enquiry, SIGNAL(triggered()), this, SLOT(connectflightsearch()));
    connect(ui->action, SIGNAL(triggered()), this, SLOT(connectbookticket()));
    connect(ui->actionMy_ticket, SIGNAL(triggered()), this, SLOT(connectmyTicket()));

    // 创建一个新的 QWidget 作为 scrollArea 的内容部件
    QWidget* shuchuWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(shuchuWidget);
    shuchuWidget->setLayout(layout); // 设置布局到 shuchuWidget 上

    // 将 shuchuWidget 设置为 scrollArea 的内容部件
    ui->scrollArea->setWidget(shuchuWidget);
    ui->scrollArea->setWidgetResizable(true); // 设置为可调整大小
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectflightsearch()
{
    f->show();
}

void MainWindow::connectbookticket()
{
    b->show();
}

void MainWindow::connectrefund()
{
    r->show();
}

void MainWindow::onFileChanged()
{
    QString filePath = "D:\\数据结构课设\\plane\\untitled\\users.txt";

    // 检查文件是否还在监控路径下（有些系统可能在文件内容更改时临时删除文件）
    if (!fileWatcher->files().contains(filePath)) {
        fileWatcher->addPath(filePath);
    }

    // 重新加载用户数据
    QVector<User> updatedUsers = loadUsersFromFile(filePath);
    UM.clearUsers();  // 清空当前用户列表
    for (const auto& user : updatedUsers) {
        UM.addUser(user);
    }

    // 设置标志位，表示文件已更改
    isFileChanged = true;
}

void MainWindow::connectmyTicket() {
    // 如果文件已经更改，则刷新界面

        qDebug() << "File has been updated, refreshing user list.";

        qDebug() << "Number of users in UserManager:" << UM.getAllUsers().size();

        QWidget* shuchuWidget = ui->scrollArea->widget();
        QVBoxLayout* mainLayout = qobject_cast<QVBoxLayout*>(shuchuWidget->layout());

        if (mainLayout == nullptr) {
            qDebug() << "Error: Layout not found!";
            return;
        }

        // 清除当前显示的内容
        QLayoutItem* item;
        while ((item = mainLayout->takeAt(0)) != nullptr) {
            if (item->widget()) {
                item->widget()->deleteLater();
            }
            delete item;
        }

        // 添加新的用户信息到界面
        for (const auto& user : UM.getAllUsers()) {
            qDebug() << "Adding user info:" << user.getUserInfo();

            QWidget* userWidget = new QWidget(this);
            QHBoxLayout* userLayout = new QHBoxLayout(userWidget);

            QLabel* userInfoLabel = new QLabel(user.getUserInfo(), userWidget);
            userLayout->addWidget(userInfoLabel);
            userInfoLabel->setWordWrap(true);
            userInfoLabel->setMaximumWidth(500);

            QPushButton* cancelButton = new QPushButton("退票", userWidget);
            userLayout->addWidget(cancelButton);

            connect(cancelButton, &QPushButton::clicked, [this, user, userWidget, mainLayout]() {
                UM.removeUser(user.getIdCard());
                qDebug() << "User removed:" << user.getIdCard();

                // 删除用户信息界面元素
                userWidget->deleteLater();
                mainLayout->removeWidget(userWidget);  // 从布局中移除

                UM.saveUsersToFileWri("D:\\数据结构课设\\plane\\untitled\\users.txt");

                // 更新布局和界面
                mainLayout->update();
                ui->scrollArea->widget()->adjustSize();
                ui->scrollArea->update();
            });

            userWidget->setLayout(userLayout);
            mainLayout->addWidget(userWidget);
        }

        mainLayout->update();
        shuchuWidget->adjustSize();
        ui->scrollArea->widget()->adjustSize();
        ui->scrollArea->update();

        // 重置标志位
        isFileChanged = false;

}
