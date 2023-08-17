#include "Decoder.h"
#include <iostream>

Decoder::Decoder() {
}

void Decoder::DecodeData(const std::string& input_file_name) {
    BitReader input(input_file_name);
    HuffmanTree tree;
    while (true) {
        tree.Reset();
        if (ReadFile(input, tree)) {
            break;
        }
    }
}

bool Decoder::ReadFile(BitReader& input, HuffmanTree& tree) {
    ReadFileInfo(input, tree);
    std::string file_name = ReadFileName(input, tree);
    bool result = ReadFileBodyAndWriteToFile(input, tree, file_name);
    std::cout << file_name << " - done" << std::endl;
    return result;
}
void Decoder::ReadFileInfo(BitReader& input, HuffmanTree& tree) {
    size_t symbol_length_count;
    std::vector<uint16_t> sorted_chars;
    std::vector<size_t> length_amount;
    uint16_t symbol_amount;

    symbol_length_count = 0;
    symbol_amount = input.ReadNineBit();
    sorted_chars.resize(symbol_amount);

    for (auto& symbol : sorted_chars) {
        symbol = input.ReadNineBit();
    }

    while (symbol_length_count < symbol_amount) {
        length_amount.push_back(input.ReadNineBit());
        symbol_length_count += length_amount.back();
    }

    tree.BuildToRead(sorted_chars, length_amount);
}
std::string Decoder::ReadFileName(BitReader& input, HuffmanTree& tree) {
    std::string file_name;
    while (true) {
        uint16_t symbol;
        bool bit = input.ReadOneBit();
        if (tree.GetCharFromBits(bit, symbol)) {
            if (symbol == FILENAME_END) {
                break;
            }
            file_name.append(" ");
            file_name[file_name.size() - 1] = static_cast<char>(symbol);
        }
    }
    return file_name;
}
bool Decoder::ReadFileBodyAndWriteToFile(BitReader& input, HuffmanTree& tree, const std::string& file_name) {
    std::ofstream output(file_name);
    while (true) {
        uint16_t symbol;
        bool bit = input.ReadOneBit();
        if (tree.GetCharFromBits(bit, symbol)) {
            if (symbol == ONE_MORE_FILE) {
                return false;
            }
            if (symbol == ARCHIVE_END) {
                return true;
            }
            output << static_cast<char>(symbol);
        }
    }
}