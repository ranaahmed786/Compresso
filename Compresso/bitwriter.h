#ifndef BITWRITER_H
#define BITWRITER_H
#include<fstream>
using namespace std;
class BitWriter
{
    ofstream &out;
    unsigned char buffer;
    int bitCount;
public:
    BitWriter(ofstream &outputStream);
    ~BitWriter();
    void writeBit(bool bit);
    void writeBits(const std::string &bits);
    void flush();
};
#endif // BITWRITER_H
