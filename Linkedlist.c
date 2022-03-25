#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Linkedlist.h"
#include "utils.h"

doubly_linked_list_t*
dll_create(uint data_size)
{
    doubly_linked_list_t *list = calloc(1, sizeof(doubly_linked_list_t));
    DIE(!list, "malloc error");
    list->data_size = data_size;
    return list;
}

dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, uint n)
{
    DIE(!list, "List uninitialized");

    if (n >= list->size) {
        fprintf(stderr, "Node doesn't exist");
        return NULL;
    }

    dll_node_t *node = list->head;
    for (uint i = 0; i < n; i++) {
        node = node->next;
    }

    return node;
}

dll_node_t*
dll_make_node(dll_node_t *next, dll_node_t *prev, const void *data, uint data_size) {
    dll_node_t *node = calloc(1, sizeof(dll_node_t));
    DIE(!node, "malloc error");

    node->next = next;
    node->prev = prev;
    node->data = calloc(1, data_size);
    DIE(!node->data, "malloc error");

    memcpy(node->data, data, data_size);

    return node;
}

void
dll_add_nth_node(doubly_linked_list_t* list, uint n, const void* data)
{
    DIE(!list, "List uninitialized");

    if (n > list->size)
        n = list->size;
    
    if (n == 0) {
        if (!list->head) {
            dll_node_t *new_node = dll_make_node(NULL, NULL, data, list->data_size);
            list->size++;
            list->head = new_node;
            return;
        }
        dll_node_t *node = list->head;
        dll_node_t *new_node = dll_make_node(node, node->prev, data, list->data_size);
        list->size++;
        list->head = new_node;
        return;
    }

    dll_node_t *prev_node =  dll_get_nth_node(list, n - 1);
    dll_node_t *new_node = dll_make_node(prev_node->next, prev_node, data, list->data_size);
    if (prev_node->next)
        (prev_node->next)->prev = new_node;
    if (prev_node)
        prev_node->next = new_node;
    list->size++;
}

dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, uint n)
{
    DIE(!list, "List uninitialized");

    if (list->size == 0) {
        fprintf(stderr, "List is empty");
        return NULL;
    }
    if (list->size == 1) {
        dll_node_t *node = list->head;
        list->size--;
        list->head = NULL;
        return node;
    }
    if (n >= list->size)
        n = list->size - 1;
    
    dll_node_t *node = dll_get_nth_node(list, n);
    if (node->prev)
        (node->prev)->next = node->next;
    if (node->next)
        (node->next)->prev = node->prev;

    if (n == 0)
        list->head = node->next;
    list->size--;

    return node;
}

uint
dll_get_size(doubly_linked_list_t* list)
{
    DIE(!list, "List uninitialized");

    dll_node_t *node = (list->head)->next;
    uint i = 1;
    while (node) {
        node = node->next;
        i++;
    }
    return i;
}

void
dll_free(doubly_linked_list_t* list)
{
    DIE(!(list), "List uninitialized");

    dll_node_t *node = list->head;
    for (uint i = 0; i < list->size; i++) {
        dll_node_t *tmp = node;
        node = node->next;
        free(tmp->data);
        free(tmp);
        tmp = NULL;
    }
}

// Prints the values from node a to node b, using given function
void
dll_print_element(doubly_linked_list_t *list, uint a, uint b, void print_func(void *)) {
    DIE(!list, "List uninitialized");

    dll_node_t *node = dll_get_nth_node(list, a);

    for (uint i = a; i <= b && node != NULL; i++) {
        print_func(node->data);
        node = node->next;
    }
}

doubly_linked_list_t *
dll_merge_lists(doubly_linked_list_t *list1, doubly_linked_list_t *list2) {
    DIE(!list1, "List uninitialized");
    DIE(!list2, "List uninitialized");

    doubly_linked_list_t *new_list = dll_create(list1->data_size);

    dll_node_t *node1 = list1->head;
    dll_node_t *node2 = list2->head;
    
    for (uint i = 0; node1 || node2; i++) {
        if (i % 2 == 0 && node1) {
            dll_add_nth_node(new_list, list1->size + list2->size, node1->data);
            node1 = node1->next;
        }
        if (i % 2 == 1 && node2) {
            dll_add_nth_node(new_list, list1->size + list2->size, node2->data);
            node2 = node2->next;
        }
    }

    return new_list;
}

void
dll_reverse_list(doubly_linked_list_t *list) {
    DIE(!list, "List uninitialized");

    dll_node_t *node = list->head;

    while (node) {
        if (node->next == NULL) {
            list->head = node;
        }
        SWAP(node->next, node->prev, dll_node_t *);
        node = node->prev;
    }
}

void
dll_sort_list(doubly_linked_list_t *list, int compare_func(void *, void *)) {
    DIE(!list, "List uninitialized");

    dll_node_t *node = list->head;
    while (node != NULL && node->next != NULL) {
        if (compare_func(node->data, node->next->data) < 0) {
            SWAP(node->data, node->next->data, dll_node_t*);
            if (node->prev)
                node = node->prev;
        } else {
                node = node->next;
        }
    }
}