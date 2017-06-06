#ifndef GOODS_RECORD_SHOW_H
#define GOODS_RECORD_SHOW_H

#include <QWidget>
#include <QDateTime>
#include <QList>
#include <QAbstractTableModel>

#include <QListWidget>
#include <QLayout>
#include <QDialog>
#include <QComboBox>
#include <QDateEdit>

#include "read_from_file.h"
#include "goods.h"
#include "goodsrecord_add.h"
#include "dialog_addgoods.h"


//goodsrecord_model
class goods_record_model: public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit goods_record_model(QObject *parent = 0);
    ~goods_record_model();

    //header
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    //basic functionality
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayPropertyRole) const override;


    void setList_goodsrecord(QList<goods_record> *list_goodsrecord);

private:
    QStringList header;
    QList<goods_record> *m_list_goodsrecord;

};


//goods_model
class goods_model: public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit goods_model(QObject *parent = 0);
    ~goods_model();

    //header
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    //basic functionality
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setList_goods(QList<goods> *list_goods);
    void add_new_goods(goods Goods);

private:
    QStringList header;
    QList<goods> *m_list_goods;
};



//ui
namespace Ui {
class goods_record_show;
}

class goods_record_show : public QWidget
{
    Q_OBJECT

public:
    explicit goods_record_show(QString goodsrecord_path, QString goodsrecord_past_path,
                               QString goods_path, QWidget *parent = 0);
    ~goods_record_show();





private slots:

    void borrow_when_double_clicked(QModelIndex index);

    void on_pushButton_addgoods_clicked();

    void on_pushButton_2_deletegoods_clicked();


    void on_pushButton_back_clicked();

    void on_pushButton_scan_goodshistory_clicked();

    void add_new_record_of_borrow(goods_record);


private:
    Ui::goods_record_show *ui;
    QString goodsrecord_file_path;
    QString goodsrecord_past_file_path;
    QString goods_file_path;
    goods_record_model *model_goodsrecord;  //model
    goods_model *model_goods;
    QList<goods_record> *data_goodsrecord;       //当前记录
    QList<goods_record> *data_past_goodsrecord;  //历史记录
    QList<goods> *data_goods;
};

#endif // GOODS_RECORD_SHOW_H
