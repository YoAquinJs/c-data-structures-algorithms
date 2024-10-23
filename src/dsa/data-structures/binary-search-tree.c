#include "binary-search-tree.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "dsa/data-structures/vector.h"

BSTNode* NewBSTNode(void* value, size_t size) {
    BSTNode* node = malloc(sizeof(BSTNode) + size);
    if (!node) {
        return NULL;
    }
    node->left = NULL;
    node->right = NULL;

    node->value = (void*)(node + sizeof(BSTNode));

    memcpy(node->value, value, size);
    return node;
}

void FreeBSTNode(BSTNode* node) {
    free(node);
}

BinarySearchTree NewBinarySearchTree(size_t memb_size, Compare compare) {
    return (BinarySearchTree){0, memb_size, compare, NULL};
}

void FreeBinarySearchTree(BinarySearchTree* bst) {
    BSTPostorderTraversal(bst->head, (BSTIterator)FreeBSTNode);
    bst->head = NULL;
}

BSTNode* RecursiveSearch(BSTNode* node, void* elem, Compare compare);

BSTNode* BSTSearch(BinarySearchTree* bst, void* elem) {
    return RecursiveSearch(bst->head, elem, bst->compare);
}

int RecursiveInsert(BSTNode* node, void* elem, BinarySearchTree* bst);

int BSTInsert(BinarySearchTree* bst, void* elem) {
    if (bst->head) {
        return RecursiveInsert(bst->head, elem, bst);
    }

    bst->head = NewBSTNode(elem, bst->memb_size);
    return bst->head ? 0 : 1;
}

int RecursiveRemove(BSTNode* node, void* elem, Compare compare);

int BSTRemove(BinarySearchTree* bst, void* elem) {
    return RecursiveRemove(bst->head, elem, bst->compare);
}

BSTNode* BSTMin(BSTNode* root) {
    if (!root) {
        return root;
    }

    BSTNode* min = root;
    while (root->left) {
        min = root->left;
    }

    return min;
}

BSTNode* BSTMax(BSTNode* root) {
    if (!root) {
        return root;
    }

    BSTNode* max = root;
    while (root->right) {
        max = root->right;
    }

    return max;
}

void BSTInorderTraversal(BSTNode* root, BSTIterator iterator) {
    if (!root) {
        return;
    }

    BSTInorderTraversal(root->left, iterator);
    iterator(root);
    BSTInorderTraversal(root->right, iterator);
}

void BSTPreorderTraversal(BSTNode* root, BSTIterator iterator) {
    if (!root) {
        return;
    }

    iterator(root);
    BSTPreorderTraversal(root->left, iterator);
    BSTPreorderTraversal(root->right, iterator);
}

void BSTPostorderTraversal(BSTNode* root, BSTIterator iterator) {
    if (!root) {
        return;
    }

    BSTPostorderTraversal(root->left, iterator);
    BSTPostorderTraversal(root->right, iterator);
    iterator(root);
}

void BSTLevelTraversal(BSTNode* root, BSTIterator iterator) {
    if (!root) {
        return;
    }

    Vector vec_buf;
    Vector curr_level = NewVector(sizeof(BSTNode*), 1, CapacityDouble);
    Vector next_level = NewVector(sizeof(BSTNode*), 2, CapacityDouble);

    VectorAppend(&curr_level, &root);

    BSTNode* curr_node;
    while (curr_level.size > 0) {
        for (size_t i = 0; i < curr_level.size; i++) {
            VectorIndex(&curr_level, i, (void**)&curr_node);

            iterator(curr_node->value);

            if (curr_node->left) {
                VectorAppend(&next_level, &curr_node->left);
            }
            if (curr_node->right) {
                VectorAppend(&next_level, &curr_node->right);
            }
        }

        vec_buf = curr_level;
        curr_level = next_level;
        next_level = vec_buf;

        VectorClear(&next_level);
    }
}

BSTNode* RecursiveSearch(BSTNode* node, void* elem, Compare compare) {
    if (!node) {
        return NULL;
    }

    int8_t cmp = compare(elem, node->value);

    if (cmp < 0) {
        return RecursiveSearch(node->left, elem, compare);
    }
    if (cmp > 0) {
        return RecursiveSearch(node->right, elem, compare);
    }

    return node;
}

int RecursiveInsert(BSTNode* node, void* elem, BinarySearchTree* bst) {
    int8_t cmp = bst->compare(elem, node->value);

    if (cmp < 0) {
        if (node->left) {
            return RecursiveInsert(node->left, elem, bst);
        }
        node->left = NewBSTNode(elem, bst->memb_size);
        return node->left ? 0 : 1;
    }
    if (cmp > 0) {
        if (node->right) {
            return RecursiveInsert(node->right, elem, bst);
        }
        node->right = NewBSTNode(elem, bst->memb_size);
        return node->right ? 0 : 1;
    }

    return 1;
}

int RecursiveRemove(BSTNode* node, void* elem, Compare compare) {
    return 1;
    // TODO
    /*if (!node) {*/
    /*    return 1;*/
    /*}*/
    /**/
    /*int8_t cmp = compare(elem, node->value);*/
    /**/
    /*if (cmp < 0) {*/
    /*    return RecursiveRemove(node->left, elem, compare);*/
    /*}*/
    /*if (cmp > 0) {*/
    /*    return RecursiveRemove(node->right, elem, compare);*/
    /*}*/
    /**/
    /*BSTNode *l_child = node->left, *r_child = node->right;*/
    /**/
    /*if (!r_child) {*/
    /*    *node = *l_child;*/
    /*} else if (!l_child) {*/
    /*    *node = *r_child;*/
    /*} else {*/
    /*}*/
    /**/
    /*FreeBSTNode(node);*/
    /*return 0;*/
}
