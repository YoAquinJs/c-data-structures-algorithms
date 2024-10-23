#include "linked-list.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

LinkedListNode* NewLinkedListNode(void* value, size_t size) {
    LinkedListNode* node = malloc(sizeof(LinkedListNode) + size);
    if (!node) {
        return NULL;
    }
    node->next = NULL;

    node->value = (void*)(node + sizeof(LinkedListNode));

    memcpy(node->value, value, size);
    return node;
}

void FreeLinkedListNode(LinkedListNode* node) {
    free(node);
}

LinkedList NewLinkedList(size_t memb_size) {
    return (LinkedList){0, memb_size, NULL};
}

void FreeLinkedList(LinkedList* list) {
    LinkedListNode* buffer;

    while (list->head) {
        buffer = list->head;
        list->head = list->head->next;
        FreeLinkedListNode(buffer);
    }
}

LinkedListNode* LinkedListIndex(LinkedList* list, size_t index) {
    if (index >= list->size) {
        return NULL;
    }

    LinkedListNode* node = list->head;
    while (0 < index--) {
        node = node->next;
    }

    return node;
}

int LinkedListRemove(LinkedList* list, size_t index) {
    LinkedListNode* buffer;

    if (index == 0) {
        buffer = list->head;
        list->head = buffer->next;
        FreeLinkedListNode(buffer);

        list->size--;
        return 0;
    }

    LinkedListNode* prev_node;
    if (index == list->size ||
        !(prev_node = LinkedListIndex(list, index - 1))) {
        return 1;
    }

    buffer = prev_node->next;
    prev_node->next = buffer->next;
    FreeLinkedListNode(buffer);

    list->size--;
    return 0;
}

int LinkedListInsert(LinkedList* list, size_t index, void* elem) {
    LinkedListNode* prev_node;
    if (index == 0) {
        prev_node = list->head;
    } else if (!(prev_node = LinkedListIndex(list, index - 1))) {
        return 1;
    }

    LinkedListNode* insert_node = NewLinkedListNode(elem, list->memb_size);

    if (index == 0) {
        insert_node->next = list->head;
        list->head = insert_node;

        list->size++;
        return 0;
    }

    insert_node->next = prev_node->next;
    prev_node->next = insert_node;

    list->size++;
    return 0;
}

int IterLinkedList(LinkedList* list, size_t start, size_t end,
                   LinkedListIterator iterator) {
    LinkedListNode* node;
    if (end > list->size || start >= end ||
        !(node = LinkedListIndex(list, start))) {
        return 1;
    }

    for (; start < end; start++) {
        iterator(start, node->value);
        node = node->next;
    }

    return 0;
}
