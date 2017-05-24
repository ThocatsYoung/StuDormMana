#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
