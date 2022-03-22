#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Linkedlist.h"
#include "utils.h"
// #include "cards.h"

int main () {
	uint n;
	printf("Add n elements\n");
	scanf("%d", &n);
	doubly_linked_list_t *list = dll_create(sizeof(int));
	for (uint i = 0; i < n; i++) {
		int a, pos;
		printf("Value:\n");
		scanf("%d", &a);
		printf("Position:\n");
		scanf("%d", &pos);
		dll_add_nth_node(list, pos, &a);
	}

	printf("Remove n elements\n");
	scanf("%d", &n);
	for (uint i = 0; i < n; i++) {
		int pos;
		printf("Position:\n");
		scanf("%d", &pos);
		dll_node_t *node = dll_remove_nth_node(list, pos);
		free(node->data);
		free(node);
	}

	dll_node_t *node = list->head;
	while(node) {
		printf("%d ", *(int *)(node->data));
		node = node->next;
	}

	dll_free(&list);
	return 0;
}