#ifndef LINKEDLIST_H
#define LINKEDLIST_H

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
dll_make_node(dll_node_t *next, dll_node_t *prev, const void *data, uint data_size);

dll_node_t*
dll_get_nth_node(doubly_linked_list_t* list, uint n);

void
dll_add_nth_node(doubly_linked_list_t* list, uint n, const void* data);

dll_node_t*
dll_remove_nth_node(doubly_linked_list_t* list, uint n);

uint
dll_get_size(doubly_linked_list_t* list);

void
dll_free(doubly_linked_list_t** pp_list);

#endif // LINKEDLIST_H