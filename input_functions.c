#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Linkedlist.h"
#include "utils.h"
#include "cards.h"
#include "input_functions.h"

int word_count(char *line)
{
	unsigned int count = 0;

	for (int i = 0; i < (int)strlen(line); i++) {
		if (line[i] != ' ' && line[i] != '\n') {
			while (i < (int)strlen(line) && line[i] != ' ' && line[i] != '\n')
				i++;
			count++;
		}
	}
	return count;
}

void add_deck_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char *word;
	uint nr_cards;

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 1) {
		INVALID_COMMAND
		return;
	}
	word = strtok(line, " ");
	nr_cards = atoi(word);


	doubly_linked_list_t deck;
	deck.data_size = sizeof(card);
	deck.head = NULL;
	deck.size = 0;
	add_cards(&deck, nr_cards);
	dll_add_nth_node(deck_list, deck_list->size, &deck);
	printf("The deck was successfully created with %d cards.\n", deck.size);
}

void delete_deck_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char *word;
	uint deck_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 1) {
		INVALID_COMMAND;
		return;
	}

	word = strtok(line, " ");
	deck_index = atoi(word);

	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}
	dll_node_t *removed_node = dll_remove_nth_node(deck_list, deck_index);
	dll_free((doubly_linked_list_t *)removed_node->data);
	free(removed_node->data);
	free(removed_node);
	printf("The deck %d was successfully deleted.\n", deck_index);
}

void delete_card_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char *word;
	uint deck_index, card_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 2) {
		INVALID_COMMAND;
		return;
	}
	
	word = strtok(line, " ");
	deck_index = atoi(word);
	word = strtok(NULL, " ");
	card_index = atoi(word);

	int ret_val = del_card(deck_list, deck_index, card_index);
	if (ret_val == 0)
		printf("The card was successfully deleted from deck %d.\n", deck_index);
}

void add_cards_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char *word;
	uint deck_index, nr_cards;

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 2) {
		INVALID_COMMAND
		return;
	}
	word = strtok(line, " ");
	deck_index = atoi(word);
	word = strtok(NULL, " ");
	nr_cards = atoi(word);

	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}
	doubly_linked_list_t *deck = dll_get_nth_node(deck_list, deck_index)->data;
	add_cards(deck, nr_cards);
	printf("The cards were successfully added to deck %d.\n", deck_index);
}

void deck_len(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char *word;
	uint deck_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 1) {
		INVALID_COMMAND;
		return;
	}

	word = strtok(line, " ");
	deck_index = atoi(word);

	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}
	doubly_linked_list_t *deck = dll_get_nth_node(deck_list, deck_index)->data;
	printf("The length of deck %d is %d.\n", deck_index, deck->size);
}

void shuffle_deck_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char *word;
	uint deck_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 1) {
		INVALID_COMMAND;
		return;
	}

	word = strtok(line, " ");
	deck_index = atoi(word);

	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}
	doubly_linked_list_t *deck = dll_get_nth_node(deck_list, deck_index)->data;
	shuffle_deck(deck);
	printf("The deck %d was successfully shuffled.\n", deck_index);
}

void merge_decks_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char *word;
	uint deck_index_1, deck_index_2;

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 2) {
		INVALID_COMMAND
		return;
	}
	word = strtok(line, " ");
	deck_index_1 = atoi(word);
	word = strtok(NULL, " ");
	deck_index_2 = atoi(word);

	if (deck_index_1 >= deck_list->size || deck_index_2 >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}
	merge_decks(deck_list, deck_index_1, deck_index_2);
	printf("The deck %d and the deck %d were successfully merged.\n", deck_index_1, deck_index_2);
}

void split_deck_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char *word;
	uint deck_index, split_index;
	
	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 2) {
		INVALID_COMMAND
		return;
	}
	word = strtok(line, " ");
	deck_index = atoi(word);
	word = strtok(NULL, " ");
	split_index = atoi(word);

	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}
	int ret_val = split_deck(deck_list, deck_index, split_index);
	if (ret_val == 0)
		printf("The deck %d was successfully split by index %d.\n", deck_index, split_index);
}

void reverse_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char *word;
	uint deck_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 1) {
		INVALID_COMMAND
		return;
	}
	word = strtok(line, " ");
	deck_index = atoi(word);

	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}

	doubly_linked_list_t *deck = dll_get_nth_node(deck_list, deck_index)->data;
	dll_reverse_list(deck);
	printf("The deck %d was successfully reversed.\n", deck_index);
}

void show_deck_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char *word;
	uint deck_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 1) {
		INVALID_COMMAND
		return;
	}
	word = strtok(line, " ");
	deck_index = atoi(word);

	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}

	doubly_linked_list_t *deck = dll_get_nth_node(deck_list, deck_index)->data;
	printf("Deck %d:\n", deck_index);
	dll_print_element(deck, 0, deck->size, &print_card);
}

void show_all_decks(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 0) {
		INVALID_COMMAND
		return;
	}

	dll_node_t *deck_node = deck_list->head;
	for(uint i = 0; i < deck_list->size; i++) {
		doubly_linked_list_t *deck = deck_node->data;
		printf("Deck %d:\n", i);
		dll_print_element(deck, 0, deck->size, &print_card);
		deck_node = deck_node->next;
	}
}

void sort_deck_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char *word;
	uint deck_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 1) {
		INVALID_COMMAND
		return;
	}
	word = strtok(line, " ");
	deck_index = atoi(word);

	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}

	doubly_linked_list_t *deck = dll_get_nth_node(deck_list, deck_index)->data;
	dll_sort_list(deck, &compare_cards);
	printf("The deck %d was successfully sorted.\n", deck_index);
}

void deck_number(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 0) {
		INVALID_COMMAND
		return;
	}
	printf("The number of decks is %d.\n", deck_list->size);
}

void exit_program(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];

	fgets(line, MAX_STRING_SIZE, stdin);
	if (word_count(line) != 0) {
		INVALID_COMMAND
		return;
	}

	dll_node_t *deck_node = NULL;
	if (deck_list->head)
		deck_node = deck_list->head;
	for (uint i = 0; i < deck_list->size; i++) {
		doubly_linked_list_t *deck = deck_node->data;
		dll_free(deck);
		deck_node = deck_node->next;
	}
	dll_free(deck_list);
	free(deck_list);
}