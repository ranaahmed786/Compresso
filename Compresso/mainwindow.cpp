#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include<QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(" Compresso ");
    setWindowIcon(QIcon());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_compressbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->CompTab);
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->homeTab);
}


void MainWindow::on_decompressbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->DecompTab);
}


void MainWindow::on_homeBtn_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->homeTab);
}


void MainWindow::on_homeBtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->homeTab);
}


void MainWindow::on_fileBtn_2_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"Select file for Compression","","All Files(*.*)");
    ui->filePathbox_2->setText(path);
}


void MainWindow::on_fileBtn_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"Select file for Compression","","All Files(*.*)");
    ui->filePathbox->setText(path);
}

