#include "dorm_repair_show.h"
#include "ui_dorm_repair_show.h"



//model
dorm_repair_model::dorm_repair_model(QObject *parent):
    QAbstractTableModel(parent), m_list_dorm_repair(NULL)
{
    headers << "宿舍" << "报修说明" << "报修时间";
}

dorm_repair_model::~dorm_repair_model()
{
    m_list_dorm_repair = NULL;
}

QVariant dorm_repair_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();
    if(orientation == Qt::Horizontal)
        return headers.at(section);
    else
        return QVariant();
}

int dorm_repair_model::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    if(m_list_dorm_repair == NULL)
        return 0;
    return m_list_dorm_repair->count();
}

int dorm_repair_model::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;
    return headers.count();
}

QVariant dorm_repair_model::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row() >= m_list_dorm_repair->size())
        return QVariant();
    if(role == Qt::TextAlignmentRole)
        return int(Qt::AlignHCenter | Qt::AlignVCenter);
    if(role == Qt::DisplayRole)
    {
        const dorm_repair *drp = &(m_list_dorm_repair->at(index.row()));
        //根据下标不同返回不同数据
        switch(index.column())
        {
        case 0: return QString("%1").arg(drp->dormnumber); break;
        case 1: return QString("%1").arg(drp->repair_case); break;
        case 2: return QString("%1").arg(drp->report_date.toString("yyyy-MM-dd")); break;
        default: return QVariant(); break;
        }
    }
    else return QVariant();
    return QVariant();
}

void dorm_repair_model::setList_dorm_repair(QList<dorm_repair> *list_dorm_repair)
{
    m_list_dorm_repair = list_dorm_repair;
}

void dorm_repair_model::add_new_dorm_repair(dorm_repair Dorm_repair)
{
    m_list_dorm_repair->prepend(Dorm_repair);
    emit layoutChanged();
}



//ui
dorm_repair_show::dorm_repair_show(QString path, QString finish_path, QWidget *parent) :
    dorm_repair_file_path(path), finish_file_path(finish_path),data_dorm_need_to_repair(NULL),
    data_finish(NULL), QWidget(parent),
    ui(new Ui::dorm_repair_show)
{
    ui->setupUi(this);

    //宿舍号限制只输入数字
    QRegExp regx_dorm("[1-9][0-9]{0,2}");
    QValidator *edit_regx_dorm = new QRegExpValidator(regx_dorm, ui->lineEdit_dorm);
    ui->lineEdit_dorm->setValidator(edit_regx_dorm);


    //设置view选取模式
    ui->tableView_dorm_repair->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_dorm_repair->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_dorm_repair->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //初始化维修记录数据
    data_dorm_need_to_repair = new QList<dorm_repair>();
    read_file_to_container(dorm_repair_file_path, *data_dorm_need_to_repair);

    data_finish = new QList<repair_record>();
    read_file_to_container(finish_file_path, *data_finish);


    //初始化维修记录model
    model_dorm_repair = new dorm_repair_model();
    model_dorm_repair->setList_dorm_repair(data_dorm_need_to_repair);
    ui->tableView_dorm_repair->setModel(model_dorm_repair);

}

dorm_repair_show::~dorm_repair_show()
{
    //保存维修记录
    write_container_to_file(*data_dorm_need_to_repair, dorm_repair_file_path);
    write_container_to_file(*data_finish, finish_file_path);


    delete ui;
    delete model_dorm_repair;
    delete data_dorm_need_to_repair;
    delete data_finish;
}


//添加报修记录
void dorm_repair_show::on_pushButton_add_repair_clicked()
{
    Dialog_addrepair *dialog_addrepair = new Dialog_addrepair(this);
    dialog_addrepair->edit_dorm_num(ui->lineEdit_dorm->text());
    connect(dialog_addrepair, Dialog_addrepair::send_MSG_of_repair,
            this->model_dorm_repair, dorm_repair_model::add_new_dorm_repair);
    dialog_addrepair->exec();
}

//确认该报修事项已完成维修
void dorm_repair_show::on_pushButton_finish_clicked()
{
    if(ui->tableView_dorm_repair->model()->rowCount() == 0)
    {
        QMessageBox::warning(this, tr("警告"), tr("没有报修记录"));
        return;
    }

    int row_tobe_finished = ui->tableView_dorm_repair->currentIndex().row();
    int reply = QMessageBox::question(this, tr("询问"), tr("确定维修已完成？"),
                                      QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes)
    {
        QString Dorm_num = (data_dorm_need_to_repair->at(row_tobe_finished)).dormnumber;
        QString Repair_case = (data_dorm_need_to_repair->at(row_tobe_finished)).repair_case;
        QDate Report_Date =(data_dorm_need_to_repair->at(row_tobe_finished)).report_date;
        QDate Finish_Date = QDate::currentDate();

        repair_record Repair_Record(Dorm_num, Repair_case, Report_Date, Finish_Date);
        data_finish->prepend(Repair_Record);
        data_dorm_need_to_repair->removeAt(row_tobe_finished);
        emit ui->tableView_dorm_repair->model()->layoutChanged();
    }
    else {
        return;
    }
}


//查看已完成的维修记录
void dorm_repair_show::on_pushButton_repair_record_clicked()
{
    QListWidget *listWidget_repair_finish_record = new QListWidget(this);
    QListIterator<repair_record> repair_record_i(*data_finish);
    while(repair_record_i.hasNext())
    {
        const repair_record *p = &(repair_record_i.next());

        QString s =QString("%1").arg(p->dormnumber) + "    "
                + QString("%1").arg(p->repair_case) + "    "
                + QString("%1").arg(p->report_date.toString("yyyy-MM-dd")) +"    "
                + QString("%1").arg(p->finish_date.toString("yyyy-MM-dd"));

        listWidget_repair_finish_record->addItem(new QListWidgetItem(s));
    }

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(listWidget_repair_finish_record);

    QDialog *repair_record_finish = new QDialog(this);
    repair_record_finish->setWindowTitle("维修记录");
    repair_record_finish->setLayout(layout);
    repair_record_finish->show();
}
