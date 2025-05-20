#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Compresso");
    ui->stackedWidget->setCurrentIndex(0);
    ui->progressBar->hide();
    ui->dCompressbar->hide();


    connect(&compressionWatcher, &QFutureWatcher<void>::finished,
            this, &MainWindow::compressionFinished);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_compressbtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->CompTab);
}

void MainWindow::on_pushButton_9_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->homeTab);
}

void MainWindow::on_decompressbtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->DecompTab);
}

void MainWindow::on_homeBtn_2_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->homeTab);
}

void MainWindow::on_homeBtn_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->homeTab);
}

void MainWindow::on_folderBtn_2_clicked() {
    QString path = QFileDialog::getExistingDirectory(this, "Select folder for Decompression", "",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->filePathbox_2->setText(path);
}

void MainWindow::on_folderBtn_clicked() {
    QString path = QFileDialog::getExistingDirectory(this, "Select folder to compress", "",
                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->filePathbox->setText(path);
}
QString MainWindow::formatSize(double bytes) {
    if (bytes < 1.0) {
        double sizeKB = bytes * 1024.0;
        return QString::number(sizeKB, 'f', 2) + " KBs";
    }
    return QString::number(bytes, 'f', 2) + " MBs";
}

void MainWindow::on_CompressFileBtn_clicked() {
    try {
        QString qPath = ui->filePathbox->text();
        if (qPath.isEmpty()) {
            throw std::runtime_error("Kindly select a valid folder for compression");
        }


        ui->CompressFileBtn->hide();
        ui->progressBar->show();
        ui->progressBar->setValue(0);


        currentCompressor = new Compressor(qPath.toStdString());


        connect(currentCompressor, &Compressor::progressUpdated,this, &MainWindow::updateCmpProgress, Qt::QueuedConnection);

        connect(&compressionWatcher,&QFutureWatcher<void>::finished,this,&MainWindow::compressionFinished);


        compressionWatcher.setFuture(QtConcurrent::run([this]() {
            try {
                currentCompressor->compressFolder();
            } catch (const std::exception &e) {
                QMetaObject::invokeMethod(this, [=]() {
                    handleCompressionFailure(e.what());
                }, Qt::QueuedConnection);
            }
        }));

    } catch (const std::exception &e) {
        QMessageBox::critical(this, "An error occurred during compression", e.what());
        ui->progressBar->hide();
    }
}

void MainWindow::compressionFinished() {
    if (!currentCompressor) return;


    ui->progressBar->hide();
    ui->CompressFileBtn->show();
    // Update stats
    Compressor &c = *currentCompressor;
    lastCompressedPath = QString::fromStdString(c.compressedFolder.string());


        double sizeOMB = static_cast<double>(c.originalFSize) / (1024.0 * 1024.0);
        double sizeCMB = static_cast<double>(c.compressedFSize) / (1024.0 * 1024.0);


        ui->orgFileSizeD->setText(formatSize(sizeOMB));


        ui->cmpFileSizeD->setText(formatSize(sizeCMB));


        ui->filesProcessed->setText(QString::number(c.FilesProcessed));


        double ratio = (sizeOMB > 0) ? (1 - (sizeCMB / sizeOMB)) * 100 : 0.0;
        ui->cmpRatioD->setText(QString::number(ratio, 'f', 1) + " %");

        ui->timeTakenD->setText(QString::number(static_cast<double>(c.TimeTaken) / 1000.0, 'f', 2) + " s");
        ui->spaceSavedD->setText(formatSize(sizeOMB - sizeCMB));

    QMessageBox::information(this, "Success", "Compression done successfully!");
    ui->stackedWidget->setCurrentWidget(ui->StatsTab);

    delete currentCompressor;
    currentCompressor = nullptr;
}
void MainWindow::updateCmpProgress(int value)
{
    ui->progressBar->setValue(value);
    QCoreApplication::processEvents();
}

void MainWindow::updateDecmpProgress(int value){
    ui->dCompressbar->setValue(value);
    QCoreApplication::processEvents();
}
void MainWindow::on_homeBtnS_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->homeTab);
}

void MainWindow::on_showInFolderBtn_clicked()
{   if(ui->StatsHeader->text() == "Compression Summary")
        QDesktopServices::openUrl(QUrl::fromLocalFile(lastCompressedPath));
    else
        QDesktopServices::openUrl(QUrl::fromLocalFile(lastDecompressedPath));
}


void MainWindow::on_DecompressFileBtn_clicked()
{
    try {
        QString Path = ui->filePathbox_2->text();
        string folderPath =Path.toStdString();
        const string suffix = "(Compressed)";
        if (Path.isEmpty()) {
            throw runtime_error("Kindly select a valid folder for decompression");
        }
        else if(folderPath.length() < suffix.length() || folderPath.substr(folderPath.length() - suffix.length()) != suffix){
            throw std::runtime_error("Kindly select a folder compressed by Compresso."+Path.toStdString()+" is not a compresso compressed folder.");
        }
        else{
            // Show progress bar and reset
            ui->DecompressFileBtn->hide();
            ui->dCompressbar->show();
            ui->dCompressbar->setValue(0);

            // Prepare decompressor
            currentDecompressor = new Decompressor(Path.toStdString());

            // Connect progress signal
            connect(currentDecompressor, &Decompressor::progressUpdated, this, &MainWindow::updateDecmpProgress, Qt::QueuedConnection);

            connect(&decompressionWatcher,&QFutureWatcher<void>::finished,this,&MainWindow::decompressionFinished);

            // Run in background
            decompressionWatcher.setFuture(QtConcurrent::run([this]() {
                try {
                    currentDecompressor->decompressFolder();
                } catch (const std::exception &e) {
                    QMetaObject::invokeMethod(this, [=]() {
                        handleDecompressionFailure(e.what());
                    }, Qt::QueuedConnection);
                }
            }));
        }
    } catch (const std::exception &e) {
        QMessageBox::critical(this, "An error occurred during decompression", e.what());
        ui->progressBar->hide();
    }
}
void MainWindow::decompressionFinished() {
    if (!currentDecompressor) return;

    // Hide progress bar
    ui->dCompressbar->hide();
    ui->DecompressFileBtn->show();
    ui->StatsHeader->setText("Decompression Summary");
    // Update stats
    Decompressor &d = *currentDecompressor;
    lastDecompressedPath = QString::fromStdString(d.decompressedFolderP.string());

    // Update dashboard with proper size formatting
    // Convert sizes to MB first
    double sizeOMB = static_cast<double>(d.originalFSize) / (1024.0 * 1024.0);
    double sizeCMB = static_cast<double>(d.compressedFSize) / (1024.0 * 1024.0);

    // Original Size (auto-format)
    ui->orgFileSizeD->setText(formatSize(sizeOMB));

    // Compressed Size (auto-format)
    ui->cmpFileSizeD->setText(formatSize(sizeCMB));


    ui->filesProcessed->setText(QString::number(d.FilesProcessed));

    // Handle division by zero for ratio calculation
    double ratio = (sizeOMB > 0) ? (1 - (sizeCMB / sizeOMB)) * 100 : 0.0;
    ui->cmpRatioD->setText(QString::number(ratio, 'f', 1) + " %");

    // Time and space saved
    ui->timeTakenD->setText(QString::number(static_cast<double>(d.TimeTaken) / 1000.0, 'f', 2) + " s");
    ui->spaceSavedD->setText(formatSize(sizeOMB - sizeCMB));
    ui->spaceLabel->setText("Space Released");
    // Show success message and switch to stats page
    QMessageBox::information(this, "Success", "Decompression done successfully!");
    ui->stackedWidget->setCurrentWidget(ui->StatsTab);

    delete currentDecompressor;
    currentDecompressor = nullptr;
}
void MainWindow::handleDecompressionFailure(const QString &error){
    QMetaObject::invokeMethod(this, [=]() {
        QMessageBox::critical(this, "Decompression Error", error);
        ui->dCompressbar->hide();
        ui->DecompressFileBtn->show();
        ui->stackedWidget->setCurrentWidget(ui->homeTab);
        delete currentDecompressor;
        currentDecompressor = nullptr;
    }, Qt::QueuedConnection);
}
void MainWindow::handleCompressionFailure(const QString &error) {
    QMetaObject::invokeMethod(this, [=]() {
        QMessageBox::critical(this, "Compression Error", error);
        ui->progressBar->hide();
        ui->CompressFileBtn->show();
        ui->stackedWidget->setCurrentWidget(ui->homeTab);
        delete currentCompressor;
        currentCompressor = nullptr;
    }, Qt::QueuedConnection);
}
