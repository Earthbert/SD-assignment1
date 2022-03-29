// Copyright 2022 Daraban Albert-Timotei
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Linkedlist.h"
#include "utils.h"

/* Creaza o lista dublu inlantuita
*/
doubly_linked_list_t*
dll_create(uint data_size)
{
    doubly_linked_list_t *list = calloc(1, sizeof(doubly_linked_list_t));
    DIE(!list, "malloc error");
    list->data_size = data_size;
    return list;
}

/* Returneaza al n-elea nod
*/
dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, uint n)
{
    DIE(!list, "List uninitialized\n");

    if (n >= list->size) {
        fprintf(stderr, "Node doesn't exist\n");
        return NULL;
    }

    dll_node_t *node = list->head;
    for (uint i = 0; i < n; i++) {
        node = node->next;
    }

    return node;
}

/* Creaza nodul proriu zis
*/
dll_node_t*
dll_make_node(dll_node_t *next, dll_node_t *prev, const void *data,
uint data_size) {
    dll_node_t *node = calloc(1, sizeof(dll_node_t));
    DIE(!node, "malloc error");

    node->next = next;
    node->prev = prev;
    node->data = calloc(1, data_size);
    DIE(!node->data, "malloc error\n");

    memcpy(node->data, data, data_size);

    return node;
}

/* Adauga un nod, alocand si memorie pentru el si datele retinute.
*/
void
dll_add_nth_node(doubly_linked_list_t* list, uint n, const void* data)
{
    DIE(!list, "List uninitialized\n");

    if (n > list->size)
        n = list->size;

    if (n == 0) {
        if (!list->head) {
            dll_node_t *new_node = dll_make_node(NULL, NULL, data,
            list->data_size);
            list->size++;
            list->head = new_node;
            return;
        }
        dll_node_t *node = list->head;
        dll_node_t *new_node = dll_make_node(node, node->prev, data,
        list->data_size);

        list->size++;
        list->head = new_node;
        return;
    }

    dll_node_t *prev_node =  dll_get_nth_node(list, n - 1);
    dll_node_t *new_node = dll_make_node(prev_node->next, prev_node, data,
    list->data_size);

    if (prev_node->next)
        (prev_node->next)->prev = new_node;
    if (prev_node)
        prev_node->next = new_node;
    list->size++;
}

/* Elimina un nod fara a elibera memorie
*/
dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, uint n)
{
    DIE(!list, "List uninitialized\n");

    if (list->size == 0) {
        fprintf(stderr, "List is empty\n");
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

/* Gaseste marimea unei liste prin parcurgerea ei
*/
uint
dll_get_size(doubly_linked_list_t* list)
{
    DIE(!list, "List uninitialized\n");

    dll_node_t *node = (list->head)->next;
    uint i = 1;
    while (node) {
        node = node->next;
        i++;
    }
    return i;
}

/* Elibereaza memoria elementelor unei liste, nu si lista.
*/
void
dll_free(doubly_linked_list_t* list)
{
    DIE(!(list), "List uninitialized\n");

    dll_node_t *node = list->head;
    for (uint i = 0; i < list->size; i++) {
        dll_node_t *tmp = node;
        node = node->next;
        free(tmp->data);
        free(tmp);
        tmp = NULL;
    }
}

/* Printeaza valorile listei intre pozitile a si b, apeland o functie de printare.
*/
void
dll_print_element(doubly_linked_list_t *list, uint a, uint b,
void print_func(void *)) {
    DIE(!list, "List uninitialized\n");

    dll_node_t *node = dll_get_nth_node(list, a);

    for (uint i = a; i <= b && node != NULL; i++) {
        print_func(node->data);
        node = node->next;
    }
}

/* Creaza o noua lista luand cate o carte pe rand din listele date ca
parametri.
*/
doubly_linked_list_t *
dll_merge_lists(doubly_linked_list_t *list1, doubly_linked_list_t *list2) {
    DIE(!list1, "List uninitialized\n");
    DIE(!list2, "List uninitialized\n");

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

/* Inverseaza ordinea nodurilor din list
*/
void
dll_reverse_list(doubly_linked_list_t *list) {
    DIE(!list, "List uninitialized\n");

    dll_node_t *node = list->head;

    while (node) {
        if (node->next == NULL) {
            list->head = node;
        }
        SWAP(node->next, node->prev, dll_node_t *);
        node = node->prev;
    }
}

/* Sorteaza o lista, utilizand bubble sort, cu ajutorul functiei compare_func
*/
void
dll_sort_list(doubly_linked_list_t *list, int compare_func(void *, void *)) {
    DIE(!list, "List uninitialized\n");

    dll_node_t *node = list->head;
    while (node != NULL && node->next != NULL) {
        if (compare_func(node->data, node->next->data) > 0) {
            SWAP(node->data, node->next->data, dll_node_t*);
            if (node->prev)
                node = node->prev;
        } else {
            node = node->next;
        }
    }
}
