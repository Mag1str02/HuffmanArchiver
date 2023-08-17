#include "Structures.h"

Node::Node(uint16_t id, uint64_t char_amount) : char_id(id), amount(char_amount) {
}
Node::Node() {
}
bool Node::IsTerminal() {
    return !left && !right;
}

bool NodeComparator::operator()(const Node* a, const Node* b) const {
    if (a->amount != b->amount)
        return a->amount > b->amount;
    return a->char_id > b->char_id;
};
