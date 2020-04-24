//
// Created by wangheng on 2020/4/24.
//

#ifndef CPP_PRIMER_EX13_28_H
#define CPP_PRIMER_EX13_28_H

#include <string>

class TreeNode {
private:
    std::string value;
    int *count;
    TreeNode *left;
    TreeNode *right;
public:
    TreeNode() : value(std::string()), count(new int(1)), left(nullptr), right(nullptr) {}
    TreeNode(const TreeNode& tn) :
        value(tn.value), count(tn.count), left(tn.left), right(tn.right){ ++*tn.count; }
    TreeNode& operator=(const TreeNode&);
    ~TreeNode();
};

TreeNode& TreeNode::operator=(const TreeNode &rhs) {
    ++*rhs.count;
    if (--*count == 0) {
        delete left;
        delete right;
        delete count;
    }
    left = rhs.left;
    right = rhs.right;
    count = rhs.count;
    value = rhs.value;

    return *this;
}

TreeNode::~TreeNode() {
    if (--*count == 0) {
        delete left;
        delete right;
        delete count;
    }
}

class BinStrTree {
private:
    TreeNode *root;
public:
    BinStrTree() : root(new TreeNode()) {}
    BinStrTree(const BinStrTree& bst) :
        root(new TreeNode(*bst.root)) {}
    BinStrTree& operator=(const BinStrTree&);
    ~BinStrTree();
};

BinStrTree& BinStrTree::operator=(const BinStrTree &rhs) {
    TreeNode* new_root = new TreeNode(*rhs.root);
    delete root;
    root = new_root;
    return *this;
}

BinStrTree::~BinStrTree() {
    delete root;
}

#endif //CPP_PRIMER_EX13_28_H
