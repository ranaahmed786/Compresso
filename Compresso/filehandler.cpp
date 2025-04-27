#include "filehandler.h"
#include "bitwriter.h"
FileHandler::FileHandler(const string &Filename):filePath(Filename),fileSize(0) {
    inFile.open(filePath,ios::binary);
    if(!inFile) throw runtime_error("error opening file");
    else{
        inFile.seekg(0,ios::end);
        fileSize=inFile.tellg();
        inFile.seekg(0,ios::beg);
    }
}

vector<unsigned char> FileHandler::readFile()
{
    vector<unsigned char> fileData(fileSize);
    if (!inFile.read(reinterpret_cast<char*>(fileData.data()), fileSize))
        throw runtime_error("Error reading file");

    return fileData;
}
void FileHandler::writeCompressedFile(const string &outFilePath,const vector<unsigned char> orgBytes,const unordered_map<unsigned char,string> &codes){
    outFile.open(outFilePath + getFileName() + ".comp", ios::binary | ios::trunc);
    if(!outFile.is_open()) throw runtime_error("unable to write compressed file");
    BitWriter writer(outFile);
    for(auto byte:orgBytes){
        writer.writeBits(codes.at(byte));
    }
    writer.flush();
    outFile.close();
}
string FileHandler::getFileName() const{

    size_t lastSlash = filePath.find_last_of("/\\");
    size_t lastDot = filePath.find_last_of(".");
    return filePath.substr(lastSlash + 1, lastDot - lastSlash - 1);

}
size_t FileHandler::getSize() const{
    return fileSize;
}
