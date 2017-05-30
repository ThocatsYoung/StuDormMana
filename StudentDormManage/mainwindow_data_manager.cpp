#include "mainwindow_data_manager.h"
#include "ui_mainwindow_data_manager.h"

MainWindow_data_manager::MainWindow_data_manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_data_manager)
{
    ui->setupUi(this);
}

MainWindow_data_manager::~MainWindow_data_manager()
{
    delete ui;
}
