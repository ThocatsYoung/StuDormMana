#ifndef DORMLISTMODEL_H
#define DORMLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "room.h"
#include "read_from_file.h"


class DormListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit DormListModel(QList<dorm> *p = 0,QObject *parent = 0);
    ~DormListModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void set_list_dorm(QList<dorm> *list_dorm); //设置源数据

    void add_dorm(dorm value);  //添加新纪录到源数据

private:
    QList<dorm> *m_list_dorm;   //底层数据 宿舍链表
};



#endif // DORMLISTMODEL_H
