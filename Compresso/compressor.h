#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include"filehandler.h"
#include"huffmentree.h"
class Compressor
{
    FileHandler file;
    HuffmenTree tree;

public:
    Compressor(const string & path);
    void compressFile();
    void saveFileAs();

};

#endif // COMPRESSOR_H
