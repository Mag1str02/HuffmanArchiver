#pragma once

#include <fstream>
#include <string>
#include <queue>

class BitReader {
public:
    explicit BitReader(std::string file_name);
    ~BitReader();

    bool ReadOneBit();
    uint16_t ReadNineBit();

    void PrintBits();

private:
    std::ifstream input_;
    std::queue<bool> bits_;

    void PushBackChar();
};
