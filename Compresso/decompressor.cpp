#include "decompressor.h"

Decompressor::Decompressor(const string&cmpFolderPath ):compressedFolderP(cmpFolderPath),TimeTaken(0),FilesProcessed(0),originalFSize(0),compressedFSize(0){

    const string suffix = "(Compressed)";
    string name = compressedFolderP.filename().string();
    if (name.size() > suffix.size() && name.substr(name.size() - suffix.size()) == suffix) {
        name = name.substr(0, name.size() - suffix.size());
    }
    fs::path basePath = compressedFolderP.parent_path();
    fs::path newFolder = basePath / name;
    int count = 1;
    while (fs::exists(newFolder)) {
        newFolder = basePath / (name + " (" + std::to_string(count) + ")");
        count++;
    }
    decompressedFolderP = newFolder;
}

void Decompressor::decompressFile(const string&cmpFilePath,const string&orgFilePath){
    inHandler.setPath(cmpFilePath);
    size_t cmpSize = filesystem::file_size(cmpFilePath);
    compressedFSize += cmpSize;
    vector<unsigned char> Data;
    Data = inHandler.readCmpFile();
    outHandler.setPath(orgFilePath,false);
    outHandler.writeOrgFile(Data);
    size_t orgSize = filesystem::file_size(orgFilePath);
    originalFSize += orgSize;
}

void Decompressor::decompressFolder(){

            QElapsedTimer timer;
            timer.start();
            fs::create_directory(decompressedFolderP);
            size_t totalFiles = std::distance(fs::recursive_directory_iterator(compressedFolderP),fs::recursive_directory_iterator());
            size_t processed =0;
            int pos;
            string FileName;
            fs::path  fileRelativePath;
            for(auto& each:fs::recursive_directory_iterator(compressedFolderP)){
                if(each.is_regular_file()){
                    if(isCmpFile(each.path())){
                        FilesProcessed++;
                        FileName = fs::relative(each.path(), compressedFolderP).string();
                        pos = FileName.find_last_of(".");
                        fileRelativePath = FileName.substr(0, pos);
                        decompressFile(each.path().string(), (decompressedFolderP / fileRelativePath).string());
                    }
                }
                else if(each.is_directory()){
                    fs::path newDir = decompressedFolderP / fs::relative(each.path(), compressedFolderP);
                    fs::create_directory(newDir);
                }
                processed++;
                int progressPercent = static_cast<int>((processed * 100) / totalFiles);
                emit progressUpdated(progressPercent);
            }
            TimeTaken =timer.elapsed();
}
bool Decompressor::isCmpFile(const fs::path &filepath){
    return filepath.extension() == ".cmp";  // much cleaner
}
