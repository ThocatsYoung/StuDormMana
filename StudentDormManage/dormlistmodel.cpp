#include "dormlistmodel.h"

DormListModel::DormListModel(QList<dorm> *p, QObject *parent)
    : m_list_dorm(p),QAbstractListModel(parent)
{
}

DormListModel::~DormListModel()
{
    m_list_dorm = NULL;
}

QVariant DormListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return QString("Column %1").arg(section);
    else
        return QString("Row %1").arg(section);
    // FIXME: Implement me!
}

int DormListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;
    return m_list_dorm->count();

    // FIXME: Implement me!
}

QVariant DormListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= m_list_dorm->size())
        return QVariant();
    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    if (role == Qt::DisplayRole)
        return QString("%1").arg((m_list_dorm->at(index.row()).GetDormNumber()));
    else
        return QVariant();
    // FIXME: Implement me!
    return QVariant();
}

void DormListModel::set_list_dorm(QList<dorm> *list_dorm)
{
    m_list_dorm = list_dorm;
}
