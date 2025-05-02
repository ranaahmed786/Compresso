#pragma once
#ifndef INFILEHANDLER_H
#define INFILEHANDLER_H
#include<vector>
#include<fstream>
#include<filesystem>
namespace fs=std::filesystem;
using namespace std;

class InFileHandler
{
    string inFilePath;
    ifstream inFile;
public:
    InFileHandler();
    InFileHandler(const string& path);
    vector<unsigned char> readFile();
    void setPath(const string& path);
};

#endif // INFILEHANDLER_H
