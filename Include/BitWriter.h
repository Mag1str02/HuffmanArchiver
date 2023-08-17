#pragma once

#include <fstream>
#include <string>
#include <queue>

class BitWriter {
public:
    BitWriter();

    void Close();

    void WriteOneBit(const bool& bit);
    void WriteNumber(uint16_t number);

    bool CanPush();
    unsigned char PushBackChar();
    
    void PrintBits();

private:
    std::queue<bool> bits_;
};
