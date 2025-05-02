#include "infilehandler.h"

InFileHandler::InFileHandler() {}
InFileHandler::InFileHandler(const string& path){
    inFilePath = path;

}
void InFileHandler::setPath(const string& path) {
    inFilePath = path;
}
vector<unsigned char> InFileHandler::readFile() {
    inFile.open(inFilePath, ios::binary);
    if (!inFile)
        throw runtime_error("Error opening file: " + inFilePath);

    size_t fileSize = fs::file_size(inFilePath);
    vector<unsigned char> fileData(fileSize);

    if (!inFile.read(reinterpret_cast<char*>(fileData.data()), fileSize))
        throw runtime_error("Error reading file: " + inFilePath);

    inFile.close();
    return fileData;
}
