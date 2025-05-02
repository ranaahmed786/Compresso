#include "compressor.h"
Compressor::Compressor(const string& path) :rootFolder(path),TimeTaken(0),FilesProcessed(0),compressedFSize(0),originalFSize(0) {
    string folderExtension = rootFolder.filename().string() + "(Compressed)";
    compressedFolder = rootFolder.parent_path() / folderExtension;
}
void Compressor::compressFolder() {

    if(!fs::is_directory(rootFolder)) {
        throw runtime_error("The provided path is not a valid directory for compression(probably a zip folder)");
        return;
    }
    else {
        QElapsedTimer timer;
        timer.start();
        fs::create_directory(compressedFolder);
        size_t totalFiles = std::distance(fs::recursive_directory_iterator(rootFolder),fs::recursive_directory_iterator());
        fs::path fileSavePath;
        fs::path fileRelativePath;
        size_t processed = 0;
        for (const auto& each : fs::recursive_directory_iterator(rootFolder)) {
            if (each.is_regular_file()) {
                FilesProcessed++;
                fileRelativePath = fs::relative(each.path(), rootFolder);
                compressFile(each.path().string(), (compressedFolder / fileRelativePath).string());
            }
            else if (each.is_directory()) {
                fs::path newDir = compressedFolder / fs::relative(each.path(), rootFolder);
                fs::create_directory(newDir);
            }
            processed++;
            int progressPercent = static_cast<int>((processed * 100) / totalFiles);
            emit progressUpdated(progressPercent);
        }
        TimeTaken=timer.elapsed();
    }
}
void Compressor::compressFile(const string& filePath, const string& fileSavePath) {
    inHandler.setPath(filePath);
    size_t orgSize = filesystem::file_size(filePath);
    originalFSize += orgSize;

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

    // IMPORTANT: Re-fetch actual disk size after writing
    size_t cmpSize = filesystem::file_size(fileSavePath + ".cmp");
    compressedFSize += cmpSize;
}
