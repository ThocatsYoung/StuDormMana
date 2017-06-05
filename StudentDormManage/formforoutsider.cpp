#include "formforoutsider.h"
#include "ui_formforoutsider.h"

//model外来人员模板实现
wailairenlistmodel::wailairenlistmodel(QObject *parent):
    QAbstractTableModel(parent), m_list_records(NULL)
{
    headers << "姓名" << "性别" << "学号" << "联系方式" << "日期";//设置表头
}


//析构函数
wailairenlistmodel::~wailairenlistmodel()
{
    m_list_records = NULL;
}

QVariant wailairenlistmodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return headers.at(section);
    else
        return QVariant();
}


//计算行数
int wailairenlistmodel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    if (m_list_records == NULL)
        return 0;
    return m_list_records->count();
}


//计算列数
int wailairenlistmodel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return headers.count();
}


//设置表格数据
QVariant wailairenlistmodel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (index.row() >= m_list_records->size())
        return QVariant();
    if (role == Qt::TextAlignmentRole)
    {
         return int(Qt::AlignHCenter | Qt::AlignVCenter);
    }

    if (role == Qt::DisplayRole)
    {
        const outsider *p = &(m_list_records->at(index.row()));
        //根据下标不同返回不同数据
        switch(index.column())
        {
        case 0:
            return QString("%1").arg(p->GetName());//名字
            break;
        case 1:
            return QString("%1").arg(outsider::
                                     sex_things.at(p->get_sex()));//性别
            break;
        case 2:
            return QString("%1").arg(p->GetIdNumber());//证件号
            break;
        case 3:
            return QString("%1").arg(p->GetContact());//联系方式
            break;
        case 4:
            return QString("%1").arg(p->GetComeTime().toString("yyyy-MM-dd"));//时间
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

//设置外来人员记录链表
void wailairenlistmodel::setList_records(QList<outsider> *list_records)
{
    m_list_records = list_records;
}


//添加外来人员记录
void wailairenlistmodel::add_new_record(outsider new_record)
{
    m_list_records->prepend(new_record);
    emit layoutChanged();
}




//ui外来人员界面实现
FormForOutsider::FormForOutsider(QString path, QString past_path,  QWidget *parent) :
    file_path(path), past_file_path(past_path), model_records(NULL), QWidget(parent),
    ui(new Ui::FormForOutsider)
{
    ui->setupUi(this);
    //设置view选取模式
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //初始化来访记录数据(文件读写)
    read_file_to_container(file_path, data_records);
    read_file_to_container(past_file_path, data_pastrecords);


    //初始化来访记录model
    model_records = new wailairenlistmodel();
    model_records->setList_records(&data_records);
    ui->tableView->setModel(model_records);
}


//析构函数
FormForOutsider::~FormForOutsider()
{
    //保存当前违纪记录数据
    write_container_to_file(data_records, file_path);
    write_container_to_file(data_pastrecords, past_file_path);


    delete ui;
    delete model_records;
}

//添加外来人员来访记录
void FormForOutsider::on_pushButton_add_outsider_record_clicked()
{
    dialog_wailairen_add *dialog = new dialog_wailairen_add(this);//添加外来人员记录的对话框
    connect(dialog, dialog_wailairen_add::send_MSG_of_wailairen,
            this->model_records, wailairenlistmodel::add_new_record);//信号槽函数
    dialog->exec();
}


//删除外访记录
void FormForOutsider::on_pushButton_finish_outsider_record_clicked()
{
    if(ui->tableView->model()->rowCount() == 0)
    {
        warning_message_box("没有可删除的来访记录");
        return;
    }
    int row_tobe_removed = ui->tableView->currentIndex().row();
    int reply = QMessageBox::question(this,tr("询问"),tr("确定删除该记录？"),
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        data_records.removeAt(row_tobe_removed);
        emit ui->tableView->model()->layoutChanged();
    }
    else
        return;
}


//将当前记录移入历史记录
void FormForOutsider::on_pushButton_clicked()
{
    if(ui->tableView->model()->rowCount() == 0)
    {
        warning_message_box("没有可移动的记录");
        return;
    }

    int reply = QMessageBox::question(this,tr("询问"),tr("确定将当前所有记录移入历史记录？"),
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        //当前记录写入历史记录
        QMutableListIterator<outsider> i(data_records);
        i.toBack();
        while(i.hasPrevious())
        {
            data_pastrecords.prepend(i.previous());
        }
        data_records.clear();  //清空当前记录链表
        emit ui->tableView->model()->layoutChanged();
    }
    else
        return;
}


//展示历史记录
void FormForOutsider::on_pushButton_show_past_clicked()
{
    QListWidget *listWidget_past_records = new QListWidget(this);
    listWidget_past_records->setFixedSize(500,400);
    QListIterator<outsider> i(data_pastrecords);
    while(i.hasNext())
    {
        const outsider *p = &(i.next());
        QString s = QString("%1").arg(p->GetComeTime().toString("yyyy-MM-dd--hh-mm"))
                +"    "+QString("%1").arg(p->GetName())
                +"    "+QString("%1").arg(outsider::sex_things.at(p->get_sex()))
                +"    "+"联系方式："+QString("%1").arg(p->GetContact())
                +"    "+"ID："+QString("%1").arg(p->GetIdNumber());
        listWidget_past_records->addItem(new QListWidgetItem(s));
    }


    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(listWidget_past_records);

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("来访人历史记录");
    dialog->setLayout(layout);
    dialog->show();
}
