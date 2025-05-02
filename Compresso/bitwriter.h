#ifndef BITWRITER_H
#define BITWRITER_H
#include<fstream>
using namespace std;
class BitWriter
{
    ofstream& out;
    unsigned char buffer;
    int bitCount;
    void writeBit(bool bit);
public:
    BitWriter(ofstream& outputStream);
    ~BitWriter();
    void writeBits(const std::string& bits);
    void flush();
};
#endif // BITWRITER_H
