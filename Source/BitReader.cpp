#include "BitReader.h"
#include <stack>
#include <iostream>

void BitReader::PrintBits() {
    std::queue<bool> buff = bits_;
    for (size_t i = 0; i < bits_.size(); ++i) {
        std::cout << (buff.front() ? '1' : '0');
        buff.pop();
    }
    std::cout << std::endl;
};

BitReader::BitReader(std::string file_name) {
    input_.open(file_name, std::ios::in);
}
BitReader::~BitReader() {
    input_.close();
}

bool BitReader::ReadOneBit() {
    if (bits_.empty()) {
        PushBackChar();
    }
    bool bit = bits_.front();
    bits_.pop();
    return bit;
}
uint16_t BitReader::ReadNineBit() {
    uint16_t nine_bit = 0;
    uint16_t step = 1;

    if (bits_.size() < 9) {
        PushBackChar();
    }
    if (bits_.size() < 9) {
        PushBackChar();
    }

    for (size_t i = 0; i < 9; ++i) {
        nine_bit += step * bits_.front();
        step <<= 1;
        bits_.pop();
    }
    return nine_bit;
}

void BitReader::PushBackChar() {
    char tmp;
    uint8_t byte;
    std::stack<bool> bits_of_byte;

    input_.get(tmp);
    byte = static_cast<uint8_t>(tmp);

    for (size_t i = 0; i < 8; ++i) {
        bits_of_byte.push(byte % 2 == 1);
        byte >>= 1;
    }
    for (size_t i = 0; i < 8; ++i) {
        bits_.push(bits_of_byte.top());
        bits_of_byte.pop();
    }
}