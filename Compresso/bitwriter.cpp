#include "bitwriter.h"
BitWriter::BitWriter(ofstream &outputStream): out(outputStream), buffer(0), bitCount(0) {}

BitWriter::~BitWriter() {
    flush(); // Auto-flush remaining bits when BitWriter goes out of scope
}

void BitWriter::writeBit(bool bit) {
    buffer <<= 1;           // Make space for the next bit
    if (bit) {
        buffer |= 1;        // Set the least significant bit if bit is 1
    }
    bitCount++;
    if (bitCount == 8) {
        out.put(buffer);    // Write full byte to output
        bitCount = 0;
        buffer = 0;
    }
}

void BitWriter::writeBits(const string &bits) {
    for (char bitChar : bits) {
        writeBit(bitChar == '1');
    }
}

void BitWriter::flush() {
    if (bitCount > 0) {
        buffer <<= (8 - bitCount); // Shift remaining bits to the left
        out.put(buffer);
        buffer = 0;
        bitCount = 0;
    }
}
