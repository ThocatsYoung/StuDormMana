#include "dialog_user_show.h"
#include "ui_dialog_user_show.h"

Dialog_user_show::Dialog_user_show(int type, QMap<QString, QString> *point_to_map,
                                   QWidget *parent) :
      edit_type(type), point_to_map_dorm_manager(point_to_map),
      QDialog(parent),
      ui(new Ui::Dialog_user_show)
  {
      ui->setupUi(this);


      //载入宿舍管理员数据
      QMapIterator<QString, QString> i(*point_to_map_dorm_manager);
      while(i.hasNext())
      {
          ui->listWidget_user->addItem(i.next().key());
      }

      //设置listWidget选取模式
      ui->listWidget_user->setSelectionBehavior (QAbstractItemView::SelectRows);
      ui->listWidget_user->setSelectionMode ( QAbstractItemView::SingleSelection);
      ui->listWidget_user->setEditTriggers (QAbstractItemView::NoEditTriggers);

      if (edit_type == 0){
          for_load();
      }else{
          for_add_and_delete();
      }
  }

Dialog_user_show::~Dialog_user_show()
{
    delete ui;
}



void Dialog_user_show::for_load()
{
    this->setWindowTitle("载入数据");
    ui->pushButton_add_user->hide();
    ui->pushButton_delete_data->hide();
    ui->pushButton_load_data->show();
}

void Dialog_user_show::for_add_and_delete()
{
    this->setWindowTitle("帐户管理");
    ui->pushButton_add_user->show();
    ui->pushButton_delete_data->show();
    ui->pushButton_load_data->hide();
}

void Dialog_user_show::add_user(QString user, QString mima)
{
    if (point_to_map_dorm_manager->contains(user)){
        warning_message_box("该用户已存在！");
        return;
    }
    point_to_map_dorm_manager->insert(user, mima);  //数据结构添加
    write_container_to_file(*point_to_map_dorm_manager, path_of_dorm_manager);  //写入文件
    create_dir_if_no_exist(user);   //创建文件夹
    ui->listWidget_user->addItem(user);
}

void Dialog_user_show::on_pushButton_add_user_clicked()
{
    Dialog_user_info *dialog = new Dialog_user_info(0, this);
    connect(dialog, Dialog_user_info::new_user,
            this, add_user);
    dialog->exec();
}

void Dialog_user_show::on_pushButton_delete_data_clicked()
{
    int index = ui->listWidget_user->currentRow();
    if (index < 0 || index > point_to_map_dorm_manager->count()){
        warning_message_box("未选中用户");
        return;
    }
    int reply = QMessageBox::question(this,tr("询问"),tr("用户数据将一并删除，\n仍确定删除该用户？"),
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        QListWidgetItem * item = ui->listWidget_user->takeItem(index);
        QString user = item->text();
        delete item;
        point_to_map_dorm_manager->remove(user);    //map中删除
        write_container_to_file(*point_to_map_dorm_manager, path_of_dorm_manager);  //写入文件
        delete_dir_if_exist(user);  //删除文件夹

    }else{
        return;
    }
}

void Dialog_user_show::on_pushButton_load_data_clicked()
{
    int index = ui->listWidget_user->currentRow();
    if (index < 0 || index > point_to_map_dorm_manager->count()){
        warning_message_box("未选中用户");
        return;
    }

    QString user = ui->listWidget_user->currentItem()->text();

    int reply = QMessageBox::question(this,tr("询问"),tr("当前已有数据将会保存，确定载入该用户数据？"),
                          QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes){
        emit send_building_info(user);
        this->accept();
    }else{
        return;
    }
}

void Dialog_user_show::on_pushButton_quit_clicked()
{
    this->close();
}
