#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include"infilehandler.h"
#include "outfilehandler.h"
#include "huffmantree.h"
#include <vector>
#include <stdint.h>
#include<unordered_map>
#include<QElapsedTimer>
#include<filesystem>
#include<QObject>
using namespace std;
namespace fs = std::filesystem;
class Compressor:public QObject
{
    Q_OBJECT
    friend class MainWindow;
    qint64 TimeTaken;
    int FilesProcessed;
    InFileHandler inHandler;
    OutFileHandler outHandler;
    HuffmanTree tree;
    fs::path rootFolder;
    fs::path compressedFolder;
    size_t originalFSize;
    size_t compressedFSize;
    void compressFile(const string& filePath, const string& relativefilePath);
public:
    Compressor(const string& path);
    void compressFolder();
signals:
    void progressUpdated(int value);
};

#endif // COMPRESSOR_H
