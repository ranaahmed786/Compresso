// outfilehandler.cpp
#include "outfilehandler.h"

OutFileHandler::OutFileHandler() : fileSize(0) {}

OutFileHandler::OutFileHandler(const std::string& path)
    : outFilePath(path + ".cmp"), fileSize(0) {}

size_t OutFileHandler::getSize() {
    std::ifstream inFile(outFilePath, ios::binary | ios::ate);
    if (!inFile) {
        return 0; // File doesn't exist yet
    }
    fileSize = inFile.tellg();
    inFile.close();
    return fileSize;
}

void OutFileHandler::setPath(const std::string& path) {
    outFilePath = path + ".cmp";
    fileSize = 0;
}

void OutFileHandler::writeCmpFile(const std::vector<unsigned char>& orgBytes,
                                  std::vector<std::pair<unsigned char, int>>& lenghts,
                                  std::unordered_map<unsigned char, std::string>& codes) {
    // Open output file (truncate if exists)
    std::ofstream outFile(outFilePath, std::ios::binary | std::ios::trunc);
    if (!outFile) {
        throw std::runtime_error("Unable to open file for writing: " + outFilePath);
    }

    // Write header
    uint32_t numSymbols = static_cast<uint32_t>(lenghts.size());
    outFile.write(reinterpret_cast<const char*>(&numSymbols), sizeof(numSymbols));

    // Write symbols
    for (const auto& entry : lenghts) {
        outFile.put(entry.first);
    }

    // Write code lengths
    for (const auto& entry : lenghts) {
        outFile.put(static_cast<char>(entry.second));
    }

    // Write compressed data
    BitWriter writer(outFile);
    for (auto byte : orgBytes) {
        writer.writeBits(codes.at(byte));
    }
    writer.flush();

    // Update file size
    fileSize = outFile.tellp();
    outFile.close();
}
