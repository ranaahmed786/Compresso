// MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "compressor.h"
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
    void on_fileBtn_2_clicked();
    void on_fileBtn_clicked();
    void on_CompressFileBtn_clicked();
    void on_homeBtnS_clicked();
    // NEW: progress update slot
    void updateProgress(int value);
    QString formatSize(double bytes);
    // NEW: completion slot
    void compressionFinished();
    void on_showInFolderBtn_clicked();

private:
    Ui::MainWindow *ui;
    QString lastCompressedPath;

    // NEW: objects for threading and watching
    QFutureWatcher<void> compressionWatcher;
    Compressor *currentCompressor = nullptr;
};

#endif // MAINWINDOW_H
