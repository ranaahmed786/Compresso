#include "compressor.h"
#include <vector>
#include<unordered_map>
Compressor::Compressor(const string &path):file(path) {}
void Compressor::compressFile(){
    vector<unsigned char> data=file.readFile();
    unordered_map<unsigned char,string> Codes;
    unordered_map<unsigned char,int> frequency;
    for(auto key:data){
        frequency[key]++;
    }
    tree.makeTree(frequency);
}
