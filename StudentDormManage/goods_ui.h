#ifndef GOODS_UI_H
#define GOODS_UI_H

#include <QWidget>

namespace Ui {
class goods_ui;
}

class goods_ui : public QWidget
{
    Q_OBJECT

public:
    explicit goods_ui(QWidget *parent = 0);
    ~goods_ui();

private:
    Ui::goods_ui *ui;
};

#endif // GOODS_UI_H
