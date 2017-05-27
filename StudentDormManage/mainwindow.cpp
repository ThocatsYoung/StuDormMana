#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connect
    connect(this, send_message_for_dorm_find,
            this, find_dorm_in_listview_dorm);

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
    m_list_of_dorm = NULL;
    m_map_find_by_student_id = NULL;
}

void MainWindow::set_listview_dorm_model(DormListModel *model)
{
    ui->listView_dorm->setModel(model);
}

void MainWindow::set_tableview_students_model(StudentListModel *students)
{
    ui->tableView_students->setModel(students);
}

void MainWindow::lianjie_students_model_and_listview_dorm(StudentListModel *m)
{
    connect(ui->listView_dorm, &QListView::clicked,
            m,StudentListModel::set_which_dorm);
}

void MainWindow::set_m_map_find_by_student_id(QMap<QString, student *> *map)
{
    m_map_find_by_student_id = map;
}

void MainWindow::set_m_list_of_dorm(QList<dorm> *dorms)
{
    m_list_of_dorm = dorms;
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
    QString dorm_number = ui->lineEdit_dorm_number->text();
    if(dorm_number.isEmpty())
        QMessageBox::warning(this, tr("警告"), tr("查询宿舍号不可为空！"));
    emit send_message_for_dorm_find(dorm_number);
}

void MainWindow::on_pushButton_find_by_stuid_clicked()
{
    QString student_id = ui->lineEdit_stuid->text();
    if(student_id.isEmpty())
        QMessageBox::warning(this, tr("警告"), tr("查询学生学号不可为空！"));
    if(!(m_map_find_by_student_id->contains(student_id)))
        QMessageBox::warning(this, tr("警告"), tr("查询学生学号不存在！"));
    else
    {
        student *stu = (*m_map_find_by_student_id)[student_id];

        QString student_info("姓名："+stu->GetName()+'\n'+
                             "学号："+stu->GetStudentId()+'\n'+
                             "宿舍号："+QString("%1").arg(stu->GetDormNumber())+'\n'+
                             "学院："+QString("%1").arg(stu->GetXueYuan())+'\n'+
                             "联系方式："+stu->GetContact()+'\n');
        QMessageBox::information(this, tr("学生信息"),student_info);
    }
}

void MainWindow::find_dorm_in_listview_dorm(QString dorm_number)
{
    //寻找匹配的宿舍
    QModelIndexList indexList = ui->listView_dorm->model()
            ->match(ui->listView_dorm->model()->index(0, 0), Qt::DisplayRole, dorm_number);

    //报错
    if(indexList.isEmpty())
    {
        QMessageBox::warning(this, tr("警告"), tr("你所查找的宿舍不存在！"));
        return;
    }

    //正常跳转
    QModelIndex selected_index(indexList.first());
    ui->listView_dorm->setCurrentIndex(selected_index);
    emit ui->listView_dorm->clicked(selected_index);
}
