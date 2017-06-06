#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QString user,
                       QWidget *parent) :
    user_name(user),
    model_dorm(NULL), model_student(NULL),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_user_data();
    init_tongzhi();

//初始化数据结构
    init_list_of_dorm();
    init_set_of_dorm_number();
    init_map_of_student_id();

    model_dorm = new DormListModel(&m_list_of_dorm);
    model_student = new StudentListModel(0);

    ui->listView_dorm->setModel(model_dorm);
    ui->tableView_students->setModel(model_student);

    //connect 在视图中查找指定宿舍
    connect(this, send_message_for_dorm_find, this, find_dorm_in_listview_dorm);

    //选中宿舍改变时改变学生视图对应信息
    connect(ui->listView_dorm, &QListView::clicked,
            this, &MainWindow::change_dorm_information);
    connect(this, MainWindow::send_point_of_student_list_to_model,
            model_student, StudentListModel::slot_to_set_student_list);

//设置界面


//主界面添加窗口
    //离校登记界面
    Formforoutschool *Form_outschool = new Formforoutschool(add_user_and_path(user_name, path::_of_outschool_record),
                                                            add_user_and_path(user_name,path::_of_outschool_record_past),
                                                            &m_map_find_by_student_id, this);
    this->add_widget_to_tabwidget(Form_outschool, "离校登记");

    //外访登记界面
    FormForOutsider *Form_outsider = new FormForOutsider(add_user_and_path(user_name, path::_of_wailairen_record),
                                                         add_user_and_path(user_name,path::_of_wailairen_record_past));
    this->add_widget_to_tabwidget(Form_outsider, "外访人员登记");

    //晚归登记界面
    Formforwangui *Form_wangui = new Formforwangui(add_user_and_path(user_name, path::_of_wangui_record),
                                                   add_user_and_path(user_name, path::_of_wangui_record_past),
                                                   &m_map_find_by_student_id);
    this->add_widget_to_tabwidget(Form_wangui, "晚归登记");

    //宿舍物品管理
    goods_record_show *Form_goods = new goods_record_show(add_user_and_path(user_name, path::_of_goodsrecord),
                                                          add_user_and_path(user_name, path::_of_goodsrecord_past),
                                                          add_user_and_path(user_name, path::_of_goods),
                                                          this);
    this->add_widget_to_tabwidget(Form_goods, "宿舍公用物品管理");

    //宿舍维修记录管理
    dorm_repair_show *Form_repair = new dorm_repair_show(add_user_and_path(user_name, path::_of_dorm_repair),
                                                         add_user_and_path(user_name, path::_of_dorm_repair_record),
                                                         this);
    this->add_widget_to_tabwidget(Form_repair, "宿舍维修");

    //宿舍违纪登记界面
    FormForRuleBreakRecord *Form_rulebreak = new FormForRuleBreakRecord
            (add_user_and_path(user_name, path::_of_rulebreak_record),
             add_user_and_path(user_name, path::_of_rulebreak_record_past),
             &set_of_dorm_number,this);
    this->add_widget_to_tabwidget(Form_rulebreak, "宿舍违纪记录");

//设置查询编辑框只可输入数字
    QRegExp regx1("[1-9][0-9]{0,2}");   //第一位不可为0，限制3位数
    QValidator *of_edit_dorm = new QRegExpValidator(regx1, ui->lineEdit_dorm_number );
    ui->lineEdit_dorm_number->setValidator(of_edit_dorm);
    QRegExp regx2("[1-9][0-9]{0,11}");   //第一位不可为0，限制12位
    QValidator *of_edit_student_id = new QRegExpValidator(regx2, ui->lineEdit_stuid );
    ui->lineEdit_stuid->setValidator(of_edit_student_id);

}

MainWindow::~MainWindow()
{
    delete ui;
    if (model_dorm != NULL){
        delete model_dorm;
        model_dorm = NULL;
    }
    if (model_student != NULL){
        delete model_student;
        model_student = NULL;
    }
}

void MainWindow::add_widget_to_tabwidget(QWidget *w ,QString title)
{
    ui->TabWidget_manage->addTab(w,title);
}

void MainWindow::init_tongzhi()
{
    QString s;
    read_file_to_container(path::_of_Tongzhi, s);
    ui->textEdit_TongZhi->setText(s);
    ui->textEdit_TongZhi->setReadOnly(true);
}

void MainWindow::init_user_data()
{
    read_file_to_container(path::_of_dorm_manager, map_dorm_manager);
}


void MainWindow::on_SwitchPushButton_clicked()
{
    quint16 nCount = ui->stackedWidget->count();
    quint16 nIndex = ui->stackedWidget->currentIndex();

    // 获取下一个需要显示的页面索引
    ++nIndex;

    // 当需要显示的页面索引大于等于总页面时，切换至首页
    if (nIndex >= nCount)
        nIndex = 0;

    ui->stackedWidget->setCurrentIndex(nIndex);
}


void MainWindow::on_pushButton_to_dorm_clicked()
{
    QString dorm_number_text = ui->lineEdit_dorm_number->text();
    if(dorm_number_text.isEmpty())
    {
        warning_message_box("查询宿舍号不可为空！");
        return;
    }else{
        if (!set_of_dorm_number.contains(dorm_number_text.toInt()))
        {
            warning_message_box("查询宿舍号不存在！");
            return;
        }
    }

    emit send_message_for_dorm_find(dorm_number_text);
}

void MainWindow::on_pushButton_find_by_stuid_clicked()
{
    QString student_id = ui->lineEdit_stuid->text();
    if(student_id.isEmpty())
    {
        warning_message_box("查询学生学号不可为空！");
        return;
    }

    if(!(m_map_find_by_student_id.contains(student_id)))
    {
        warning_message_box("查询学生学号不存在！");
        return;
    }else{
        //展示学生信息
        student *stu = (m_map_find_by_student_id)[student_id];
        QMessageBox::information(this, tr("学生信息"), stu->toString());
    }
    ui->lineEdit_stuid->clear();    //清空文本
}

void MainWindow::change_dorm_information()
{
    int index = ui->listView_dorm->currentIndex().row();
    int count = m_list_of_dorm.count();

    if (index < 0 || index > (count-1))
        return;

    QList<student> *p = &((m_list_of_dorm.operator [](index)).StuDorm);
    emit this->send_point_of_student_list_to_model(p);

    return;
}

void MainWindow::find_dorm_in_listview_dorm(QString dorm_number)
{
    //寻找匹配的宿舍
    QModelIndexList indexList = ui->listView_dorm->model()
            ->match(ui->listView_dorm->model()->index(0, 0), Qt::DisplayRole, dorm_number);

    //报错
    if(indexList.isEmpty())
    {
       warning_message_box("你所查找的宿舍不存在！");
        return;
    }

    //正常跳转
    QModelIndex selected_index(indexList.first());
    ui->listView_dorm->setCurrentIndex(selected_index);
    emit ui->listView_dorm->clicked(selected_index);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    switch( QMessageBox::information(this,tr("提示"),
                                     tr("确定退出学生宿舍管理系统？\n若退出，你当前的所有操作将会保存。"),
                                     tr("确定"), tr("取消"),0,1))
    {
    case 0:
        event->accept();
        break;
    case 1:
    default:
        event->ignore();
        break;
    }
}



void MainWindow::init_list_of_dorm()
{
    m_list_of_dorm.clear();
    if (user_name.isEmpty())
        return;
    read_file_to_container(add_user_and_path(user_name, path::_of_data_dorm),
                           m_list_of_dorm);
}

void MainWindow::init_set_of_dorm_number()
{
    set_of_dorm_number.clear();
    for(QListIterator<dorm> i(m_list_of_dorm);
            i.hasNext();){
            set_of_dorm_number.insert(i.next().GetDormNumber());
    }
}

void MainWindow::init_map_of_student_id()
{
    m_map_find_by_student_id.clear();
    for(QMutableListIterator<dorm> i(m_list_of_dorm); i.hasNext();)
    {
        QMutableListIterator<student> j(i.next().StuDorm);
        while(j.hasNext())
        {
            student *stu = &j.next();
            if(m_map_find_by_student_id.contains(stu->GetStudentId()))
                continue;
            m_map_find_by_student_id.insert(stu->GetStudentId(),stu);
        }
    }
}


