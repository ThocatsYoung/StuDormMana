#include "studentlistmodel.h"

StudentListModel::StudentListModel(QList<dorm> *d, QList<student> *s,
                                   QObject *parent)
    : dorm_list(d), student_list(s), QAbstractTableModel(parent)
{
    //设置表头
    headers << tr("姓名") << tr("学号") <<
               tr("学院") << tr("联系方式");
}

StudentListModel::~StudentListModel()
{
    dorm_list = NULL;
    student_list = NULL;
}

QVariant StudentListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return headers.at(section);
    else
        return QVariant();
    // FIXME: Implement me!
}

int StudentListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return student_list->count();

    // FIXME: Implement me!
}

int StudentListModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return headers.count();

    // FIXME: Implement me!
}

QVariant StudentListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= student_list->size())
        return QVariant();
    if (role == Qt::TextAlignmentRole)
    {
         return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    if (role == Qt::DisplayRole)
    {
        const student *p = &(student_list->at(index.row()));
        //根据下标不同返回不同数据
        switch(index.column())
        {
        case 0:
            return QString("%1").arg(p->GetName());
            break;
        case 1:
            return QString("%1").arg(p->GetStudentId());
            break;
        case 2:
            return QString("%1").arg(p->GetXueYuan());
            break;
        case 3:
            return QString("%1").arg(p->GetContact());
            break;
        default:
            return QVariant();
            break;
        }
    }
    else
        return QVariant();
    // FIXME: Implement me!
    return QVariant();
}

void StudentListModel::set_student_list(QList<student> *sl)
{
    student_list = sl;
    emit layoutChanged();
}

void StudentListModel::set_which_dorm(QModelIndex in)
{
    qint16 ok = in.row();
    if(ok >= (dorm_list->size()))
        return;  
    this->set_student_list(&((*dorm_list)[ok].StuDorm));
}
