#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "my_model.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(mod);
    ui->tableView->setColumnWidth(0, 60);
    ui->tableView->setColumnWidth(1, 660);
    ui->tableView->setColumnWidth(2, 105);
    ui->tableView->setColumnWidth(3, 105);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->horizontalHeader()->setSortIndicatorShown(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->tableView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Add_title_clicked() { mod->insertRow(mod->Size()); }
