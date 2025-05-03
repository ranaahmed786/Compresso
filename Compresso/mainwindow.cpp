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

    // Connect compression watcher finished signal
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

void MainWindow::on_fileBtn_2_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "Select file for Decompression", "", "All Files(*.*)");
    ui->filePathbox_2->setText(path);
}

void MainWindow::on_fileBtn_clicked() {
    QString path = QFileDialog::getExistingDirectory(this, "Select folder to compress", "",
                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->filePathbox->setText(path);
}

void MainWindow::on_CompressFileBtn_clicked() {
    try {
        QString qPath = ui->filePathbox->text();
        if (qPath.isEmpty()) {
            throw std::runtime_error("Kindly select a valid folder for compression");
        }

        // Show progress bar and reset
        ui->CompressFileBtn->hide();
        ui->progressBar->show();
        ui->progressBar->setValue(0);

        // Prepare compressor
        currentCompressor = new Compressor(qPath.toStdString());

        // Connect progress signal
        connect(currentCompressor, &Compressor::progressUpdated,
                this, &MainWindow::updateProgress, Qt::QueuedConnection);

        // Run in background
        compressionWatcher.setFuture(QtConcurrent::run([this]() {
            currentCompressor->compressFolder();
        }));

    } catch (const std::exception &e) {
        QMessageBox::critical(this, "An error occurred during compression", e.what());
        ui->progressBar->hide();
    }
}
QString MainWindow::formatSize(double bytes) {
    if (bytes < 1.0) { // Less than 1 MB
        double sizeKB = bytes * 1024.0;
        return QString::number(sizeKB, 'f', 2) + " KBs";
    }
    return QString::number(bytes, 'f', 2) + " MBs";
}

// Modified compression finished handler
void MainWindow::compressionFinished() {
    if (!currentCompressor) return;

    // Hide progress bar
    ui->progressBar->hide();
    ui->CompressFileBtn->show();
    // Update stats
    Compressor &c = *currentCompressor;
    lastCompressedPath = QString::fromStdString(c.compressedFolder.string());

    // Update dashboard with proper size formatting
        // Convert sizes to MB first
        double sizeOMB = static_cast<double>(c.originalFSize) / (1024.0 * 1024.0);
        double sizeCMB = static_cast<double>(c.compressedFSize) / (1024.0 * 1024.0);

        // Original Size (auto-format)
        ui->orgFileSizeD->setText(formatSize(sizeOMB));

        // Compressed Size (auto-format)
        ui->cmpFileSizeD->setText(formatSize(sizeCMB));

        // Other metrics
        ui->filesProcessed->setText(QString::number(c.FilesProcessed));

        // Handle division by zero for ratio calculation
        double ratio = (sizeOMB > 0) ? (1 - (sizeCMB / sizeOMB)) * 100 : 0.0;
        ui->cmpRatioD->setText(QString::number(ratio, 'f', 1) + " %");

        // Time and space saved
        ui->timeTakenD->setText(QString::number(static_cast<double>(c.TimeTaken) / 1000.0, 'f', 2) + " s");
        ui->spaceSavedD->setText(formatSize(sizeOMB - sizeCMB));
    // Show success message and switch to stats page
    QMessageBox::information(this, "Success", "Compression done successfully!");
    ui->stackedWidget->setCurrentWidget(ui->CompStatsTab);

    delete currentCompressor;
    currentCompressor = nullptr;
}
void MainWindow::updateProgress(int value)
{
    ui->progressBar->setValue(value);
    QCoreApplication::processEvents(); // Optional: Keeps UI responsive
}

void MainWindow::on_homeBtnS_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->homeTab);
}

void MainWindow::on_showInFolderBtn_clicked()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(lastCompressedPath));
}

