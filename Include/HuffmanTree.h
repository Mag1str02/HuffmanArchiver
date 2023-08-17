#pragma once

#include "Structures.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <utility>

const uint16_t FILENAME_END = 256;
const uint16_t ONE_MORE_FILE = 257;
const uint16_t ARCHIVE_END = 258;

class HuffmanTree {
public:
    HuffmanTree();
    void SetFileName(const std::string& file_name);

    void BuildToWrite(std::ifstream& input);
    void BuildToRead(const std::vector<uint16_t>& sorted_chars, const std::vector<size_t>& length_amount);

    void Reset();

    BitLine GetBitsFromChar(const uint16_t& symbol) const;
    bool GetCharFromBits(const bool& bit, uint16_t& symbol);

    uint16_t GetCharAmount() const;
    CharAndLength GetSortedChars() const;
    Alphabet GetCharBits() const;
    FileName GetFileName() const;

    void PrintTree() const;
    void PrintCharLength(const CharAndLength& char_length) const;
    void PrintCanonitialBook() const;

private:

    Node* current_pointer_pos_;
    FileName file_name_;
    CharAndLength char_with_length_;
    Alphabet char_bit_line_;
    Tree tree_;
    CharToId char_to_id_;

    void BuildTreeToWrite(std::ifstream& input);
    void BuildTreeToRead();
    void BuildCanonitioalBook();
    void BuildCanonitioalBook(const std::vector<uint16_t>& sorted_chars, const std::vector<size_t>& length_amount);
    void BuildLength();
    FrequencyList BuildFrequency(std::ifstream& input) const;
    BitLine BuildNextCode(const size_t& length, const BitLine& prev_num);
};
