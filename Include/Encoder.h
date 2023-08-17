#pragma once

#include "HuffmanTree.h"
#include "BitWriter.h"

class Encoder {
public:
    Encoder();

    void EncodeData(std::vector<std::ifstream>& input_streams, std::ofstream& output_stream,
                    const std::vector<std::string>& file_names);

private:
    void WriteFile(BitWriter& output, HuffmanTree& tree, bool last, std::ofstream& output_stream);
    void WriteFileInfo(BitWriter& output, HuffmanTree& tree, std::ofstream& output_stream);
    void WriteFileName(BitWriter& output, HuffmanTree& tree, std::ofstream& output_stream);
    void WriteFileBody(BitWriter& output, HuffmanTree& tree, bool last, std::ofstream& output_stream);
    void WriteToStream(BitWriter& output, std::ofstream& output_stream);
};
