#pragma once
#ifndef INFILEHANDLER_H
#define INFILEHANDLER_H
#include"huffmantree.h"
#include"bitreader.h"
#include<vector>
#include<cstdint>
#include<fstream>
#include<filesystem>
#include<unordered_map>
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
    vector<unsigned char>  readCmpFile();
    void setPath(const string& path);
};

#endif // INFILEHANDLER_H
