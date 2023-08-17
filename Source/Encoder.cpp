#include "Encoder.h"
#include <iostream>

Encoder::Encoder() {
}

void Encoder::EncodeData(std::vector<std::ifstream>& input_streams, std::ofstream& output_stream,
                         const std::vector<std::string>& file_names) {
    BitWriter output;
    std::vector<HuffmanTree> trees(input_streams.size());

    for (size_t i = 0; i < input_streams.size(); ++i) {
        trees[i].SetFileName(file_names[i]);
        trees[i].BuildToWrite(input_streams[i]);
        WriteFile(output, trees[i], (i == input_streams.size() - 1), output_stream);
    }
}

void Encoder::WriteFile(BitWriter& output, HuffmanTree& tree, bool last, std::ofstream& output_stream) {
    WriteFileInfo(output, tree, output_stream);
    WriteFileName(output, tree, output_stream);
    WriteFileBody(output, tree, last, output_stream);
    std::cout << tree.GetFileName() << " - done" << std::endl;
}

void Encoder::WriteFileInfo(BitWriter& output, HuffmanTree& tree, std::ofstream& output_stream) {
    std::vector<std::pair<uint16_t, size_t>> sorted_chars = tree.GetSortedChars();
    std::vector<uint16_t> length_amount(259, 0);
    size_t char_count = 0;

    output.WriteNumber(tree.GetCharAmount());
    WriteToStream(output, output_stream);

    for (const auto& symbol : sorted_chars) {
        output.WriteNumber(symbol.first);
        WriteToStream(output, output_stream);
    }

    for (const auto& symbol : sorted_chars) {
        ++length_amount[symbol.second];
    }

    for (size_t i = 1; i < length_amount.size() && char_count < tree.GetCharAmount(); ++i) {
        char_count += length_amount[i];
        output.WriteNumber(length_amount[i]);
        WriteToStream(output, output_stream);
    }
}
void Encoder::WriteFileName(BitWriter& output, HuffmanTree& tree, std::ofstream& output_stream) {
    std::vector<bool> code;
    const uint16_t MASK = 0b0000'0000'1111'1111;
    std::string file_name = tree.GetFileName();
    for (size_t i = 0; i <= file_name.size(); ++i) {
        if (i == file_name.size()) {
            code = tree.GetBitsFromChar(FILENAME_END);
        } else {
            code = tree.GetBitsFromChar(static_cast<uint16_t>(file_name[i]) & MASK);
        }

        for (const auto& bit : code) {
            output.WriteOneBit(bit);
            WriteToStream(output, output_stream);
        }
    }
}
void Encoder::WriteFileBody(BitWriter& output, HuffmanTree& tree, bool last, std::ofstream& output_stream) {
    std::vector<bool> code;
    const uint16_t MASK = 0b0000'0000'1111'1111;
    char symbol;
    std::ifstream input(tree.GetFileName());

    while (input.get(symbol)) {
        code = tree.GetBitsFromChar(static_cast<uint16_t>(symbol) & MASK);
        for (const auto& bit : code) {
            output.WriteOneBit(bit);
            WriteToStream(output, output_stream);
        }
    }
    if (last) {
        code = tree.GetBitsFromChar(ARCHIVE_END);
    } else {
        code = tree.GetBitsFromChar(ONE_MORE_FILE);
    }
    for (const auto& bit : code) {
        output.WriteOneBit(bit);
        WriteToStream(output, output_stream);
    }
    output.Close();
    WriteToStream(output, output_stream);
}
void Encoder::WriteToStream(BitWriter& output, std::ofstream& output_stream) {
    while(output.CanPush()){
        output_stream << output.PushBackChar();
    }
}
