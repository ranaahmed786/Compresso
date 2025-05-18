// MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "compressor.h"
#include "decompressor.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QDesktopServices>
#include <QUrl>
#include <QtConcurrent>
#include <QFutureWatcher>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_compressbtn_clicked();
    void on_pushButton_9_clicked();
    void on_decompressbtn_clicked();
    void on_homeBtn_2_clicked();
    void on_homeBtn_clicked();
    void on_folderBtn_2_clicked();
    void on_folderBtn_clicked();
    void on_CompressFileBtn_clicked();
    void on_homeBtnS_clicked();
    void updateCmpProgress(int value);
    void updateDecmpProgress(int value);
    QString formatSize(double bytes);
    void compressionFinished();
    void decompressionFinished();
    void on_showInFolderBtn_clicked();
    void on_DecompressFileBtn_clicked();

private:
    Ui::MainWindow *ui;
    QString lastCompressedPath;
    QString lastDecompressedPath;
    //objects for threading and watching of compression;
    QFutureWatcher<void> compressionWatcher;
    Compressor *currentCompressor = nullptr;
    //objects for threding and watching of decompression
    QFutureWatcher<void> decompressionWatcher;
    Decompressor *currentDecompressor =nullptr;


};

#endif // MAINWINDOW_H
