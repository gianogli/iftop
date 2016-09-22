/*
 * sorted_list.c:
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "sorted_list.h"
#include "iftop.h"
#include <assert.h>

void limited_sorted_list_insert(sorted_list_type* list, void* item, int max_list_lenght) {
    sorted_list_node *node, *p;
    int i = 0;

    p = &(list->root);

    while (i < max_list_lenght && p->next != NULL && list->compare(item, p->next->data) > 0) {
        i++;
        p = p->next;
    }

    if (i < max_list_lenght) {
        node = xmalloc(sizeof *node);
        node->next = p->next;
        node->data = item;
        p->next = node;
        i++;
        p = node;
    }

    while (i < max_list_lenght && p->next != NULL) {
        i++;
        p = p->next;
    }

    if (p->next != NULL) {
        assert((p->next)->next == NULL);
        free(p->next);
        p->next = NULL;
    }
}


void sorted_list_insert(sorted_list_type* list, void* item) {
    sorted_list_node *node, *p;

    p = &(list->root);

    while(p->next != NULL && list->compare(item, p->next->data) > 0) {
        p = p->next;
    } 

    node = xmalloc(sizeof *node);

    node->next = p->next;
    node->data = item;
    p->next = node;
}

sorted_list_node* sorted_list_next_item(sorted_list_type* list, sorted_list_node* prev) {
    if(prev == NULL) {
        return list->root.next;
    }
    else {
        return prev->next;
    }
}

void sorted_list_destroy(sorted_list_type* list) {
    sorted_list_node *p, *n;
    p = list->root.next;

    while(p != NULL) {
        n = p->next;
        free(p);
        p = n;
    }

    list->root.next = NULL;
}

void sorted_list_initialise(sorted_list_type* list) {
    list->root.next = NULL;
}



