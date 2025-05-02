#include "infilehandler.h"

InFileHandler::InFileHandler() {}
InFileHandler::InFileHandler(const string& path):fileSize(0) {
    inFilePath = path;

}
size_t InFileHandler::getSize() {
    if (inFilePath.empty()) {
        throw std::runtime_error("No file path specified");
    }

    inFile.open(inFilePath, ios::binary);
    if (!inFile) {
        throw runtime_error("Error opening file: "+inFilePath);
    }

    inFile.seekg(0,ios::end);
    fileSize = inFile.tellg();
    inFile.seekg(0,ios::beg);
    inFile.close();

    return fileSize;
}

void InFileHandler::setPath(const string& path) {
    inFilePath = path;
    getSize();
}
vector<unsigned char> InFileHandler::readFile() {
    inFile.open(inFilePath, ios::binary);
    vector<unsigned char> fileData(fileSize);
    if (!inFile.read(reinterpret_cast<char*>(fileData.data()), fileSize))
        throw runtime_error("Error reading file :" +inFilePath);
    inFile.close();
    return fileData;
}
