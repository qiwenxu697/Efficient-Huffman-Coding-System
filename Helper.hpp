#ifndef HELPER_HPP
#define HELPER_HPP

#include <fstream>
#include <vector>

using namespace std;

class FancyInputStream {
private:
    ifstream in;
    int bitBuffer;
    int bitCount;

public:
    FancyInputStream(const string& filename);
    ~FancyInputStream();
    int read_byte();
    int read_bit();
    bool good();
    void reset();
};

class FancyOutputStream {
private:
    ofstream out;
    int bitBuffer;
    int bitCount;

public:
    FancyOutputStream(const string& filename);
    ~FancyOutputStream();
    void write_byte(unsigned char byte);
    void write_bit(int bit);
    void write_int(int value);
    void flush();
};

void error(const string& message);

#endif // HELPER_HPP
