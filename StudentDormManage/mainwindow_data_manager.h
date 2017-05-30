#ifndef MAINWINDOW_DATA_MANAGER_H
#define MAINWINDOW_DATA_MANAGER_H

#include <QMainWindow>

namespace Ui {
class MainWindow_data_manager;
}

class MainWindow_data_manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_data_manager(QWidget *parent = 0);
    ~MainWindow_data_manager();

private:
    Ui::MainWindow_data_manager *ui;
};

#endif // MAINWINDOW_DATA_MANAGER_H
