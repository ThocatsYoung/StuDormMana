#include "mainwindow_data_manager.h"
#include "ui_mainwindow_data_manager.h"

MainWindow_data_manager::MainWindow_data_manager(QString user,
                                                 QWidget *parent) :
    user_name(user),
    model_dorm(NULL), model_student(NULL), QMainWindow(parent),
    ui(new Ui::MainWindow_data_manager)
{
    ui->setupUi(this);

    init_user_data();

    //设置model
    model_dorm = new DormListModel(&m_list_of_dorm);
    model_student = new StudentListModel(0);

    ui->listView_dorm->setModel(model_dorm);
    ui->tableView_student->setModel(model_student);

    //宿舍被点击，改变宿舍信息label显示 及 学生视图对应信息
    connect(ui->listView_dorm, &QListView::clicked,
            this, &MainWindow_data_manager::change_dorm_information);
    connect(this, MainWindow_data_manager::send_point_of_student_list_to_model,
            model_student, StudentListModel::slot_to_set_student_list);

    //宿舍被点击-学生视图取消选定
    connect(ui->listView_dorm, &QListView::clicked,
            ui->tableView_student, &QTableView::clearSelection);

    //以宿舍号查找宿舍
    connect(this, send_message_for_dorm_find,
            this, find_dorm_in_listview_dorm);

    //动作-槽 修改密码 帐户管理
    connect(ui->action_edit_mima, QAction::triggered,
            this, solt_for_action_edit_mima);
    connect(ui->action_add_remove_users, QAction::triggered,
            this, slot_for_action_manage_users);

    //设置查询编辑框只可输入数字
    QRegExp regx1("[1-9][0-9]{0,2}");   //第一位不可为0，限制3位数
    QValidator *of_edit_dorm = new QRegExpValidator(regx1, ui->lineEdit_dorm_number );
    ui->lineEdit_dorm_number->setValidator(of_edit_dorm);

    QRegExp regx2("[1-9][0-9]{0,11}");   //第一位不可为0，限制12位
    QValidator *of_edit_student_id = new QRegExpValidator(regx2, ui->lineEdit_stuid );
    ui->lineEdit_stuid->setValidator(of_edit_student_id);


}

MainWindow_data_manager::~MainWindow_data_manager()
{

    if (model_dorm != NULL){
        delete model_dorm;
        model_dorm = NULL;
    }
    if (model_student != NULL){
        delete model_student;
        model_student = NULL;
    }

    delete ui;
}


void MainWindow_data_manager::setModel_dorm(DormListModel *value)
{
    model_dorm = value;
}

void MainWindow_data_manager::setModel_student(StudentListModel *value)
{
    model_student = value;
}

void MainWindow_data_manager::init_user_data()
{
    //初始化登录人员数据(文件读写)
    read_file_to_container(path_of_dorm_manager, map_dorm_manager);
    read_file_to_container(path_of_data_manager, map_data_manager);

}

void MainWindow_data_manager::init_list_of_dorm()
{
    m_list_of_dorm.clear();
    if (dorm_building_name.isEmpty())
        return;

    read_file_to_container(add_user_and_path(dorm_building_name, path_of_data_dorm),
                           m_list_of_dorm);

    ui->tableView_student->clearSelection();
    ui->listView_dorm->clearSelection();
    emit ui->listView_dorm->model()->layoutChanged();

}

void MainWindow_data_manager::init_map_find_by_student_id()
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

void MainWindow_data_manager::init_set_of_dorm_number()
{
    set_of_dorm_number.clear();
    for (QListIterator<dorm> i(m_list_of_dorm); i.hasNext();)
    {
        set_of_dorm_number.insert(i.next().GetDormNumber());
    }
}

void MainWindow_data_manager::save_user_data_to_file()
{
    write_container_to_file(map_data_manager, path_of_data_dorm);
    write_container_to_file(map_dorm_manager, path_of_dorm_manager);
}

void MainWindow_data_manager::save_dorm_data_to_file()
{
    write_container_to_file (m_list_of_dorm,
                             add_user_and_path(dorm_building_name, path_of_data_dorm));
}

void MainWindow_data_manager::add_new_dorm_to_list(dorm value)
{
    if (set_of_dorm_number.contains(value.GetDormNumber())){
        warning_message_box("该宿舍已存在！");
        return;
    }
    int i = 0;
    for(; i != m_list_of_dorm.count(); ++i){
        if (value < m_list_of_dorm.at(i))
        {
            break;
        }
    }
    if (i == m_list_of_dorm.count()){
        m_list_of_dorm.append(value);
    }else{
        m_list_of_dorm.insert(i, value);
    }
    emit model_dorm->layoutChanged();

    set_of_dorm_number.insert(value.GetDormNumber());

    //跳转到新添加的宿舍
    QModelIndex q = model_dorm->index(i, 0);
    ui->listView_dorm->setCurrentIndex(q);

    emit ui->listView_dorm->clicked(q);
}

void MainWindow_data_manager::find_dorm_in_listview_dorm(QString dorm_number)
{
    quint16 dorm_number_value = dorm_number.toInt();
    if (!(set_of_dorm_number.contains(dorm_number_value)))
    {
        warning_message_box("你所查找的宿舍不存在！");
        return;
    }

    //寻找匹配的宿舍
    QModelIndexList indexList = ui->listView_dorm->model()->match(
                ui->listView_dorm->model()->index(0, 0),
                    Qt::DisplayRole, dorm_number);

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

void MainWindow_data_manager::add_student_to_current_dorm(student new_student)
{
    //初始化
    int index = ui->listView_dorm->currentIndex().row();
    dorm *pDorm = &(m_list_of_dorm.operator [](index));

    if (m_map_find_by_student_id.contains(new_student.GetStudentId()))
    {
        warning_message_box("不可添加该学生记录，\n学号已存在！");
        return;
    }

    //修改数据
    pDorm->add(new_student);

    //查询map修改
    student *point_for_find_map = &(pDorm->StuDorm.last());
    m_map_find_by_student_id.insert(point_for_find_map->GetStudentId(),
                                     point_for_find_map);
    //view改变
    emit ui->tableView_student->model()->layoutChanged();
}


void MainWindow_data_manager::on_pushButton_find_by_stuid_clicked()
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
    }
    else
    {
        //展示学生信息
        student *stu = (m_map_find_by_student_id)[student_id];
        QMessageBox::information(this, tr("学生信息"),
                                 stu->toString_detail());
    }
    ui->lineEdit_stuid->clear();    //清空文本
}

void MainWindow_data_manager::on_pushButton_to_dorm_clicked()
{
    QString dorm_number = ui->lineEdit_dorm_number->text();
    if(dorm_number.isEmpty())
    {
        warning_message_box("查询宿舍号不可为空！");
        return;
    }
    emit send_message_for_dorm_find(dorm_number);
}


void MainWindow_data_manager::on_pushButton_add_dorm_clicked()
{
    Dialog_Dorm_Edit *dialog = new Dialog_Dorm_Edit (0, 0, this);
    connect(dialog, Dialog_Dorm_Edit::send_new_dorm_info,
            this, add_new_dorm_to_list);
    int reply = dialog->exec();
    if (reply != QDialog::Accepted)
    {
        return;
    }else{
        emit ui->listView_dorm->clicked(ui->listView_dorm->currentIndex());
    }
}

void MainWindow_data_manager::on_pushButton_show_student_clicked()
{
    int index = ui->tableView_student->currentIndex().row();
    int count = ui->tableView_student->model()->rowCount();

    if (count == 0){
        warning_message_box("该宿舍无住宿学生");
        return;
    }
    if (index >= 0 && index <= (count-1)){
        student *p = model_student->get_student_info_at(index);
        QMessageBox::information(this, tr("学生详细信息"), p->toString_detail());
    }else{
        warning_message_box("未选取学生");
        return;
    }
}

void MainWindow_data_manager::change_dorm_information(QModelIndex sended_index)
{
    int index = sended_index.row();
    int count = m_list_of_dorm.count();

    if (index < 0 || index >= count)
        return;

    dorm* pDorm = &(m_list_of_dorm.operator [](index));
    QList<student> *p = &(pDorm->StuDorm);
    emit this->send_point_of_student_list_to_model(p);

    QStringList sl_of_label_text = pDorm->toStringList();

    ui->label_info_max->setText(sl_of_label_text.at(0));
    ui->label_info_now->setText(sl_of_label_text.at(1));
    ui->label_info_waterfee->setText(sl_of_label_text.at(2));
    ui->label_info_elecfee->setText(sl_of_label_text.at(3));

    return;
}

void MainWindow_data_manager::on_pushButton_edit_dorm_clicked()
{
    int current_row = ui->listView_dorm->currentIndex().row();
    if (current_row >= m_list_of_dorm.count()
            || current_row < 0)
        return;

    dorm *d = &(m_list_of_dorm.operator [](current_row));
    Dialog_Dorm_Edit *dialog = new Dialog_Dorm_Edit (1, d, this);
    int reply = dialog->exec();
    if (reply != QDialog::Accepted)
        return;
    emit ui->listView_dorm->clicked(ui->listView_dorm->currentIndex());
}

void MainWindow_data_manager::on_pushButton_delete_dorm_clicked()
{
    if (m_list_of_dorm.count() == 0)
    {
        warning_message_box("无宿舍可删除");
        return;
    }
    int current_row = ui->listView_dorm->currentIndex().row();
    if (current_row < 0 || current_row >= m_list_of_dorm.count()){
        warning_message_box("未选中宿舍");
        return;
    }

    int reply = QMessageBox::question(this,tr("询问"),tr("确定删除该宿舍？"),
                          QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QList<student> *p = &(m_list_of_dorm.operator [](current_row).StuDorm);
        for(QListIterator<student> i(*p); i.hasNext();)
        {
            m_map_find_by_student_id.remove(i.next().GetStudentId());
            //清除查询map数据
        }

        m_list_of_dorm.removeAt(current_row);
        emit ui->listView_dorm->model()->layoutChanged();
        ui->listView_dorm->clearFocus();
        model_student->set_student_list(NULL);
    }else{
        return;
    }


}

void MainWindow_data_manager::on_pushButton_add_student_clicked()
{
    int index = ui->listView_dorm->currentIndex().row();
    if (index < 0 || index >= m_list_of_dorm.count())
    {
        QMessageBox::warning(this, tr("警告"), tr("未选取宿舍"));
        return;
    }
    dorm *pDorm = &(m_list_of_dorm.operator [](index));
    if (pDorm->StuDorm.count() >= pDorm->GetMaxNumber()){
        QMessageBox::warning(this, tr("警告"), tr("当前宿舍人数已满"));
        return;
    }

    student_information_edit_Dialog *dialog =
            new student_information_edit_Dialog(0, pDorm, 0, this);

    connect(dialog, student_information_edit_Dialog::send_student_info,
            this, add_student_to_current_dorm);

    dialog->exec();
}

void MainWindow_data_manager::on_pushButton_edit_student_clicked()
{
    int index_dorm = ui->listView_dorm->currentIndex().row();
    int index_student = ui->tableView_student->currentIndex().row();

    if (index_dorm < 0 || index_dorm >= m_list_of_dorm.count()){
        warning_message_box("未选取宿舍");
        return;
    }
    dorm *pDorm = &(m_list_of_dorm.operator [](index_dorm));

    if (index_student < 0 || index_student >= pDorm->StuDorm.count()){
        warning_message_box("未选取学生");
        return;
    }
    student *pStudent = &(pDorm->StuDorm.operator [](index_student));

    student_information_edit_Dialog *dialog =
            new student_information_edit_Dialog(1, pDorm, pStudent, this);

    dialog->exec();
}

void MainWindow_data_manager::on_pushButton_delete_student_clicked()
{
    int index_dorm = ui->listView_dorm->currentIndex().row();
    int index_student = ui->tableView_student->currentIndex().row();
    dorm *pDorm = &(m_list_of_dorm.operator [](index_dorm));
    student *pStudent = &(pDorm->StuDorm.operator [](index_student));

    if (index_dorm < 0 || index_dorm >= m_list_of_dorm.count()){
        warning_message_box("未选取宿舍");
        return;
    }
    if (index_student < 0 || index_student >= pDorm->StuDorm.count()){
        warning_message_box("未选取学生");
        return;
    }

    int reply = QMessageBox::question(this,tr("询问"),tr("确定移除该学生？"),
                          QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        m_map_find_by_student_id.remove(pStudent->GetStudentId());
        pDorm->goAway(index_student);
        emit ui->tableView_student->model()->layoutChanged();
    }
    return;
}

QString MainWindow_data_manager::getDorm_building_name() const
{
    return dorm_building_name;
}

void MainWindow_data_manager::solt_for_action_edit_mima()
{
    QString mima = map_data_manager.value(user_name);

#if DEBUG_TEST
    qDebug() << "sended mima";
    qDebug() << mima;
#endif

    Dialog_user_info *dialog = new Dialog_user_info(1, this, user_name, mima);
    connect(dialog, Dialog_user_info::changed_mima,
            this, edit_current_mima);
    dialog->exec();
}

void MainWindow_data_manager::slot_for_action_manage_users()
{
#if DEBUG_TEST
    qDebug() << "open users manage view";
#endif
    Dialog_user_show *dialog = new Dialog_user_show(1, &map_dorm_manager, this);
    dialog->exec();
    return;
}

void MainWindow_data_manager::edit_current_mima(QString mima)
{
    map_data_manager[user_name] = mima;
    write_container_to_file(map_data_manager, path_of_data_dorm);
}

void MainWindow_data_manager::setDorm_building_name(const QString &value)
{
    if (!dorm_building_name.isEmpty()){
        save_dorm_data_to_file();
    }

    dorm_building_name = value;

    //载入数据
    init_list_of_dorm();
    init_map_find_by_student_id();
    init_set_of_dorm_number();

    ui->label_building->setText(dorm_building_name);
}

void MainWindow_data_manager::closeEvent(QCloseEvent *event)
{
    switch( QMessageBox::information(this,tr("提示"),
                                     tr("确定退出学生宿舍管理系统？\n若退出，你当前的所有操作将会保存。"),
                                     tr("确定"), tr("取消"),0,1))
    {
    case 0:
        save_user_data_to_file();
        save_dorm_data_to_file();
        event->accept();
        break;
    case 1:
    default:
        event->ignore();
        break;
    }
    return;
}

void MainWindow_data_manager::on_commandLinkButton_clicked()
{
    Dialog_user_show *dialog = new Dialog_user_show(0, &map_dorm_manager, this);
    connect(dialog, Dialog_user_show::send_building_info,
            this, setDorm_building_name);
    dialog->exec();
}
