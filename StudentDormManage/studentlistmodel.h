#ifndef STUDENTLISTMODEL_H
#define STUDENTLISTMODEL_H

#include <QAbstractTableModel>

#include "people.h"
#include "room.h"
#include "read_from_file.h"

#include <QStringListModel>
#include "dormlistmodel.h"

//失误,继承了TableModel但是命名错了
class StudentListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit StudentListModel(QList<dorm> *d, QList<student> *s,
                              QObject *parent = 0);
    ~StudentListModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void set_student_list(QList<student> *sl);
    //友元类
    friend class DormListModel;

public slots:
    void set_which_dorm(QModelIndex in);    //以下标设置学生链表指针

private:
    QStringList headers;
    QList<dorm> *dorm_list; //用于与宿舍号选取对应数据
    QList<student> *student_list;   //指向住宿学生数据

};

#endif // STUDENTLISTMODEL_H
