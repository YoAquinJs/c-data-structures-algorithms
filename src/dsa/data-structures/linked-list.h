#pragma once

#include <stddef.h>

typedef struct LinkedListNode {
    void* value;
    struct LinkedListNode* next;
} LinkedListNode;

void FreeLinkedListNode(LinkedListNode* node);

typedef struct LinkedList {
    size_t size;
    size_t memb_size;
    LinkedListNode* head;
} LinkedList;

LinkedList NewLinkedList(size_t memb_size);
void FreeLinkedList(LinkedList* list);

int LinkedListIndex(LinkedList list, size_t index, void* elem);
int LinkedListRemove(LinkedList* list, size_t index);
int LinkedListInsert(LinkedList* list, size_t index, void* elem);
void IterLinkedList(LinkedList list,
                    void (*Iterator)(size_t index, void* elem));
