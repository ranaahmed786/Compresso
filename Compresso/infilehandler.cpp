#include "infilehandler.h"

InFileHandler::InFileHandler() {}
InFileHandler::InFileHandler(const string& path){
    inFilePath = path;

}
void InFileHandler::setPath(const string& path) {
    inFilePath = path;
}
vector<unsigned char>  InFileHandler::readCmpFile(){
    inFile.open(inFilePath, ios::binary);
    if(!inFile)
        throw runtime_error("Error opening file: " + inFilePath);
    else {
        uint32_t totalBits = 0;
        uint32_t numofsymb = 0;

        //  Read number of symbols (4 bytes)
        if (!inFile.read(reinterpret_cast<char*>(&numofsymb), sizeof(numofsymb))) {
            throw runtime_error("Error reading number of symbols in file header of: " + inFilePath);
        }

        vector<unsigned char> symbols(numofsymb);
        vector<unsigned char> lengths(numofsymb);

        // Read symbols (numofsymb bytes)
        if (!inFile.read(reinterpret_cast<char*>(symbols.data()), numofsymb)) {
            throw runtime_error("Error reading symbols in file header of: " + inFilePath);
        }

        //  Read code lengths (numofsymb bytes )
        if (!inFile.read(reinterpret_cast<char*>(lengths.data()), numofsymb)) {
            throw runtime_error("Error reading code lengths in file header of: " + inFilePath);
        }

        //Read total number of encoded bits (4 bytes)
        if (!inFile.read(reinterpret_cast<char*>(&totalBits), sizeof(totalBits))) {
            throw runtime_error("Error reading number of data bits in file header of: " + inFilePath);
        }

        unordered_map<unsigned char, string> CanonicalCodes;
        vector<pair<unsigned char, int>> SymbolsNLengths;

        for (uint32_t i = 0; i < numofsymb; ++i)
             SymbolsNLengths.push_back({symbols[i], static_cast<int>(lengths[i])});

        HuffmenTree Tree;
        Tree.getHuffCanonicalCodes(SymbolsNLengths, CanonicalCodes, true);

        //reversing the mapping for the Canonical codes
        unordered_map<string,unsigned char> CodeToSymbol;
        for (const auto& each:CanonicalCodes)
            CodeToSymbol[each.second]=each.first;

        BitReader reader(inFile);
        vector<unsigned char> decodedBytes;
        string currentBits;

        for (uint32_t i = 0; i < totalBits; ++i) {
            bool bit = reader.readBit();
            currentBits += bit ? '1' : '0';

            auto it = CodeToSymbol.find(currentBits);
            if (it != CodeToSymbol.end()) {
                decodedBytes.push_back(it->second);
                currentBits.clear(); // Reset for next symbol
            }
        }
        inFile.close();
        return decodedBytes;
    }
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
