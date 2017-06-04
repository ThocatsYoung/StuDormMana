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
    explicit StudentListModel(QList<student> *s = 0,
                              QObject *parent = 0);
    ~StudentListModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    //友元类
    friend class DormListModel;

    student* get_student_info_at(int index);    //获取选定学生信息

    void set_student_list(QList<student> *sl);  //设置底层数据

public slots:

    void slot_to_set_student_list(QList<student> *sl);

private:
    QStringList headers;

    QList<student> *student_list;   //指向住宿学生数据

};

#endif // STUDENTLISTMODEL_H
