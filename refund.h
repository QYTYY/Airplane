#ifndef REFUND_H
#define REFUND_H

#include <QMainWindow>

namespace Ui {
class refund;
}

class refund : public QMainWindow
{
    Q_OBJECT

public:
    explicit refund(QWidget *parent = nullptr);
    ~refund();

private:
    Ui::refund *ui;
};

#endif // REFUND_H
