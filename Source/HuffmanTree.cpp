#include "HuffmanTree.h"
#include <iostream>
#include <algorithm>
#include <queue>

HuffmanTree::HuffmanTree() {
}

void HuffmanTree::SetFileName(const std::string& file_name) {
    file_name_ = file_name;
}

void HuffmanTree::BuildToWrite(std::ifstream& input) {
    BuildTreeToWrite(input);
    BuildLength();
    BuildCanonitioalBook();
}
void HuffmanTree::BuildToRead(const std::vector<uint16_t>& sorted_chars, const std::vector<size_t>& length_amount) {
    BuildCanonitioalBook(sorted_chars, length_amount);
    BuildTreeToRead();
}

void HuffmanTree::Reset() {
    current_pointer_pos_ = nullptr;
    file_name_ = "";
    char_with_length_.clear();
    char_bit_line_.clear();
    tree_.clear();
    char_to_id_.clear();
}

BitLine HuffmanTree::GetBitsFromChar(const uint16_t& symbol) const {
    return char_bit_line_[char_to_id_.at(symbol)];
}
bool HuffmanTree::GetCharFromBits(const bool& bit, uint16_t& symbol) {
    if (bit) {
        current_pointer_pos_ = current_pointer_pos_->right;
    } else {
        current_pointer_pos_ = current_pointer_pos_->left;
    }
    if (current_pointer_pos_->IsTerminal()) {
        symbol = current_pointer_pos_->char_id;
        current_pointer_pos_ = &tree_.front();
        return true;
    }
    return false;
}

uint16_t HuffmanTree::GetCharAmount() const {
    return static_cast<uint16_t>(char_to_id_.size());
}
CharAndLength HuffmanTree::GetSortedChars() const {
    return char_with_length_;
}
Alphabet HuffmanTree::GetCharBits() const {
    return char_bit_line_;
}
FileName HuffmanTree::GetFileName() const {
    return file_name_;
}

void HuffmanTree::BuildTreeToWrite(std::ifstream& input) {
    uint16_t start_id = 260;
    std::map<uint16_t, size_t> char_frequency = BuildFrequency(input);
    std::priority_queue<Node*, std::vector<Node*>, NodeComparator> tree;

    tree_.reserve(char_frequency.size() * 2);
    tree_.resize(char_frequency.size());

    size_t pos = 0;
    for (const auto& symbol : char_frequency) {
        tree_[pos] = Node(symbol.first, symbol.second);
        tree.push(&tree_[pos]);
        ++pos;
    }

    while (tree.size() > 1) {
        Node* a = tree.top();
        tree.pop();
        Node* b = tree.top();
        tree.pop();

        Node c(start_id, a->amount + b->amount);
        c.left = a;
        c.right = b;

        tree_.push_back(c);
        tree.push(&tree_.back());
        ++start_id;
    }
}
void HuffmanTree::BuildTreeToRead() {
    uint16_t start_id = 260;

    tree_.reserve(char_bit_line_.size() * 2);
    tree_.push_back(Node(start_id++, 0));
    current_pointer_pos_ = &tree_.front();

    Node* prev_node;
    for (size_t i = 0; i < char_bit_line_.size(); ++i) {
        prev_node = &tree_.front();
        for (const auto& bit : char_bit_line_[i]) {
            Node** child;
            if (bit) {
                child = &(prev_node->right);
            } else {
                child = &(prev_node->left);
            }
            if (!*(child)) {
                tree_.push_back(Node(start_id++, 0));
                *(child) = &tree_.back();
            }
            prev_node = *(child);
        }
        tree_.back().char_id = char_with_length_[i].first;
        tree_.back().amount = char_with_length_[i].second;
    }
}

void HuffmanTree::BuildCanonitioalBook() {
    for (size_t i = 0; i < char_with_length_.size(); ++i) {
        char_to_id_[char_with_length_[i].first] = i;
    }

    char_bit_line_.resize(char_with_length_.size());
    char_bit_line_[0] = std::vector<bool>(char_with_length_[0].second, 0);
    for (size_t i = 1; i < char_bit_line_.size(); ++i) {
        char_bit_line_[i] = BuildNextCode(char_with_length_[i].second, char_bit_line_[i - 1]);
    }
}
void HuffmanTree::BuildCanonitioalBook(const std::vector<uint16_t>& sorted_chars,
                                       const std::vector<size_t>& length_amount) {
    char_bit_line_.resize(sorted_chars.size());
    size_t pos = 0;
    for (size_t current_length = 1; current_length <= length_amount.size(); ++current_length) {
        size_t same_length_count = 0;
        while (same_length_count < length_amount[current_length - 1]) {
            if (pos == 0) {
                char_bit_line_[pos] = std::vector<bool>(current_length, 0);
            } else {
                char_bit_line_[pos] = BuildNextCode(current_length, char_bit_line_[pos - 1]);
            }
            ++same_length_count;
            ++pos;
        }
    }

    char_with_length_.resize(sorted_chars.size());
    for (size_t i = 0; i < sorted_chars.size(); ++i) {
        char_with_length_[i] = std::make_pair(sorted_chars[i], char_bit_line_[i].size());
    }
}
BitLine HuffmanTree::BuildNextCode(const size_t& length, const BitLine& prev_code) {
    std::vector<bool> next_code = prev_code;
    size_t pos = 0;
    for (size_t i = next_code.size() - 1; i >= 0; --i) {
        if (next_code[i]) {
            next_code[i] = false;
            if (i == 0) {
                next_code.insert(next_code.begin(), true);
            }
        } else {
            next_code[i] = true;
            break;
        }
    }
    while (next_code.size() < length) {
        next_code.push_back(false);
    }
    return next_code;
}
void HuffmanTree::BuildLength() {
    std::vector<std::pair<Node*, uint8_t>> nodes;
    nodes.push_back(std::make_pair(&tree_.back(), 0));
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (!nodes[i].first->left && !nodes[i].first->right) {
            char_with_length_.push_back(std::make_pair(nodes[i].first->char_id, nodes[i].second));
        }
        if (nodes[i].first->left) {
            nodes.push_back(std::make_pair(nodes[i].first->left, nodes[i].second + 1));
        }
        if (nodes[i].first->right) {
            nodes.push_back(std::make_pair(nodes[i].first->right, nodes[i].second + 1));
        }
    }
    std::sort(char_with_length_.begin(), char_with_length_.end(),
              [](const std::pair<uint16_t, size_t>& a, const std::pair<uint16_t, size_t>& b) {
                  if (a.second != b.second)
                      return a.second < b.second;
                  return a.first < b.first;
              });
}
CharToId HuffmanTree::BuildFrequency(std::ifstream& input) const {
    std::streampos begin = input.tellg();
    const uint16_t DELTA = 65280;
    uint16_t char_id;
    char byte;
    CharToId char_frequency;
    for (const auto& symbol : file_name_) {
        char_id = static_cast<uint16_t>(symbol);
        if (char_id > 255) {
            char_id -= DELTA;
        }
        ++char_frequency[char_id];
    }

    while (input.get(byte)) {
        char_id = static_cast<uint16_t>(byte);
        if (char_id > 255) {
            char_id -= DELTA;
        }
        ++char_frequency[char_id];
    }
    ++char_frequency[FILENAME_END];
    ++char_frequency[ONE_MORE_FILE];
    ++char_frequency[ARCHIVE_END];

    input.seekg(begin);

    return char_frequency;
}

void HuffmanTree::PrintTree() const {
    for (size_t i = 0; i < tree_.size(); ++i) {
        std::cout << tree_[i].char_id;
        std::cout << ": " << tree_[i].amount << " |";
        if (tree_[i].left) {
            std::cout << " L: " << tree_[i].left->char_id;
        }
        if (tree_[i].right) {
            std::cout << " R: " << tree_[i].right->char_id;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
void HuffmanTree::PrintCharLength(const CharAndLength& char_length) const {
    for (const auto& symbol : char_length) {
        std::cout << symbol.first;
        std::cout << " " << symbol.second << std::endl;
    }
    std::cout << std::endl;
}
void HuffmanTree::PrintCanonitialBook() const {
    for (size_t i = 0; i < char_with_length_.size(); ++i) {
        std::cout << char_with_length_[i].first << ": ";
        if (char_with_length_[i].first < 100) {
            std::cout << " ";
        }
        if (char_with_length_[i].first < 10) {
            std::cout << " ";
        }
        for (const auto& bit : char_bit_line_[i]) {
            std::cout << (bit ? '1' : '0');
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}