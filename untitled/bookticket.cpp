#include "bookticket.h"
#include "ui_bookticket.h"

BookTicket::BookTicket(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BookTicket)
{
    ui->setupUi(this);
    readExcelFile("D:\\数据结构课设\\plane\\untitled\\flight.xlsx", FS);

    auto F = FS.getFlights();
    for(const auto& flight : F){
        G.addFlight(flight);
    }
    // 创建一个新的 QWidget 作为 scrollArea 的内容部件
    QWidget* shuchuWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(shuchuWidget);

    // 将 shuchuWidget 设置为 scrollArea 的内容部件
    ui->scrollArea->setWidget(shuchuWidget);
    ui->scrollArea->setWidgetResizable(true); // 设置为可调整大小

}

BookTicket::~BookTicket()
{
    delete ui;
}

void BookTicket::on_pushButton_released()
{
    // 获取 shuchuWidget 的布局
    QVBoxLayout* layout = static_cast<QVBoxLayout*>(ui->scrollArea->widget()->layout());

    // 清空现有的所有子控件
    while (QLayoutItem* item = layout->takeAt(0)) {
        delete item->widget(); // 删除现有的子控件
        delete item; // 删除布局项
    }

    //读数据
    auto decity = ui->departure->toPlainText();
    auto arcity = ui->arrive->toPlainText();
    auto num = ui->plane_num->toPlainText();
    //查直飞
    QVector<Flight> flightsToCity = FS.findFlightsByCity(decity,arcity);
    if(flightsToCity.isEmpty()){
        QMessageBox::warning(this, "抱歉","没有直飞航班，下面是转机航线");
    }
    if(num.isEmpty()){


        //展示直飞航班
        if(!flightsToCity.empty()){
            QLabel* cityLabel = new QLabel("下面是直飞航班");
            layout->addWidget(cityLabel); // 使用 layout 添加标签
            for (const auto& flight : flightsToCity) {
                // 创建一个新的QWidget来显示航班信息和按钮
                QWidget* flightWidget = new QWidget(this);
                QHBoxLayout* flightLayout = new QHBoxLayout(flightWidget);

                qDebug() << "Found flight:" << flight.flightNumber;
                auto info = flight.getInfo();
                // 添加航班信息
                QLabel* infoLabel = new QLabel(info, this);
                infoLabel->setWordWrap(true);
                infoLabel->setMaximumWidth(500);
                flightLayout->addWidget(infoLabel);

                // 创建订票按钮
                QPushButton* bookButton = new QPushButton("订票", this);
                connect(bookButton, &QPushButton::clicked, this, [this, flight]() {
                    // 处理订票逻辑
                    qDebug() << "Booking flight:" << flight.flightNumber;
                    bool ok;
                    QString name = QInputDialog::getText(this, "输入姓名", "姓名:", QLineEdit::Normal, "", &ok);
                    if (ok && !name.isEmpty()) {
                        // 弹出输入对话框，要求用户输入身份证号
                        QString idCard = QInputDialog::getText(this, "输入身份证号", "身份证号:", QLineEdit::Normal, "", &ok);
                        if (ok && !idCard.isEmpty()) {
                            // 弹出输入对话框，要求用户输入星期几
                            QString dayInput = QInputDialog::getText(this, "输入星期几", "请输入星期几 (1-7，1为星期一，7为星期日):", QLineEdit::Normal, "", &ok);
                            if (ok && !dayInput.isEmpty()) {
                                int day = dayInput.toInt();
                                if (day < 1 || day > 7) {
                                    QMessageBox::warning(this, "输入错误", "请输入有效的星期几 (1-7)！");
                                    return;
                                }

                                // 检查航班是否在该天有
                                if (!flight.schedule[day - 1]) { // day - 1 因为数组从0开始
                                    QString availableDays;
                                    for (int i = 0; i < 7; ++i) {
                                        if (flight.schedule[i]) {
                                            availableDays += QString::number(i + 1) + " "; // i + 1 转换为星期几
                                        }
                                    }
                                    QMessageBox::warning(this, "无航班", "该航班在今天没有航班，"
                                                                         "可用的航班在星期: " + availableDays.trimmed());
                                    return; // 提前返回
                                }

                                // 设置日期
                                int number = dayInput.toInt();
                                FlightTicket* FT = new FlightTicket(flight,number) ;// 修改航班的日期

                                // 创建用户对象
                                User user(name, idCard, *FT);

                                // 显示订票成功的消息
                                QMessageBox::information(this, "订票成功", "航班 " + flight.flightNumber + " 已成功预订！");

                                // 保存 user 对象，或进行后续处理
                                UM.addUser(user);
                            }
                        }
                    }
                    UM.printAllUsers();
                    UM.saveUsersToFileApp("D:\\数据结构课设\\plane\\untitled\\users.txt");

                });

                // 将按钮添加到布局中
                flightLayout->addWidget(bookButton);

                // 设置 flightWidget 的布局
                flightWidget->setLayout(flightLayout);

                // 将 flightWidget 添加到主布局中
                layout->addWidget(flightWidget);
            }

        }
        //展示转机航班


        std::vector<QString> path = G.dijkstra(decity, arcity);
        if (path.empty()) {
            qDebug() << "No path found between" << decity << "and" << arcity;
            return; // 提前返回
        }else{

            // 添加城市标签
            for (const auto& city : path) {
                QLabel* cityLabel = new QLabel(city, this);
                layout->addWidget(cityLabel); // 使用 layout 添加标签
            }

            // 添加路径信息和航班信息
            for (size_t i = 0; i < path.size() - 1; i++) {
                QString qs = path[i] + "->" + path[i + 1];
                QLabel* pathLabel = new QLabel(qs, this);
                layout->addWidget(pathLabel); // 添加路径信息标签

                decity = path[i];
                arcity = path[i + 1];
                QVector<Flight> flightsToCity = FS.findFlightsByCity(decity, arcity);



                // 为每个航班添加信息和按钮
                for (const auto& flight : flightsToCity) {
                    qDebug() << "Found flight:" << flight.flightNumber;
                    auto info = flight.getInfo();

                    // 创建一个新的QWidget来显示航班信息和按钮
                    QWidget* flightWidget = new QWidget(this);
                    QHBoxLayout* flightLayout = new QHBoxLayout(flightWidget);

                    // 添加航班信息
                    QLabel* infoLabel = new QLabel(info, this);
                    infoLabel->setWordWrap(true);
                    infoLabel->setMaximumWidth(500);
                    flightLayout->addWidget(infoLabel);

                    // 创建订票按钮
                    QPushButton* bookButton = new QPushButton("订票", this);
                    connect(bookButton, &QPushButton::clicked, this, [this,flight]() {
                        qDebug() << "Booking flight:" << flight.flightNumber;

                        // 弹出输入对话框，要求用户输入姓名
                        bool ok;
                        QString name = QInputDialog::getText(this, "输入姓名", "姓名:", QLineEdit::Normal, "", &ok);
                        if (ok && !name.isEmpty()) {
                            // 弹出输入对话框，要求用户输入身份证号
                            QString idCard = QInputDialog::getText(this, "输入身份证号", "身份证号:", QLineEdit::Normal, "", &ok);
                            if (ok && !idCard.isEmpty()) {
                                // 弹出输入对话框，要求用户输入星期几
                                QString dayInput = QInputDialog::getText(this, "输入星期几", "请输入星期几 (1-7，1为星期一，7为星期日):", QLineEdit::Normal, "", &ok);
                                if (ok && !dayInput.isEmpty()) {
                                    int day = dayInput.toInt();
                                    if (day < 1 || day > 7) {
                                        QMessageBox::warning(this, "输入错误", "请输入有效的星期几 (1-7)！");
                                        return;
                                    }

                                    // 检查航班是否在该天有
                                    if (!flight.schedule[day - 1]) { // day - 1 因为数组从0开始
                                        QString availableDays;
                                        for (int i = 0; i < 7; ++i) {
                                            if (flight.schedule[i]) {
                                                availableDays += QString::number(i + 1) + " "; // i + 1 转换为星期几
                                            }
                                        }
                                        QMessageBox::warning(this, "无航班", "该航班在今天没有航班，"
                                                                             "可用的航班在星期: " + availableDays.trimmed());
                                        return; // 提前返回
                                    }

                                    int number = dayInput.toInt();
                                    FlightTicket* FT = new FlightTicket(flight,number) ;
                                    // 创建用户对象
                                    User user(name, idCard, *FT);

                                    // 显示订票成功的消息
                                    QMessageBox::information(this, "订票成功", "航班 " + flight.flightNumber + " 已成功预订！");

                                    // 保存 user 对象，或进行后续处理
                                    UM.addUser(user);
                                }
                            }
                        }
                        UM.printAllUsers();
                        UM.saveUsersToFileApp("D:\\数据结构课设\\plane\\untitled\\users.txt");
                    });

                    // 将按钮添加到布局中
                    flightLayout->addWidget(bookButton);

                    // 设置 flightWidget 的布局
                    flightWidget->setLayout(flightLayout);

                    // 将 flightWidget 添加到主布局中
                    layout->addWidget(flightWidget);
                }
            }
        }
        // 更新 UI
        layout->update();
    }else{
        auto F = FS.getFlights();
        for( const auto& flight : F){
            if(flight.flightNumber==num){
                auto info = flight.getInfo();
                // 创建一个新的QWidget来显示航班信息和按钮
                QWidget* flightWidget = new QWidget(this);
                QHBoxLayout* flightLayout = new QHBoxLayout(flightWidget);

                // 添加航班信息
                QLabel* infoLabel = new QLabel(info, this);
                infoLabel->setWordWrap(true);
                infoLabel->setMaximumWidth(500);
                flightLayout->addWidget(infoLabel);

                // 创建订票按钮
                QPushButton* bookButton = new QPushButton("订票", this);
                connect(bookButton, &QPushButton::clicked, this, [this,flight]() {
                    qDebug() << "Booking flight:" << flight.flightNumber;

                    // 弹出输入对话框，要求用户输入姓名
                    bool ok;
                    QString name = QInputDialog::getText(this, "输入姓名", "姓名:", QLineEdit::Normal, "", &ok);
                    if (ok && !name.isEmpty()) {
                        // 弹出输入对话框，要求用户输入身份证号
                        QString idCard = QInputDialog::getText(this, "输入身份证号", "身份证号:", QLineEdit::Normal, "", &ok);
                        if (ok && !idCard.isEmpty()) {
                            // 弹出输入对话框，要求用户输入星期几
                            QString dayInput = QInputDialog::getText(this, "输入星期几", "请输入星期几 (1-7，1为星期一，7为星期日):", QLineEdit::Normal, "", &ok);
                            if (ok && !dayInput.isEmpty()) {
                                int day = dayInput.toInt();
                                if (day < 1 || day > 7) {
                                    QMessageBox::warning(this, "输入错误", "请输入有效的星期几 (1-7)！");
                                    return;
                                }

                                // 检查航班是否在该天有
                                if (!flight.schedule[day - 1]) { // day - 1 因为数组从0开始
                                    QString availableDays;
                                    for (int i = 0; i < 7; ++i) {
                                        if (flight.schedule[i]) {
                                            availableDays += QString::number(i + 1) + " "; // i + 1 转换为星期几
                                        }
                                    }
                                    QMessageBox::warning(this, "无航班", "该航班在今天没有航班，"
                                                                         "可用的航班在星期: " + availableDays.trimmed());
                                    return; // 提前返回
                                }

                                int number = dayInput.toInt();
                                FlightTicket* FT = new FlightTicket(flight,number) ;
                                // 创建用户对象
                                User user(name, idCard, *FT);

                                // 显示订票成功的消息
                                QMessageBox::information(this, "订票成功", "航班 " + flight.flightNumber + " 已成功预订！");

                                // 保存 user 对象，或进行后续处理
                                UM.addUser(user);
                            }
                        }
                    }
                    UM.printAllUsers();
                    UM.saveUsersToFileApp("D:\\数据结构课设\\plane\\untitled\\users.txt");

                });

                // 将按钮添加到布局中
                flightLayout->addWidget(bookButton);

                // 设置 flightWidget 的布局
                flightWidget->setLayout(flightLayout);

                // 将 flightWidget 添加到主布局中
                layout->addWidget(flightWidget);
            }
        }


    }

}
void BookTicket::on_pushButton_2_released()
{
    // 获取 shuchuWidget 的布局
    QVBoxLayout* layout = static_cast<QVBoxLayout*>(ui->scrollArea->widget()->layout());
    while (QLayoutItem* item = layout->takeAt(0)) {
        delete item->widget(); // 删除现有的子控件
        delete item; // 删除布局项
    }

    auto decity = ui->departure->toPlainText();
    auto arcity = ui->arrive->toPlainText();

    std::vector<QString> path = G.dijkstra(decity, arcity);
    if (path.empty()) {
        qDebug() << "No path found between" << decity << "and" << arcity;
        return; // 提前返回
    }
    qDebug() << "path before lambda:" << path.size();

    // 先展示前两个城市之间的线路
    decity = path[0];
    arcity = path[1];

    // 创建一个新的QWidget来显示航班信息
    QWidget* flightWidget = new QWidget(this);
    QHBoxLayout* flightLayout = new QHBoxLayout(flightWidget);

    // 获取航班信息
    QVector<Flight> flightsToCity = FS.findFlightsByCity(decity, arcity);

    // 为每个航班添加信息和按钮
    for (const auto& flight : flightsToCity) {
        qDebug() << "Found flight:" << flight.flightNumber;
        auto info = flight.getInfo();

        // 添加航班信息
        QLabel* infoLabel = new QLabel(info, this);
        infoLabel->setWordWrap(true);
        infoLabel->setMaximumWidth(500);
        flightLayout->addWidget(infoLabel);

        // 创建订票按钮
        QPushButton* bookButton = new QPushButton("起飞航班", this);
        connect(bookButton, &QPushButton::clicked, this, [flight, path, this, &flightLayout]() {
            qDebug() << "Booking flight:" << flight.flightNumber;
            qDebug() << "path:" << path.size();

            // 创建对话框
            QDialog inputDialog(this);
            QVBoxLayout* layout = new QVBoxLayout(&inputDialog);

            // 创建输入框并设置提示文本
            QLineEdit* dayInput = new QLineEdit(&inputDialog);
            dayInput->setPlaceholderText("Enter the day of the week (1 for Mon, 2 for Tue, ..., 7 for Sun)");
            layout->addWidget(dayInput);

            // 创建确认按钮
            QPushButton* confirmButton = new QPushButton("Confirm", &inputDialog);
            layout->addWidget(confirmButton);

            // 连接确认按钮的点击信号与QDialog的接受槽
            connect(confirmButton, &QPushButton::clicked, &inputDialog, &QDialog::accept);

            // 显示对话框并等待用户输入
            if (inputDialog.exec() == QDialog::Accepted) {
                bool ok;
                QString dayText = dayInput->text();
                int dayNumber = dayText.toInt(&ok);

                // 验证输入是否合法
                if (ok && dayNumber >= 1 && dayNumber <= 7) {
                    qDebug() << "Day selected:" << dayNumber;

                    // 确保传递的参数有效
                    if (path.empty() || flight.flightNumber.isEmpty()) {
                        qDebug() << "Invalid input parameters.";
                        return;
                    }

                    // 直接使用成员变量 sche
                    this->sche = createFlightSchedule(path, flight, FS, dayNumber);

                    if (this->sche.isEmpty()) {
                        qDebug() << "No flights found for the selected day.";
                    } else {
                        // 输出找到的航班信息
                        for (const auto& flightticket : sche) {
                            qDebug() << flightticket.getFlight().getInfo();
                        }
                        qDebug() << "Flights successfully scheduled!";
                    }
                } else {
                    qDebug() << "Invalid day input!";
                }
            }
        });

        // 将按钮添加到布局中
        flightLayout->addWidget(bookButton);
    }

    // 设置 flightWidget 的布局
    flightWidget->setLayout(flightLayout);

    // 获取主布局并添加 flightWidget
    QVBoxLayout* mainLayout = static_cast<QVBoxLayout*>(ui->scrollArea->widget()->layout());
    mainLayout->addWidget(flightWidget);

    // 更新 UI
    mainLayout->update();
}




void BookTicket::on_pushButton_3_released()
{
    // 获取 shuchuWidget 的布局
    QVBoxLayout* layout = static_cast<QVBoxLayout*>(ui->scrollArea->widget()->layout());
    while (QLayoutItem* item = layout->takeAt(0)) {
        delete item->widget(); // 删除现有的子控件
        delete item; // 删除布局项
    }
    // 创建一个新的QWidget来显示航班信息
    QWidget* flightWidget = new QWidget(this);
    QHBoxLayout* flightLayout = new QHBoxLayout(flightWidget);
    if (this->sche.isEmpty()) {
        qDebug() << "No flights found for the selected day.";}
    for (const auto& flightticket : this->sche) {
        qDebug() << "Found flight:" << flightticket.getFlight().flightNumber;
        auto info = flightticket.getInfo();

        // 添加航班信息
        QLabel* infoLabel = new QLabel(info, this);
        infoLabel->setWordWrap(true);
        infoLabel->setMaximumWidth(500);
        flightLayout->addWidget(infoLabel);
    }
    QPushButton* bookButton = new QPushButton("我已确认航班信息", this);
    connect(bookButton, &QPushButton::clicked, this, [this]() {
        // 弹出输入框让用户输入姓名和身份证号
        QDialog inputDialog(this);
        inputDialog.setWindowTitle("请输入个人信息");

        QVBoxLayout* layout = new QVBoxLayout(&inputDialog);

        // 姓名输入框
        QLineEdit* nameInput = new QLineEdit(&inputDialog);
        nameInput->setPlaceholderText("请输入您的姓名");
        layout->addWidget(nameInput);

        // 身份证号输入框
        QLineEdit* idInput = new QLineEdit(&inputDialog);
        idInput->setPlaceholderText("请输入您的身份证号");
        layout->addWidget(idInput);

        // 确认按钮
        QPushButton* confirmButton = new QPushButton("确认", &inputDialog);
        layout->addWidget(confirmButton);

        // 确认按钮点击后处理输入
        connect(confirmButton, &QPushButton::clicked, &inputDialog, &QDialog::accept);

        // 显示对话框
        if (inputDialog.exec() == QDialog::Accepted) {
            QString name = nameInput->text();
            QString idCard = idInput->text();

            // 验证输入
            if (name.isEmpty() || idCard.isEmpty()) {
                QMessageBox::warning(this, "输入错误", "请填写完整的姓名和身份证号");
                return;
            }

            // 处理用户输入的姓名和身份证号（例如打印）
            qDebug() << "用户姓名：" << name;
            qDebug() << "身份证号：" << idCard;
            for(auto flightticket : sche){
                 User user(name, idCard, flightticket);
                 UM.addUser(user);
            }

        }
        UM.printAllUsers();
        UM.saveUsersToFileApp("D:\\数据结构课设\\plane\\untitled\\flight.xlsx");
    });


    flightLayout->addWidget(bookButton);
    // 设置 flightWidget 的布局
    flightWidget->setLayout(flightLayout);

    // 获取主布局并添加 flightWidget
    QVBoxLayout* mainLayout = static_cast<QVBoxLayout*>(ui->scrollArea->widget()->layout());
    mainLayout->addWidget(flightWidget);

    // 更新 UI
    mainLayout->update();
}
