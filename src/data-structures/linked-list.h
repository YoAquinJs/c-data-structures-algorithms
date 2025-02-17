#pragma once

#include <stddef.h>

typedef void (*LinkedListIterator)(size_t index, void* elem);

typedef struct LinkedListNode {
    void* value;
    struct LinkedListNode* next;
} LinkedListNode;

LinkedListNode* NewLinkedListNode(void* value, size_t size);
void FreeLinkedListNode(LinkedListNode* node);

typedef struct LinkedList {
    size_t size;
    size_t memb_size;
    LinkedListNode* head;
} LinkedList;

LinkedList NewLinkedList(size_t memb_size);
void FreeLinkedList(LinkedList* list);

LinkedListNode* LinkedListIndex(LinkedList* list, size_t index);
int LinkedListRemove(LinkedList* list, size_t index);
int LinkedListInsert(LinkedList* list, size_t index, void* elem);
// iter from start to end (end non inclusive), fail on attempted reverse
// iteration
int IterLinkedList(LinkedList* list, size_t start, size_t end,
                   LinkedListIterator iterator);
