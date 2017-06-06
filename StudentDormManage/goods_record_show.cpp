#include "goods_record_show.h"
#include "ui_goods_record_show.h"


//goodsrecord_model
goods_record_model::goods_record_model(QObject *parent):
    QAbstractTableModel(parent), m_list_goodsrecord(NULL)
{
    header << "物品" << "借用者" <<"联系电话" <<"借用数量" << "借用日期" << "归还期限";
}

goods_record_model::~goods_record_model()
{
    m_list_goodsrecord = NULL;
}

QVariant goods_record_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal)
        return header.at(section);
    else
        return QVariant();
}

int goods_record_model::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    if(m_list_goodsrecord == NULL)
        return 0;

    return m_list_goodsrecord->count();
}

int goods_record_model::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return header.count();
}

QVariant goods_record_model::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(index.row() >= m_list_goodsrecord->size())
        return QVariant();

    if(role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    }

    if(role == Qt::DisplayRole)
    {
        const goods_record *p_goodsrecord = &(m_list_goodsrecord->at(index.row()));
        switch(index.column())
        {
        case 0: return QString("%1").arg(p_goodsrecord->goodsname);break;
        case 1: return QString("%1").arg(p_goodsrecord->manname);break;
        case 2: return QString("%1").arg(p_goodsrecord->phonenumber);break;
        case 3: return QString("%1").arg(p_goodsrecord->usenumber);
        case 4: return QString("%1").arg(p_goodsrecord->borrowdate.toString("yyyy-MM-dd"));
        case 5: return QString("%1").arg(p_goodsrecord->backdate.toString("yyyy-MM-dd"));
        default: return QVariant();break;
        }
    }
    else
        return QVariant();
    return QVariant();
}

void goods_record_model::setList_goodsrecord(QList<goods_record> *list_goodsrecord)
{
    m_list_goodsrecord = list_goodsrecord;
}



//goods_model
goods_model::goods_model(QObject *parent):
    QAbstractTableModel(parent), m_list_goods(NULL)
{
    header << "物品" << "总数" << "余数";
}

goods_model::~goods_model()
{
    m_list_goods = NULL;
}

QVariant goods_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal)
        return header.at(section);
    else
        return QVariant();
}

int goods_model::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    if(m_list_goods == NULL)
        return 0;

    return m_list_goods->count();
}

int goods_model::columnCount(const QModelIndex &parent) const
{
    if(parent.isValid())
        return 0;

    return header.count();
}

QVariant goods_model::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(index.row() >= m_list_goods->size())
        return QVariant();
    if(role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    }

    if(role == Qt::DisplayRole)
    {
        const goods *goods_p = &(m_list_goods->at(index.row()));
        switch(index.column())
        {
        case 0: return QString("%1").arg(goods_p->goodsname); break;
        case 1: return QString("%1").arg(goods_p->total); break;
        case 2: return QString("%1").arg(goods_p->nownumber); break;
        default: return QVariant(); break;
        }
    }
    else
        return QVariant();
    return QVariant();
}

void goods_model::setList_goods(QList<goods> *list_goods)
{
    m_list_goods = list_goods;
}

void goods_model::add_new_goods(goods Goods)
{
    m_list_goods->prepend(Goods);
    emit layoutChanged();
}




//ui
goods_record_show::goods_record_show(QString goodsrecord_path, QString goodsrecord_past_path,
                                     QString goods_path, QWidget *parent) :
    goodsrecord_file_path(goodsrecord_path), goodsrecord_past_file_path(goodsrecord_past_path),
    goods_file_path(goods_path),
    data_goodsrecord(NULL), data_past_goodsrecord(NULL), data_goods(NULL),
    model_goodsrecord(NULL), model_goods(NULL), QWidget(parent),
    ui(new Ui::goods_record_show)
{
    ui->setupUi(this);

    //设置view选取模式
    //goods_record部分
    ui->tableView_goodrecord->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_goodrecord->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_goodrecord->setEditTriggers(QAbstractItemView::NoEditTriggers);


    //goods部分
    ui->tableView_goods->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_goods->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_goods->setEditTriggers(QAbstractItemView::NoEditTriggers);


    //初始化数据
    //goods_record
    data_goodsrecord = new QList<goods_record>();
    read_file_to_container(goodsrecord_file_path, *data_goodsrecord);

    data_past_goodsrecord = new QList<goods_record>();
    read_file_to_container(goodsrecord_past_file_path, *data_past_goodsrecord);



    //goods
    data_goods = new QList<goods>();
    read_file_to_container(goods_file_path, *data_goods);




    //初始化model
    //goods_record
    model_goodsrecord = new goods_record_model();
    model_goodsrecord->setList_goodsrecord(data_goodsrecord);
    ui->tableView_goodrecord->setModel(model_goodsrecord);


    //goods
    model_goods = new goods_model();
    model_goods->setList_goods(data_goods);
    ui->tableView_goods->setModel(model_goods);

    connect(ui->tableView_goods, QTableView::doubleClicked,        //为借物输入物品及余量
            this, borrow_when_double_clicked);

}

goods_record_show::~goods_record_show()
{
    //保存当前数据
    //goods_record
    write_container_to_file(*data_goodsrecord, goodsrecord_file_path);
    write_container_to_file(*data_past_goodsrecord, goodsrecord_past_file_path);


    //goods
    write_container_to_file(*data_goods, goods_file_path);


    delete ui;
    delete model_goodsrecord;
    delete data_goodsrecord;
    delete data_past_goodsrecord;
    delete model_goods;
    delete data_goods;
}

void goods_record_show::borrow_when_double_clicked(QModelIndex index)    //为借物对话框输入物品名及余量
{
    int row = index.row();
    goods *pGoods = &(data_goods->operator [](row));
    goodsrecord_add *goodsrecord_add_dialog = new goodsrecord_add(this);
    goodsrecord_add_dialog->edit_line(pGoods->goodsname, QString("%1").arg(pGoods->nownumber));

    connect(goodsrecord_add_dialog, goodsrecord_add::send_MSG_goodsrecord,
            this, add_new_record_of_borrow);

    goodsrecord_add_dialog->exec();
}




void goods_record_show::on_pushButton_addgoods_clicked()               //添加物品
{
    Dialog_addgoods *addgoods_dialog = new Dialog_addgoods(this);
    connect(addgoods_dialog, Dialog_addgoods::send_MSG_of_goods,
            this->model_goods, goods_model::add_new_goods);
    addgoods_dialog->exec();
}

void goods_record_show::on_pushButton_2_deletegoods_clicked()         //删除物品
{
    if(ui->tableView_goods->model()->rowCount() == 0)
    {
        QMessageBox::warning(this, tr(" "), tr("没有可删除的物品"));
        return;
    }
    int goodsrow_tobe_removed = ui->tableView_goods->currentIndex().row();
    int reply = QMessageBox::question(this, tr("询问"), tr("确定删除该物品？"),
                                      QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        data_goods->removeAt(goodsrow_tobe_removed);
        emit ui->tableView_goods->model()->layoutChanged();
    }
    else
        return;

}




void goods_record_show::on_pushButton_back_clicked()          //确认归还
{
   if(ui->tableView_goodrecord->model()->rowCount() == 0)
   {
       QMessageBox::warning(this, tr("警告"), tr("没有借出记录"));
       return;
   }
   int row_tobe_back = ui->tableView_goodrecord->currentIndex().row();
   int reply = QMessageBox::question(this, tr("询问"), tr("确认已归还？"),
                                      QMessageBox::Yes | QMessageBox::No);
   if(reply == QMessageBox::Yes)
   {
       data_past_goodsrecord->prepend(data_goodsrecord->at(row_tobe_back));
       data_goodsrecord->removeAt(row_tobe_back);
       emit ui->tableView_goodrecord->model()->layoutChanged();

   }
}


//查看出借物品的历史记录
void goods_record_show::on_pushButton_scan_goodshistory_clicked()
{
    QListWidget *listWidget_back_goodsrecord = new QListWidget();

    QListIterator<goods_record> bgr(*data_past_goodsrecord);
    while(bgr.hasNext())
    {
        const goods_record *gr = &(bgr.next());
        QString s = QString("%1").arg(gr->goodsname) + "  " + QString("%1").arg(gr->manname)
                +"  " + QString("%1").arg(gr->phonenumber) + "  " + QString("%1").arg(gr->borrowdate.toString("yyyy-MM-dd"))
                +"  " + QString("%1").arg(gr->backdate.toString("yyyy-MM-dd"));
        listWidget_back_goodsrecord->addItem(new QListWidgetItem(s));
    }

    QHBoxLayout *back_layout = new QHBoxLayout;
    back_layout->addWidget(listWidget_back_goodsrecord);

    QDialog *back_dialog = new QDialog(this);
    back_dialog->setWindowTitle("归还记录");
    back_dialog->setLayout(back_layout);
    back_dialog->show();
}

void goods_record_show::add_new_record_of_borrow(goods_record new_record)    //添加物品借出记录
{
    int index = ui->tableView_goods->currentIndex().row();
    //记录添加
    data_goodsrecord->prepend(new_record);

    //物品数量修改
    goods* pGood = &(data_goods->operator [](index));
    pGood->nownumber -= new_record.usenumber;

    emit model_goods->layoutChanged();
    emit model_goodsrecord->layoutChanged();
}
