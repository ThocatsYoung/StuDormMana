#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QValidator>
#include <QMap>
#include "dormlistmodel.h"
#include "studentlistmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void set_listview_dorm_model(DormListModel *model);
    void set_tableview_students_model(StudentListModel *students);

    void lianjie_students_model_and_listview_dorm(StudentListModel *m);

    void set_m_map_find_by_student_id(QMap<QString, student*> *map);
    void set_m_list_of_dorm(QList<dorm> *dorms);
    void add_widget_to_tabwidget(QWidget* w);

signals:
    void send_message_for_dorm_find(QString str);


private slots:
    void on_SwitchPushButton_clicked();

    void on_pushButton_to_dorm_clicked();

    void on_pushButton_find_by_stuid_clicked();

public slots:
    void find_dorm_in_listview_dorm(QString dorm_number);

private:
    Ui::MainWindow *ui;
    QList<dorm> *m_list_of_dorm;
    QMap<QString, student*> *m_map_find_by_student_id;
};

#endif // MAINWINDOW_H
