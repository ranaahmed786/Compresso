#include "compressor.h"
#include <vector>
#include<unordered_map>
#include <iostream>
Compressor::Compressor(const string &path):file(path) {}
void Compressor::compressFile(){
    vector<unsigned char> data=file.readFile();
    unordered_map<unsigned char,string> Codes;
    unordered_map<unsigned char,int> frequency;
    for(auto key:data){
        frequency[key]++;
    }
    tree.makeTree(frequency);
    unordered_map<unsigned char,string> u1;
    u1=tree.getCodes();

}
