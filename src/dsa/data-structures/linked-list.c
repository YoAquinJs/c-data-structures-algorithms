#include "linked-list.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void FreeLinkedListNode(LinkedListNode* node) {
    free(node->value);
    free(node);
}
LinkedList NewLinkedList(size_t memb_size) {
    return (LinkedList){0, memb_size, NULL};
}

void FreeLinkedList(LinkedList* list) {
    LinkedListNode* buf;

    while (list->head) {
        buf = list->head;
        list->head = list->head->next;
        FreeLinkedListNode(buf);
    }
}

int LinkedListIndex(LinkedList list, size_t index, void* elem) {
    if (index >= list.size) {
        return 1;
    }

    LinkedListNode* node = list.head;
    while (0 < index--) {
        node = node->next;
    }

    elem = node->value;
    return 0;
}

int LinkedListRemove(LinkedList* list, size_t index) {
    if (index >= list->size) {
        return 1;
    }

    LinkedListNode* buf;
    if (index == 0) {
        buf = list->head;
        list->head = buf->next;
        FreeLinkedListNode(buf);

        list->size--;
        return 0;
    }

    LinkedListNode* node = list->head;
    while (0 < --index) {
        node = node->next;
    }

    buf = node->next;
    node->next = buf->next;
    FreeLinkedListNode(buf);

    list->size--;
    return 0;
}

int LinkedListInsert(LinkedList* list, size_t index, void* elem) {
    if (index > list->size) {
        return 1;
    }

    LinkedListNode* insert_node = malloc(sizeof(LinkedListNode));
    if (!insert_node) {
        return 1;
    }
    insert_node->value = malloc(list->memb_size);
    if (!insert_node->value) {
        return 1;
    }
    memcpy(insert_node->value, elem, list->memb_size);

    if (index == 0) {
        insert_node->next = list->head;
        list->head = insert_node;

        list->size++;
        return 0;
    }

    LinkedListNode* prev_node = list->head;
    while (0 < --index) {
        prev_node = prev_node->next;
    }

    insert_node->next = prev_node->next;
    prev_node->next = insert_node;

    list->size++;
    return 0;
}

void IterLinkedList(LinkedList list,
                    void (*Iterator)(size_t index, void* elem)) {
    LinkedListNode* node = list.head;
    for (size_t index = 0; index < list.size; index++) {
        Iterator(index, node->value);
        node = node->next;
    }
}
