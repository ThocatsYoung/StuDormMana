#ifndef GOODSRECORD_ADD_H
#define GOODSRECORD_ADD_H

#include <QDialog>
#include <QMessageBox>
#include "goods.h"
#include "read_from_file.h"
#include <QDate>


namespace Ui {
class goodsrecord_add;
}

class goodsrecord_add : public QDialog
{
    Q_OBJECT

public:
    explicit goodsrecord_add(QWidget *parent = 0);
    ~goodsrecord_add();
    void edit_line(QString Goodsname, QString Nownumber);
    int get_usenumber();

signals:
    void send_MSG_goodsrecord(goods_record Goods_record);


private slots:
    void on_buttonBox_accepted();

private:
    Ui::goodsrecord_add *ui;
};

#endif // GOODSRECORD_ADD_H
