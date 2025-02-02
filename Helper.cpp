#include "Helper.hpp"
#include <iostream>

FancyInputStream::FancyInputStream(const string& filename) : bitBuffer(0), bitCount(0) {
    in.open(filename, ios::binary);
}

FancyInputStream::~FancyInputStream() {
    in.close();
}

int FancyInputStream::read_byte() {
    char byte;
    if (in.read(&byte, 1)) {
        return static_cast<unsigned char>(byte);
    }
    return -1;
}

int FancyInputStream::read_bit() {
    if (bitCount == 0) {
        bitBuffer = read_byte();
        if (bitBuffer == -1) return -1;
        bitCount = 8;
    }
    return (bitBuffer >> (--bitCount)) & 1;
}

bool FancyInputStream::good() {
    return in.good();
}

void FancyInputStream::reset() {
    in.clear();
    in.seekg(0, ios::beg);
}

FancyOutputStream::FancyOutputStream(const string& filename) : bitBuffer(0), bitCount(0) {
    out.open(filename, ios::binary);
}

FancyOutputStream::~FancyOutputStream() {
    flush();
    out.close();
}

void FancyOutputStream::write_byte(unsigned char byte) {
    out.put(byte);
}

void FancyOutputStream::write_bit(int bit) {
    bitBuffer = (bitBuffer << 1) | (bit & 1);
    if (++bitCount == 8) {
        flush();
    }
}

void FancyOutputStream::write_int(int value) {
    for (int i = 3; i >= 0; --i) {
        write_byte((value >> (i * 8)) & 0xFF);
    }
}

void FancyOutputStream::flush() {
    if (bitCount > 0) {
        bitBuffer <<= (8 - bitCount);
        out.put(bitBuffer);
        bitBuffer = 0;
        bitCount = 0;
    }
}

void error(const string& message) {
    cerr << "Error: " << message << endl;
}
