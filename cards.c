// Copyright 2022 Daraban Albert-Timotei
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Linkedlist.h"
#include "utils.h"
#include "cards.h"

/* Printeaza datele specifice unei carti, de la adresa primita ca parametru.
*/
void
print_card(void *data) {
	printf("\t%d ", ((card *)data)->num);
	switch (((card *)data)->symbol)
	{
	case 4:
		printf("HEART\n");
		break;
	case 3:
		printf("SPADE\n");
		break;
	case 2:
		printf("DIAMOND\n");
		break;
	case 1:
		printf("CLUB\n");
		break;
	}
}

/* Adauga un numar de carti la un pachet, luate din stdin.
*/
void
add_cards(doubly_linked_list_t *deck, uint nr_cards) {
	card input_card;
	int num = 0;
	char line[MAX_STRING_SIZE];
	char *word;

	for (uint i = 0 ; i < nr_cards;) {
		fgets(line, MAX_STRING_SIZE, stdin);
		word = strtok(line, " ");
		num = atoi(word);
		word = strtok(NULL, " ");

		if (num <= 14 && num >= 1) {
			input_card.num = num;
		} else {
			INVALID_CARD
			continue;
		}

		word[strlen(word) - 1] = '\0';

		if (strcmp("HEART", word) == 0) {
			input_card.symbol = 4;
		} else if (strcmp("SPADE", word) == 0) {
			input_card.symbol = 3;
		} else if (strcmp("DIAMOND", word) == 0) {
			input_card.symbol = 2;
		} else if (strcmp("CLUB", word) == 0) {
			input_card.symbol = 1;
		} else {
			INVALID_CARD
			continue;
		}
		i++;
		dll_add_nth_node(deck, deck->size, &input_card);
	}
}

/* Sterge o carte dintr-un pachet, si daca pachetul devine gol il stege si pe
el.
*/
int
del_card(doubly_linked_list_t *deck_list, uint deck_index, uint card_index) {
	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return 1;
	}
	doubly_linked_list_t *deck = dll_get_nth_node(deck_list, deck_index)->data;

	if (card_index >= deck->size) {
		CARD_INDEX_OUT_OF_BOUNDS(deck_index)
		return 1;
	}

	dll_node_t *removed_node = dll_remove_nth_node(deck, card_index);
	free(removed_node->data);
	free(removed_node);

	if (deck->size == 0) {
		removed_node = dll_remove_nth_node(deck_list, deck_index);
		dll_free(removed_node->data);
		free(removed_node->data);
		free(removed_node);
	}
	return 0;
}

/* Amesteca un pachet, duce prima a doua jumatate la incepul.
*/
void
shuffle_deck(doubly_linked_list_t *deck) {
	dll_node_t *first = deck->head;
	dll_node_t *mid = dll_get_nth_node(deck, deck->size / 2);
	dll_node_t *last = dll_get_nth_node(deck, deck->size - 1);

	deck->head = mid;
	first->prev = last;
	last->next = first;
	if (mid->prev)
		mid->prev->next = NULL;
	mid->prev = NULL;
}

// Amesteca doua pachete, apeland functia merge_list
void
merge_decks(doubly_linked_list_t *deck_list, uint index1, uint index2) {
	if (index1 >= deck_list->size || index2 >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}

	dll_node_t *node1 = dll_remove_nth_node(deck_list, index1);
	if (index1 < index2)
		index2--;

	dll_node_t *node2 = dll_remove_nth_node(deck_list, index2);
	doubly_linked_list_t *deck1 = (doubly_linked_list_t *)node1->data;
	doubly_linked_list_t *deck2 = (doubly_linked_list_t *)node2->data;

	doubly_linked_list_t *new_deck = dll_merge_lists(deck1, deck2);
	dll_free(deck1);
	free(deck1);
	dll_free(deck2);
	free(deck2);

	free(node1);
	free(node2);

	dll_add_nth_node(deck_list, deck_list->size, new_deck);
	/* Eliberez pentru ca functia dll_add_nth_node aloca si ea memorie pentru
	new_deck.
	*/
	free(new_deck);
}

/* Compara doua carti, nu stiu de ce returneaza card2.symbol - card1.symbol
si nu invers, dar doar asa trec testele.
*/ 
int
compare_cards(void *p_card1, void *p_card2) {
	card card1 = *(card *)p_card1;
	card card2 = *(card *)p_card2;

	if (card1.num != card2.num)
		return card1.num - card2.num;

	if (card1.symbol != card2.symbol)
		return card2.symbol - card1.symbol;

	return 0;
}

/* Imparte un pachet in doua incepand cu split_index
*/
int
split_deck(doubly_linked_list_t *deck_list,
	uint deck_index, uint split_index) {
	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return 1;
	}
	doubly_linked_list_t *deck_split = dll_get_nth_node(deck_list,
	deck_index)->data;

	if (split_index >= deck_split->size) {
		CARD_INDEX_OUT_OF_BOUNDS(deck_index)
		return 1;
	}

	if (split_index == 0)
		return 0;

	doubly_linked_list_t *new_deck = dll_create(sizeof(card));

	dll_node_t *node = dll_get_nth_node(deck_split, split_index);

	if (node->prev)
		node->prev->next = NULL;
	node->prev = NULL;
	new_deck->head = node;
	if (node->prev)
		(node->prev)->next = NULL;

	new_deck->size = deck_split->size - split_index;
	deck_split->size = split_index;

	dll_add_nth_node(deck_list, deck_index + 1, new_deck);
	/* Eliberez pentru ca functia dll_add_nth_node aloca si ea memorie pentru
	new_deck.
	*/
	free(new_deck);
	return 0;
}
