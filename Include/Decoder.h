#pragma once

#include "HuffmanTree.h"
#include "BitReader.h"

class Decoder {
public:
    Decoder();

    void DecodeData(const std::string& input_file_name);

private:
    bool ReadFile(BitReader& input, HuffmanTree& tree);
    void ReadFileInfo(BitReader& input, HuffmanTree& tree);
    std::string ReadFileName(BitReader& input, HuffmanTree& tree);
    bool ReadFileBodyAndWriteToFile(BitReader& input, HuffmanTree& tree, const std::string& file_name);
};
