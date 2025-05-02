#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(" Compresso ");
    setWindowIcon(QIcon());
    ui->cProgressbar->hide();
    ui->stackedWidget->setCurrentIndex(0);
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
    QString path=QFileDialog::getOpenFileName(this,"Select file for Deompression","","All Files(*.*)");
    ui->filePathbox_2->setText(path);
}


void MainWindow::on_fileBtn_clicked()
{
    QString path=QFileDialog::getExistingDirectory(this,"Select folder to compress","",QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
        ui->filePathbox->setText(path);
}


void MainWindow::on_CompressFileBtn_clicked()
{
    try{
        string path=ui->filePathbox->text().toStdString();
        if(path==""){
            throw runtime_error("Kindly select a valid folder for compression");
        }
        else{
            Compressor c(path);
            c.compressFolder();
            QMessageBox::information(this,"success","compression done successfully");
        }
    }
    catch(const exception&e){
        QMessageBox::critical(this,"An error occured during compression",e.what());
    }

}

