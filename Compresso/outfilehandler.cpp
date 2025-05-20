// outfilehandler.cpp
#include "outfilehandler.h"

OutFileHandler::OutFileHandler() {}

OutFileHandler::OutFileHandler(const std::string& path)
    : outFilePath(path + ".cmp") {}


void OutFileHandler::setPath(const std::string& path ,bool forCmp) {
    if(forCmp) outFilePath = path + ".cmp";
    else outFilePath = path;
}

void OutFileHandler::writeOrgFile(const vector<unsigned char>& Data){
    ofstream outFile(outFilePath,ios::binary | ios::trunc);
    if(!outFile)
        throw runtime_error("Error opening Orignal file "+outFilePath);
    else{
        if(!outFile.write(reinterpret_cast<const char*>(Data.data()),Data.size()))
            throw runtime_error("Error writing Orignal file "+outFilePath);
        outFile.close();
    }
}

void OutFileHandler::writeCmpFile(const vector<unsigned char>& orgBytes,
                                  vector<pair<unsigned char, int>>& lengths,
                                  unordered_map<unsigned char, string>& codes) {

    ofstream outFile(outFilePath, ios::binary | ios::trunc);
    if (!outFile) {
        throw runtime_error("Unable to open file for writing: " + outFilePath);
    }


    uint32_t numSymbols = static_cast<uint32_t>(lengths.size());
    outFile.write(reinterpret_cast<const char*>(&numSymbols), sizeof(numSymbols));


    for (const auto& entry : lengths) {
        outFile.put(entry.first);
    }


    for (const auto& entry : lengths) {
        outFile.put(static_cast<char>(entry.second));
    }


    uint32_t totalBitsWritten = 0;
    for (auto byte : orgBytes) {
        totalBitsWritten += static_cast<uint32_t>(codes.at(byte).size());
    }


    outFile.write(reinterpret_cast<const char*>(&totalBitsWritten), sizeof(totalBitsWritten));


    BitWriter writer(outFile);
    for (auto byte : orgBytes) {
        writer.writeBits(codes.at(byte));
    }
    writer.flush();


    fileSize = outFile.tellp();
    outFile.close();
}
