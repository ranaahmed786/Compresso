#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H
#include"infilehandler.h"
#include"outfilehandler.h"
#include<QObject>
#include<filesystem>
#include<QElapsedTimer>
using namespace std;
namespace fs =std::filesystem;

class Decompressor:public QObject
{
    Q_OBJECT
    friend class MainWindow;
    qint64 TimeTaken;
    int FilesProcessed;
    InFileHandler inHandler;
    OutFileHandler outHandler;
    fs::path compressedFolderP;
    fs::path decompressedFolderP;
    size_t originalFSize;
    size_t compressedFSize;
    void decompressFile(const string&cmpFilePath,const string&orgpFilePath);
    bool isCmpFile(const fs::path &filepath);
public:
    Decompressor(const string&cmpFolderPath);
    void  decompressFolder();
    bool isCompressedFolder();
signals:
    void progressUpdated(int value);
};

#endif // DECOMPRESSOR_H
