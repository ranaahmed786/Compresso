#pragma once
#ifndef INFILEHANDLER_H
#define INFILEHANDLER_H
#include<vector>
#include<fstream>
using namespace std;

class InFileHandler
{
    string inFilePath;
    size_t fileSize;
    ifstream inFile;
public:
    InFileHandler();
    InFileHandler(const string& path);
    vector<unsigned char> readFile();
    void setPath(const string& path);
    size_t getSize();
};

#endif // INFILEHANDLER_H
