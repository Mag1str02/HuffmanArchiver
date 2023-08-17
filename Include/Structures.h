#pragma once

#include <string>
#include <vector>
#include <utility>
#include <map>

struct Node {
    uint16_t char_id = 0;
    uint64_t amount = 0;
    Node* left = nullptr;
    Node* right = nullptr;

    Node();
    Node(uint16_t id, uint64_t char_amount);

    bool IsTerminal();
};

struct NodeComparator {
    bool operator()(const Node* a, const Node* b) const;
};

using CharAndLength = std::vector<std::pair<uint16_t, size_t>>;
using BitLine = std::vector<bool>;
using FileName = std::string;
using Tree = std::vector<Node>;
using CharToId = std::map<uint16_t, size_t>;
using FrequencyList = std::map<uint16_t, size_t>;
using Alphabet = std::vector<BitLine>;