#include "bitreader.h"

BitReader::BitReader(std::ifstream& inputStream)
    : in(inputStream), buffer(0), bitCount(0) {}

bool BitReader::readBit() {
    if (bitCount == 0) {
        if (!in.get(reinterpret_cast<char&>(buffer))) {
            throw std::runtime_error("Unexpected EOF while reading bits");
        }
        bitCount = 8;
    }

    bool bit = buffer & (1 << 7);
    bit = bit != 0;
    buffer <<= 1;
    --bitCount;
    return bit;
}
