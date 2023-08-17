#include "BitWriter.h"
#include <stack>
#include <iostream>

void BitWriter::PrintBits() {
    std::queue<bool> buff = bits_;
    for (size_t i = 0; i < bits_.size(); ++i) {
        std::cout << (buff.front() ? '1' : '0');
        buff.pop();
    }
    std::cout << std::endl;
};

BitWriter::BitWriter() {
}

void BitWriter::Close() {
    if (!bits_.empty()) {
        size_t more_bits_amount = 8 - bits_.size();
        for (size_t i = 0; i < more_bits_amount; ++i) {
            bits_.push(false);
        }
    }
}

void BitWriter::WriteOneBit(const bool& bit) {
    bits_.push(bit);
}
void BitWriter::WriteNumber(uint16_t number) {
    const uint16_t MASK = 0b0000'0001'1111'1111;
    number &= MASK;
    for (size_t i = 0; i < 9; ++i) {
        bool bit = (number % 2 == 1);
        bits_.push(bit);
        number /= 2;
    }
}

bool BitWriter::CanPush() {
    return bits_.size() >= 8;
}
unsigned char BitWriter::PushBackChar() {
    uint8_t symbol = 0;
    for (size_t i = 0; i < 8; ++i) {
        symbol = (symbol << 1) + bits_.front();
        bits_.pop();
    }
    return static_cast<unsigned char>(symbol);
}
