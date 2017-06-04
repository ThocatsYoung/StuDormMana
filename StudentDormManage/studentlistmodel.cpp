#include "studentlistmodel.h"

StudentListModel::StudentListModel(QList<student> *s,
                                   QObject *parent)
    :student_list(s), QAbstractTableModel(parent)
{
    //设置表头
    headers << tr("姓名") << tr("学号") <<
               tr("学院") << tr("联系方式");
}

StudentListModel::~StudentListModel()
{
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
    if (student_list == NULL)
        return 0;
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
    if (student_list == NULL)
        return QVariant();
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

        int xueyuan_number = p->GetXueYuan();
        QString text_xueyuan = student::list_of_XueYuan.value(xueyuan_number,
                                                              student::list_of_XueYuan.last());
        //设置学院项文本，若下标过界则返回最后一个

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
            return text_xueyuan;
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

student* StudentListModel::get_student_info_at(int index)
{
    return &(student_list->operator [](index));
}

void StudentListModel::set_student_list(QList<student> *sl)
{
    student_list = sl;
    emit layoutChanged();
}



void StudentListModel::slot_to_set_student_list(QList<student> *sl)
{
    this->set_student_list(sl);
}
