#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "utils/utils.h"

typedef void (*BSTIterator)(void* elem);

typedef struct BSTNode {
    void* value;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* NewBSTNode(void* value, size_t size);
void FreeBSTNode(BSTNode* node);

typedef struct BinarySearchTree {
    size_t height;
    size_t memb_size;
    Compare compare;
    BSTNode* head;
} BinarySearchTree;

BinarySearchTree NewBinarySearchTree(size_t memb_size, Compare compare);
void FreeBinarySearchTree(BinarySearchTree* bst);

BSTNode* BSTSearch(BinarySearchTree* bst, void* elem);
int BSTInsert(BinarySearchTree* bst, void* elem);
int BSTRemove(BinarySearchTree* bst, void* elem);

BSTNode* BSTMin(BSTNode* root);
BSTNode* BSTMax(BSTNode* root);

// sorted
void BSTInorderTraversal(BSTNode* root, BSTIterator iterator);
// root then nodes
void BSTPreorderTraversal(BSTNode* root, BSTIterator iterator);
// nodes then root
void BSTPostorderTraversal(BSTNode* root, BSTIterator iterator);
// level by lelvel top to bottom
void BSTLevelTraversal(BSTNode* root, BSTIterator iterator);
