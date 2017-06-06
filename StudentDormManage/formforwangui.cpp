#include "formforwangui.h"
#include "ui_formforwangui.h"

//model晚归登记模板实现
wanguilistmodel::wanguilistmodel(QObject *parent):
    QAbstractTableModel(parent), m_list_records(NULL)
{
    headers << "宿舍号" << "姓名" << "晚归时间" << "联系方式"<< "学号";//表头信息
}

//析构函数
wanguilistmodel::~wanguilistmodel()
{
    m_list_records = NULL;
}


//表头
QVariant wanguilistmodel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return headers.at(section);
    else
        return QVariant();
}

//计算行数
int wanguilistmodel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    if (m_list_records == NULL)
        return 0;
    return m_list_records->count();
}

//计算列数
int wanguilistmodel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return headers.count();
}

//设置表格数据
QVariant wanguilistmodel::data(const QModelIndex &index, int role) const
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
        const outschool *p = &(m_list_records->at(index.row()));
        //根据下标不同返回不同数据
        switch(index.column())
        {
        case 0:
            return QString("%1").arg(p->GetDormNumber());//宿舍号
            break;
        case 1:
            return QString("%1").arg(p->GetName());//名字
            break;
        case 2:
            return QString("%1").arg(p->GetOutTime().toString("yyyy-MM-dd--hh--mm"));//晚归时间
            break;
        case 3:
            return QString("%1").arg(p->GetContact());//联系方式
            break;
        case 4:
            return QString("%1").arg(p->GetIdNumber());//学号
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

//设置晚归记录链表
void wanguilistmodel::setList_records(QList<outschool> *list_records)
{
    m_list_records = list_records;
}

//添加晚归记录
void wanguilistmodel::add_new_record(outschool new_record)
{
    m_list_records->prepend(new_record);
    emit layoutChanged();
}




//ui晚归记录界面实现
Formforwangui::Formforwangui(QString path, QString past_path, QMap<QString, student*> *map, QWidget *parent) :
        file_path(path), past_file_path(past_path), outmap(map), model_records(NULL),QWidget(parent),
    ui(new Ui::Formforwangui)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    //设置view选取模式
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //初始化来访记录数据(文件读写)
    read_file_to_container(file_path, data_records);
    read_file_to_container(past_file_path, data_pastrecords);


    //初始化来访记录model
    model_records = new wanguilistmodel();
    model_records->setList_records(&data_records);
    ui->tableView->setModel(model_records);
}

//析构函数
Formforwangui::~Formforwangui()
{
    write_container_to_file(data_records, file_path);
    write_container_to_file(data_pastrecords, past_file_path);

    if (model_records != NULL)
    {
        delete model_records;
    }
    delete ui;
}


//添加晚归记录
void Formforwangui::on_pushButton_clicked()
{
    QString IdNumber= ui->lineEdit->text();
    if(IdNumber.isEmpty())
    {
        warning_message_box("学号不可为空");
        return;
    }    
    if(outmap == NULL)
    {
        warning_message_box("map数据错误！");
        return;
    }

    if(!outmap->contains(IdNumber))
    {
        warning_message_box("此学号不存在");
        return;
    }

    const student *pStu = outmap->value(IdNumber);
    QString Name = pStu->GetName();
    QString Contact = pStu->GetContact();
    quint16 DormNumber = pStu->GetDormNumber();
    QDateTime date = ui->dateTimeEdit->dateTime();
    outschool new_record(Name,DormNumber,IdNumber, Contact,date);
    this->model_records->add_new_record(new_record);
}


//删除晚归记录
void Formforwangui::on_pushButton_3_clicked()
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


//写入晚归历史记录
void Formforwangui::on_pushButton_2_clicked()
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
        QMutableListIterator<outschool> i(data_records);
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


//显示晚归历史记录
void Formforwangui::on_pushButton_4_clicked()
{
    QListWidget *listWidget_past_records = new QListWidget(this);
    listWidget_past_records->setFixedSize(500,400);
    QListIterator<outschool> i(data_pastrecords);
    while(i.hasNext())
    {
        const outschool *p = &(i.next());
        QString s = "离校时间："+QString("%1").arg(p->GetOutTime().toString("yyyy-MM-dd-hh-mm"))
                +"    "+QString("%1").arg(p->GetName())
                +"    "+"宿舍号："+QString("%1").arg(p->GetDormNumber())
                +"    "+"联系方式："+QString("%1").arg(p->GetContact())
                +"    "+"ID："+QString("%1").arg(p->GetIdNumber());
        listWidget_past_records->addItem(new QListWidgetItem(s));
    }


    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(listWidget_past_records);

    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("晚归登记历史记录");
    dialog->setLayout(layout);
    dialog->show();
}
