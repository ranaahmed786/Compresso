#include "compressor.h"
Compressor::Compressor(const string& path) :rootFolder(path) {
    string folderExtension = rootFolder.filename().string() + "(Compressed)";
    compressedFolder = rootFolder.parent_path() / folderExtension;
}
void Compressor::compressFolder() {
    if(!fs::is_directory(rootFolder)) {
        throw runtime_error("The provided path is not a valid directory for compression(probably a zip folder)");
        return;
    }
    else {
        fs::create_directory(compressedFolder);
        fs::path fileSavePath;
        fs::path fileRelativePath;
        for (const auto& each : fs::recursive_directory_iterator(rootFolder)) {
            if (each.is_regular_file()) {
                fileRelativePath = fs::relative(each.path(), rootFolder);
                compressFile(each.path().string(), (compressedFolder / fileRelativePath).string());
            }
            else if (each.is_directory()) {
                fs::path newDir = compressedFolder / fs::relative(each.path(), rootFolder);
                fs::create_directory(newDir);
            }
        }
    }
}
void Compressor::compressFile(const string& filePath, const string& fileSavePath) {
    inHandler.setPath(filePath);
    originalFSize += inHandler.getSize();
    vector<unsigned char> data = inHandler.readFile();
    unordered_map<unsigned char, int> frequency;
    for (auto key : data) {
        frequency[key]++;
    }
    tree.makeTree(frequency);
    unordered_map<unsigned char, string> bytesNcodes;
    vector<pair<unsigned char, int>> lenghts;
    tree.getHuffCanonicalCodes(lenghts, bytesNcodes);
    outHandler.setPath(fileSavePath);
    outHandler.writeCmpFile(data, lenghts, bytesNcodes);
    compressedFSize += outHandler.getSize();
}
