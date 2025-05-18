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
    // Open output file (truncate if exists)
    ofstream outFile(outFilePath, ios::binary | ios::trunc);
    if (!outFile) {
        throw runtime_error("Unable to open file for writing: " + outFilePath);
    }

    // Write number of symbols
    uint32_t numSymbols = static_cast<uint32_t>(lengths.size());
    outFile.write(reinterpret_cast<const char*>(&numSymbols), sizeof(numSymbols));

    // Write all symbols
    for (const auto& entry : lengths) {
        outFile.put(entry.first);
    }

    // Write corresponding code lengths
    for (const auto& entry : lengths) {
        outFile.put(static_cast<char>(entry.second));
    }

    // Calculate total number of bits to be written
    uint32_t totalBitsWritten = 0;
    for (auto byte : orgBytes) {
        totalBitsWritten += static_cast<uint32_t>(codes.at(byte).size());
    }

    // Write total number of bits (for  decoding and padding handling)
    outFile.write(reinterpret_cast<const char*>(&totalBitsWritten), sizeof(totalBitsWritten));

    // Write compressed data using BitWriter
    BitWriter writer(outFile);
    for (auto byte : orgBytes) {
        writer.writeBits(codes.at(byte));
    }
    writer.flush();

    // Update file size
    fileSize = outFile.tellp();
    outFile.close();
}
