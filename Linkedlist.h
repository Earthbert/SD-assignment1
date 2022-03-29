// Copyright 2022 Daraban Albert-Timotei
#ifndef CHECKER_LINKEDLIST_H_
#define CHECKER_LINKEDLIST_H_

typedef unsigned int uint;

typedef struct dll_node_t dll_node_t;
struct dll_node_t
{
	void *data;
	dll_node_t *next, *prev;
};

typedef struct doubly_linked_list_t
{
	dll_node_t *head;
	uint data_size;
	uint size;
} doubly_linked_list_t;

// Functions for linkedlist implementation

doubly_linked_list_t*
dll_create(uint data_size);

dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, uint n);

void
dll_add_nth_node(doubly_linked_list_t* list, uint n, const void* data);

dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, uint n);

uint
dll_get_size(doubly_linked_list_t* list);

void
dll_free(doubly_linked_list_t* pp_list);

void
dll_print_element(doubly_linked_list_t *list, uint a, uint b,
void print_func(void *));

doubly_linked_list_t*
dll_merge_lists(doubly_linked_list_t *list1, doubly_linked_list_t *list2);

void
dll_reverse_list(doubly_linked_list_t *list);

void
dll_sort_list(doubly_linked_list_t *list, int compare_func(void *, void *));

#endif  // CHECKER_LINKEDLIST_H_
