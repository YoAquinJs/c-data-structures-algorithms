#include "binary-search-tree.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
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

    node->value = (void*)node + sizeof(BSTNode);

    memcpy(node->value, value, size);
    return node;
}

void FreeBSTNode(BSTNode* node) {
    free(node);
}

BinarySearchTree NewBinarySearchTree(size_t memb_size, Compare compare) {
    return (BinarySearchTree){memb_size, compare, NULL};
}
void FreeBinarySearchTreeRecursive(BSTNode* root) {
    if (!root) {
        return;
    }

    FreeBinarySearchTreeRecursive(root->left);
    FreeBinarySearchTreeRecursive(root->right);
    FreeBSTNode(root);
}
void FreeBinarySearchTree(BinarySearchTree* bst) {
    FreeBinarySearchTreeRecursive(bst->head);
    bst->head = NULL;
}

BSTNode* RecursiveSearch(BSTNode* node, void* elem, Compare compare);

BSTNode* BSTSearch(BinarySearchTree* bst, void* elem) {
    BSTNode* node = bst->head;

    while (node) {
        int8_t cmp = bst->compare(elem, node->value);

        if (cmp == 0) {
            return node;
        }

        node = cmp > 0 ? node->right : node->left;
    }

    return NULL;
}

int BSTSearchParent(BinarySearchTree* bst, void* elem, BSTNode** parent,
                    BSTNode*** node_ptr_ref) {
    BSTNode* node = bst->head;
    int8_t cmp = bst->compare(elem, node->value);
    if (cmp == 0) {
        if (node_ptr_ref) *node_ptr_ref = &bst->head;
        return 2;
    }

    while (node) {
        if (cmp < 0) {
            if (!node->left) {
                return 1;
            }
            if (bst->compare(elem, node->left->value) == 0) {
                if (parent) *parent = node;
                if (node_ptr_ref) *node_ptr_ref = &node->left;
                break;
            }

            node = node->left;
        } else {
            if (!node->right) {
                return 1;
            }
            if (bst->compare(elem, node->right->value) == 0) {
                if (parent) *parent = node;
                if (node_ptr_ref) *node_ptr_ref = &node->right;
                break;
            }

            node = node->right;
        }

        cmp = bst->compare(elem, node->value);
    }

    return 0;
}

int RecursiveInsert(BSTNode* node, void* elem, BinarySearchTree* bst);

int BSTInsert(BinarySearchTree* bst, void* elem) {
    if (!bst->head) {
        bst->head = NewBSTNode(elem, bst->memb_size);
        return bst->head ? 0 : 1;
    }

    BSTNode* node = bst->head;

    while (node) {
        int8_t cmp = bst->compare(elem, node->value);

        if (cmp < 0) {
            if (!node->left) {
                node->left = NewBSTNode(elem, bst->memb_size);
                return node->left ? 0 : 1;
            }
            node = node->left;
        } else if (cmp > 0) {
            if (!node->right) {
                node->right = NewBSTNode(elem, bst->memb_size);
                return node->right ? 0 : 1;
            }
            node = node->right;
        } else {
            break;
        }
    }

    return 1;
}

BSTNode* RecursiveRemove(BSTNode* parent, void* elem, size_t memb_size,
                         Compare compare);

int BSTRemove(BinarySearchTree* bst, void* elem) {
    BSTNode** node_ptr_ref;
    int search_st = BSTSearchParent(bst, elem, NULL, &node_ptr_ref);

    if (search_st == 1) {
        return 1;
    }

    BSTNode* node = *node_ptr_ref;

    if (!node->left) {
        *node_ptr_ref = node->right;
    } else if (!node->right) {
        *node_ptr_ref = node->left;
    } else {
        BSTNode *successor = BSTMin(node->right), **successor_ptr_ref;
        if (successor != node->right) {
            BSTSearchParent(bst, successor->value, NULL, &successor_ptr_ref);
            *successor_ptr_ref = successor->right;
            successor->right = node->right;
        }
        successor->left = node->left;
        *node_ptr_ref = successor;
    }

    FreeBSTNode(node);
    return 0;
}

BSTNode* BSTMin(BSTNode* root) {
    if (!root) {
        return root;
    }

    while (root->left) {
        root = root->left;
    }

    return root;
}

BSTNode* BSTMax(BSTNode* root) {
    if (!root) {
        return root;
    }

    while (root->right) {
        root = root->right;
    }

    return root;
}

void BSTInorderTraversal(BSTNode* root, BSTIterator iterator) {
    if (!root) {
        return;
    }

    BSTInorderTraversal(root->left, iterator);
    iterator(root->value);
    BSTInorderTraversal(root->right, iterator);
}

void BSTPreorderTraversal(BSTNode* root, BSTIterator iterator) {
    if (!root) {
        return;
    }

    iterator(root->value);
    BSTPreorderTraversal(root->left, iterator);
    BSTPreorderTraversal(root->right, iterator);
}

void BSTPostorderTraversal(BSTNode* root, BSTIterator iterator) {
    if (!root) {
        return;
    }

    BSTPostorderTraversal(root->left, iterator);
    BSTPostorderTraversal(root->right, iterator);
    iterator(root->value);
}

void BSTLevelTraversal(BSTNode* root, BSTIterator iterator,
                       void (*OnNewLevel)(void)) {
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
            curr_node = ((BSTNode**)curr_level.buffer)[i];
            if (iterator) {
                iterator(curr_node->value);
            }

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

        if (OnNewLevel && next_level.size > 0) {
            OnNewLevel();
        }

        VectorClear(&next_level);
    }

    FreeVector(&curr_level);
    FreeVector(&next_level);
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

BSTNode* RecursiveRemove(BSTNode* node, void* elem, size_t memb_size,
                         Compare compare) {
    if (!node) {
        return node;
    }

    int8_t cmp = compare(elem, node->value);

    if (cmp < 0) {
        node->left = RecursiveRemove(node->left, elem, memb_size, compare);
    } else if (cmp > 0) {
        node->right = RecursiveRemove(node->right, elem, memb_size, compare);
    } else {
        BSTNode* successor;
        if (!node->left) {
            successor = node->right;
            FreeBSTNode(node);
            return successor;
        }

        if (!node->right) {
            successor = node->left;
            FreeBSTNode(node);
            return successor;
        }

        successor = BSTMin(node);
        memcpy(node->value, successor->value, memb_size);
        node->right =
            RecursiveRemove(node->right, successor->value, memb_size, compare);
    }

    return node;
}
