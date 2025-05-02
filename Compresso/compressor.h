#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include"infilehandler.h"
#include "outfilehandler.h"
#include "huffmantree.h"
#include <vector>
#include <stdint.h>
#include<unordered_map>
#include<filesystem>
using namespace std;
namespace fs = std::filesystem;
class Compressor
{
    InFileHandler inHandler;
    OutFileHandler outHandler;
    HuffmenTree tree;
    fs::path rootFolder;
    fs::path compressedFolder;
    size_t originalFSize;
    size_t compressedFSize;
    void compressFile(const string& filePath, const string& relativefilePath);
public:
    Compressor(const string& path);
    void compressFolder();

};

#endif // COMPRESSOR_H
