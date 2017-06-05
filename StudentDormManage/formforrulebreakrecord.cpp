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



//ui
FormForRuleBreakRecord::FormForRuleBreakRecord(QString path, QString past_path,
                                               QSet<quint16> *p, QWidget *parent) :
    file_path(path), past_file_path(past_path),
    point_to_set_of_dorm_number(p),
    model_records(NULL), QWidget(parent),
    ui(new Ui::FormForRuleBreakRecord)
{
    ui->setupUi(this);

    //设置view选取模式
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode (QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //初始化违纪记录数据(文件读写)
    read_file_to_container(file_path, data_records);
    read_file_to_container(past_file_path, data_pastrecords);


    //初始化违纪记录model
    model_records = new RuleBreakRecordModel();
    model_records->setList_records(&data_records);
    ui->tableView->setModel(model_records);
}

FormForRuleBreakRecord::~FormForRuleBreakRecord()
{
    //保存当前违纪记录数据
    save_record_to_file();

    point_to_set_of_dorm_number = NULL;
    delete ui;
    if (model_records != NULL)
    {
        delete model_records;
    }
}

void FormForRuleBreakRecord::save_record_to_file()
{
    write_container_to_file(data_records, file_path);
    write_container_to_file(data_pastrecords, past_file_path);
    return;
}

void FormForRuleBreakRecord::add_new_record(record_rulebreak new_record)
{
    data_records.prepend(new_record);   //添加数据
    emit model_records->layoutChanged();   //通知视图
}



void FormForRuleBreakRecord::on_pushButton_add_rulebreaker_record_clicked()
{
    //建立添加记录对话框
    Dialog_rulebreak_add *dialog = new Dialog_rulebreak_add(point_to_set_of_dorm_number, this);
    connect(dialog, Dialog_rulebreak_add::send_MSG_of_rulebreak,
            this, FormForRuleBreakRecord::add_new_record);
    dialog->exec();
}

void FormForRuleBreakRecord::on_pushButton_finish_rulebreaker_record_clicked()
{
    if(model_records->rowCount() == 0)
    {
        warning_message_box("没有可删除的违纪记录");
        return;
    }

    int row_tobe_removed = ui->tableView->currentIndex().row();//获取要被删除的行号

    if (row_tobe_removed >= data_records.count()
            || row_tobe_removed < 0)
    {
        warning_message_box("未选中违纪记录");
        return;
    }

    int reply = ask_yes_or_no("确定删除该记录？");
    if(reply == true)
    {
        data_records.removeAt(row_tobe_removed);
        emit model_records->layoutChanged();
    }
    else
        return;
}

void FormForRuleBreakRecord::on_pushButton_remove_to_past_clicked()    //将当前记录移入历史记录
{
    if(ui->tableView->model()->rowCount() == 0)
    {
        warning_message_box("没有可移动的记录");
        return;
    }

    bool reply = ask_yes_or_no("确定将当前所有记录移入历史记录？");
    if(reply == true)
    {
        //当前记录写入历史记录
        QMutableListIterator<record_rulebreak> i(data_records);
        i.toBack();
        while(i.hasPrevious())
        {
            data_pastrecords.prepend(i.previous());
        }
        data_records.clear();  //清空当前记录链表
        emit model_records->layoutChanged();
    }
    else
        return;
}

void FormForRuleBreakRecord::on_pushButton_show_past_clicked()  //展示历史记录
{
//建立用于展示的 listWidget
    QListWidget *listWidget_past_records = new QListWidget(this);
    //将历史记录数据读入 listWidget
    QListIterator<record_rulebreak> i(data_pastrecords);
    while(i.hasNext())
    {
        const record_rulebreak *p = &(i.next());
        listWidget_past_records->addItem(new QListWidgetItem(p->toString()));
    }

    QHBoxLayout *layout = new QHBoxLayout(this);    //建立layout
    layout->addWidget(listWidget_past_records); //将 listWidget 放入 layout
//建立dialog
    QDialog *dialog = new QDialog(this);
    dialog->setWindowTitle("宿舍违纪历史记录");
    dialog->setLayout(layout);
    dialog->exec();
}


void FormForRuleBreakRecord::on_pushButton_clear_past_clicked()
{
    bool reply = ask_yes_or_no("文件中的数据也将会清空\n确定清空历史记录？");
    if (reply == true){
        data_pastrecords.clear();
        write_container_to_file(data_pastrecords, past_file_path);
        information_message_box("历史数据已经清除。");
    }
    else{
        return;
    }
}
