#include <stdlib.h>
#include <stdio.h>
#include "mem.h"
#include "list.h"

struct list *list_new() {
    struct list *l = getcmem(sizeof(struct list));
    l->size = 0;
    return l;
}

void list_add(struct list *l, void *ptr) {
    struct node *newnode = getcmem(sizeof(struct node));
    newnode->data = ptr;

    if(l->head == NULL) {
        l->head = newnode;
        l->tail = newnode;
    } else {
        struct node *lastnode = l->tail;
        lastnode->next = newnode;
        newnode->prev = lastnode;
        l->tail = newnode;
    }

    l->size++;
}

void *list_get_idx(struct list *l, size_t idx) {
    size_t count = 0;
    struct node *curr = l->head;
    while(count < idx) {
        if(curr->next == NULL)
            break;
        curr = curr->next;
        count++;
    }
    return curr->data;
}

void list_rem_idx(struct list *l, size_t idx) {
    size_t count = 0;
    struct node *curr = l->head;
    while(count < idx) {
        curr = curr->next;
        count++;
    }

    struct node *prev = NULL;
    if(curr->prev != NULL) {
        prev = curr->prev;
    }

    struct node *next = NULL;
    if(curr->next != NULL) {
        next = curr->next;
    }

    prev->next = next;
    l->size--;

    free(curr);
}
