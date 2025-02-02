#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include "Helper.hpp"

using namespace std;

class HCNode {
public:
    int count;
    unsigned char symbol;
    HCNode* c0;
    HCNode* c1;
    HCNode* p;

    HCNode(int count, unsigned char symbol)
        : count(count), symbol(symbol), c0(nullptr), c1(nullptr), p(nullptr) {}
};

class HCNodePtrComp {
public:
    bool operator()(HCNode* lhs, HCNode* rhs) const {
        return lhs->count > rhs->count;
    }
};

class HCTree {
private:
    HCNode* root;
    vector<HCNode*> leaves;

    void deleteTree(HCNode* node);

public:
    HCTree() : root(nullptr), leaves(256, nullptr) {}
    ~HCTree();

    void build(const vector<int>& freqs);
    void encode(unsigned char symbol, FancyOutputStream& out) const;
    unsigned char decode(FancyInputStream& in) const;
    HCNode* getRoot() const;
};

#endif // HCTREE_HPP
