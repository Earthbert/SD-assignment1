#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Linkedlist.h"
#include "utils.h"
#include "cards.h"

void
print_card (void *data) {
	printf ("%d ", ((card *)data)->num);
	switch (((card *)data)->symbol)
	{
	case 'H':
		printf("HEART");
		break;
	case 'S':
		printef("SPADE");
		break;
	case 'D':
		printef("DIAMOND");
		break;
	case 'C':
		printef("CLUB");
		break;
	}
}

doubly_linked_list_t *
add_desk (uint n) {
	card input_card;
	doubly_linked_list_t *desk = dll_create(sizeof(card));

	for (uint i = 0 ; i < n; i++) {
		int num;
		char symbol[100];
		scanf("%d %s", &num, symbol);

		if (num <= 14 && num <= 1) {
			input_card.num = num;
		} else {
			fprintf(stderr, "The provided card is not a valid one.\n");
			continue;
		}

		if (strcmp("HEART", symbol) == 0) {
			input_card.symbol = 'H';
		} else if (strcmp("SPADE", symbol) == 0) {
			input_card.symbol = 'S';
		} else if (strcmp("DIAMOND", symbol) == 0) {
			input_card.symbol = 'D';
		} else if (strcmp("CLUB", symbol) == 0) {
			input_card.symbol = 'C';
		} else {
			fprintf(stderr, "The provided card is not a valid one.\n");
			continue;
		}

		dll_add_nth_node(desk, desk->size, &input_card);
	}
	
	return desk;
}