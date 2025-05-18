#ifndef BITREADER_H
#define BITREADER_H
#include<fstream>
using namespace std;
class BitReader {
    ifstream& in;
    unsigned char buffer;
    int bitCount;

public:
    BitReader(std::ifstream& inputStream);
    bool readBit();
};

#endif // BITREADER_H
