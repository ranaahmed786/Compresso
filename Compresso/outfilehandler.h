// outfilehandler.h
#ifndef OUTFILEHANDLER_H
#define OUTFILEHANDLER_H

#include <fstream>
#include <vector>
#include <unordered_map>
#include "bitwriter.h"
#include <cstdint>
#include <string>
#include<filesystem>

class OutFileHandler {
    std::string outFilePath;
    size_t fileSize;

public:
    OutFileHandler();
    OutFileHandler(const std::string& path);
    void writeOrgFile(const vector<unsigned char>& Data);
    void writeCmpFile(const std::vector<unsigned char>& orgBytes,
                      std::vector<std::pair<unsigned char, int>>& lenghts,
                      std::unordered_map<unsigned char, std::string>& codes);
    void setPath(const std::string& path ,bool forCmp =true) ;
};

#endif // OUTFILEHANDLER_H
