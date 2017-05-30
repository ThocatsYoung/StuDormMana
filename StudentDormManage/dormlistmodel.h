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

    void set_list_dorm(QList<dorm> *list_dorm);

private:
    QList<dorm> *m_list_dorm;
};



#endif // DORMLISTMODEL_H
