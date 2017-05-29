#include "formforrulebreakrecord.h"
#include "ui_formforrulebreakrecord.h"




//model
RuleBreakRecordModel::RuleBreakRecordModel(QObject *parent):
    QAbstractTableModel(parent), m_list_records(NULL)
{
    headers << "宿舍号" << "违纪行为" << "日期";
}

RuleBreakRecordModel::~RuleBreakRecordModel()
{
    m_list_records = NULL;
}

QVariant RuleBreakRecordModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
        return headers.at(section);
    else
        return QVariant();
}

int RuleBreakRecordModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    if (m_list_records == NULL)
        return 0;
    return m_list_records->count();
}

int RuleBreakRecordModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return headers.count();
}

QVariant RuleBreakRecordModel::data(const QModelIndex &index, int role) const
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
        const record_rulebreak *p = &(m_list_records->at(index.row()));
        //根据下标不同返回不同数据
        switch(index.column())
        {
        case 0:
            return QString("%1").arg(p->get_dorm_number());
            break;
        case 1:
            return QString("%1").arg(record_rulebreak::
                                     break_rule_things.at(p->get_breaked_rule()));
            break;
        case 2:
            return QString("%1").arg(p->get_date().toString("yyyy-MM-dd"));
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


void RuleBreakRecordModel::setList_records(QList<record_rulebreak> *list_records)
{
    m_list_records = list_records;
}

void RuleBreakRecordModel::add_new_record(record_rulebreak new_record)
{
    m_list_records->prepend(new_record);
    emit layoutChanged();
}



//ui
FormForRuleBreakRecord::FormForRuleBreakRecord(QString path, QString past_path,  QWidget *parent) :
    file_path(path), past_file_path(past_path), data_records(NULL), model_records(NULL), QWidget(parent),
    ui(new Ui::FormForRuleBreakRecord)
{
    ui->setupUi(this);

    //设置view选取模式
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //初始化违纪记录数据(文件读写)
    data_records = new QList<record_rulebreak>();
    QFile file(file_path);
    file.open(QIODevice::ReadOnly);
    QDataStream f(&file);
    f >> (*data_records);
    file.close();

    data_pastrecords = new QList<record_rulebreak>();
    QFile past_file(past_file_path);
    past_file.open(QIODevice::ReadOnly);
    QDataStream pf(&past_file);
    pf >> (*data_pastrecords);
    past_file.close();


    //初始化违纪记录model
    model_records = new RuleBreakRecordModel();
    model_records->setList_records(data_records);
    ui->tableView->setModel(model_records);
}

FormForRuleBreakRecord::~FormForRuleBreakRecord()
{
    //保存当前违纪记录数据
    QFile file(file_path);
    file.open(QIODevice::WriteOnly);
    QDataStream f(&file);
    f << (*data_records);
    file.close();

    QFile past_file(past_file_path);
    past_file.open(QIODevice::WriteOnly);
    QDataStream pf(&past_file);
    pf << (*data_pastrecords);
    past_file.close();


    delete ui;
    delete model_records;
    delete data_records;
}



void FormForRuleBreakRecord::on_pushButton_add_outsider_record_clicked()
{
    Dialog_rulebreak_add *dialog = new Dialog_rulebreak_add(this);
    connect(dialog, Dialog_rulebreak_add::send_MSG_of_rulebreak,
            this->model_records, RuleBreakRecordModel::add_new_record);
    dialog->exec();
}

void FormForRuleBreakRecord::on_pushButton_finish_outsider_record_clicked()
{
    if(ui->tableView->model()->rowCount() == 0)
    {
        QMessageBox::warning(this,tr("警告"),tr("没有可删除的违纪记录"));
        return;
    }
    int row_tobe_removed = ui->tableView->currentIndex().row();
    int reply = QMessageBox::question(this,tr("询问"),tr("确定删除该记录？"),
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        data_records->removeAt(row_tobe_removed);
        emit ui->tableView->model()->layoutChanged();
    }
    else
        return;
}

void FormForRuleBreakRecord::on_pushButton_clicked()
{
    if(ui->tableView->model()->rowCount() == 0)
    {
        QMessageBox::warning(this,tr("警告"),tr("没有可移动的记录"));
        return;
    }

    int reply = QMessageBox::question(this,tr("询问"),tr("确定将当前所有记录移入历史记录？"),
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        //当前记录写入历史记录
        QMutableListIterator<record_rulebreak> i(*data_records);
        while(i.hasNext())
        {
            data_pastrecords->prepend(i.next());
        }
        data_records->clear();
        emit ui->tableView->model()->layoutChanged();
    }
    else
        return;
}

void FormForRuleBreakRecord::on_pushButton_show_past_clicked()
{
    QListWidget *listWidget_past_records = new QListWidget();
    QListIterator<record_rulebreak> i(*data_pastrecords);
    while(i.hasNext())
    {
        const record_rulebreak *p = &(i.next());
        QString s = QString("%1").arg(p->get_date().toString("yyyy-MM-dd"))
                +"    "+QString("%1").arg(p->get_dorm_number())
                +"    "+QString("%1").arg(record_rulebreak::break_rule_things.at(p->get_breaked_rule()));
        listWidget_past_records->addItem(new QListWidgetItem(s));
    }


    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(listWidget_past_records);

    QDialog *dialog = new QDialog(this);
    dialog->setLayout(layout);
    dialog->show();
}
