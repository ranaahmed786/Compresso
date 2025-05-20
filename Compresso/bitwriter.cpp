#include "bitwriter.h"
BitWriter::BitWriter(ofstream& outputStream) : out(outputStream), buffer(0), bitCount(0) {}

BitWriter::~BitWriter() {
    flush();
}

void BitWriter::writeBit(bool bit) {
    buffer <<= 1;
    if (bit) {
        buffer |= 1;
    }
    bitCount++;
    if (bitCount == 8) {
        out.put(buffer);
        bitCount = 0;
        buffer = 0;
    }
}

void BitWriter::writeBits(const string& bits) {
    for (char bitChar : bits) {
        writeBit(bitChar == '1');
    }
}

void BitWriter::flush() {
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        out.put(buffer);
        buffer = 0;
        bitCount = 0;
    }
}
