#ifndef FILEHANDLER_H
#define FILEHANDLER_H
#include<vector>
#include<fstream>
#include<unordered_map>
using namespace std;
class FileHandler
{
    string filePath;
    size_t fileSize;
    ifstream inFile;
    ofstream outFile;

public:
    FileHandler(const string &Filename);
    void writeCompressedFile(const string &outFilePath,const vector<unsigned char> orgBytes,const unordered_map <unsigned char,string> &codes);
    void writeFile(const string &outfilePath,const vector<unsigned char> &compressedData);
    vector<unsigned char> readFile();
    string getFileName() const;
    size_t getSize() const;
};

#endif // FILEHANDLER_H
