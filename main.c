#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Linkedlist.h"
#include "utils.h"
#include "cards.h"

void find_nth_word(char *word, char *line, int n) {
    char *start;
    char *end;
    int i = 0;
    while (n) {
        start = NULL;
        end = NULL;
        while (i < (int)strlen(line) && !end) {
            if (line[i] != ' ' && !start) {
                start = &line[i];
            } else if (line[i + 1] == ' ' || line[i + 1] == '\0') {
                end = &line[i];
            }
            i++;
        }
        n--;
    }
    if (start && end) {
        i = 0;
        while (start <= end) {
            word[i] = *start;
            start++;
            i++;
        }
        word[i] = '\0';
		return;
    }
	word[0] = '\0';
}


void add_deck_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char word[MAX_STRING_SIZE];
	uint nr_cards;

	fgets(line, MAX_STRING_SIZE, stdin);
	printf("%s", line);
	find_nth_word(word, line, 1);
	nr_cards = atoi(word);
	find_nth_word(word, line, 2);
	if (strlen(word)) {
		INVALID_COMMAND
		return;
	}

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
	char word[MAX_STRING_SIZE];

	uint deck_index;
	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	deck_index = atoi(word);
	find_nth_word(word, line, 2);
	if (strlen(word)) {
		INVALID_COMMAND
		return;
	}

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
	char word[MAX_STRING_SIZE];
	uint deck_index, card_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	deck_index = atoi(word);
	find_nth_word(word, line, 2);
	card_index = atoi(word);
	find_nth_word(word, line, 3);
	if (strlen(word)) {
		INVALID_COMMAND
		return;
	}
	
	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}
	del_card(deck_list, deck_index, card_index);
}

void add_cards_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char word[MAX_STRING_SIZE];
	uint deck_index, nr_cards;

	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	deck_index = atoi(word);
	find_nth_word(word, line, 2);
	nr_cards = atoi(word);
	find_nth_word(word, line, 3);
	if (strlen(word)) {
		INVALID_COMMAND
		return;
	}
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
	char word[MAX_STRING_SIZE];

	uint deck_index;
	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	deck_index = atoi(word);
	find_nth_word(word, line, 2);
	if (strlen(word)) {
		INVALID_COMMAND
		return;
	}

	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}
	doubly_linked_list_t *deck = dll_get_nth_node(deck_list, deck_index)->data;
	printf("The length of deck %d is %d.\n", deck_index, deck->size);
}

void shuffle_deck_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char word[MAX_STRING_SIZE];

	uint deck_index;
	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	deck_index = atoi(word);
	find_nth_word(word, line, 2);
	if (strlen(word)) {
		INVALID_COMMAND
		return;
	}

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
	char word[MAX_STRING_SIZE];
	uint deck_index_1, deck_index_2;

	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	deck_index_1 = atoi(word);
	find_nth_word(word, line, 2);
	deck_index_2 = atoi(word);
	find_nth_word(word, line, 3);
	if (strlen(word)) {
		INVALID_COMMAND
		return;
	}

	if (deck_index_1 >= deck_list->size || deck_index_2 >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}
	merge_decks(deck_list, deck_index_1, deck_index_2);
	printf("The deck %d and the deck %d were successfully merged.\n", deck_index_1, deck_index_2);
}

void split_deck_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char word[MAX_STRING_SIZE];
	uint deck_index, index_split;
	
	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	deck_index = atoi(word);
	find_nth_word(word, line, 2);
	index_split = atoi(word);
	find_nth_word(word, line, 3);
	if (strlen(word)) {
		INVALID_COMMAND
		return;
	}

	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}
	split_deck(deck_list, deck_index, index_split);
}

void reverse_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char word[MAX_STRING_SIZE];
	uint deck_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	deck_index = atoi(word);
	find_nth_word(word, line, 2);
	if (strlen(word)) {
		INVALID_COMMAND
		return;
	}

	doubly_linked_list_t *deck = dll_get_nth_node(deck_list, deck_index)->data;
	dll_reverse_list(deck);
	printf("The deck %d was successfully reversed.\n", deck_index);
}

void show_deck_input(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char word[MAX_STRING_SIZE];
	uint deck_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	deck_index = atoi(word);
	find_nth_word(word, line, 2);
	if (strlen(word)) {
		INVALID_COMMAND
		return;
	}

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
	char word[MAX_STRING_SIZE];

	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	if (strlen(word)) {
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
	char word[MAX_STRING_SIZE];
	uint deck_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	deck_index = atoi(word);
	find_nth_word(word, line, 2);
	if (strlen(word)) {
		INVALID_COMMAND
		return;
	}

	if (deck_index >= deck_list->size) {
		DECK_INDEX_OUT_OF_BOUNDS
		return;
	}

	doubly_linked_list_t *deck = dll_get_nth_node(deck_list, deck_index)->data;
	dll_sort_list(deck, &compare_cards);
	printf("The deck %d was successfully sorted.\n", deck_index);
}

void exit_program(doubly_linked_list_t *deck_list) {
	char line[MAX_STRING_SIZE];
	char word[MAX_STRING_SIZE];
	uint deck_index;

	fgets(line, MAX_STRING_SIZE, stdin);
	find_nth_word(word, line, 1);
	if (strlen(word)) {
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

int main () {
	doubly_linked_list_t *deck_list = dll_create(sizeof(doubly_linked_list_t));

	char command[MAX_STRING_SIZE];

	while (1) {
		scanf("%s", command);
		if (!strcmp("ADD_DECK", command)) {
			add_deck_input(deck_list);
			continue;
		}
		if (!strcmp("DEL_DECK", command)) {
			delete_deck_input(deck_list);
			continue;
		}
		if (!strcmp("DEL_CARD", command)) {
			delete_card_input(deck_list);
			continue;
		}
		if (!strcmp("ADD_CARDS", command)) {
			add_cards_input(deck_list);
			continue;
		}
		if (!strcmp("DECK_NUMBER", command)) {
			printf("The number of decks is %d.\n", deck_list->size);
			continue;
		}
		if (!strcmp("DECK_LEN", command)) {
			deck_len(deck_list);
			continue;
		}
		if (!strcmp("SHUFFLE_DECK", command)) {
			shuffle_deck_input(deck_list);
			continue;
		}
		if (!strcmp("MERGE_DECKS", command)) {
			merge_decks_input(deck_list);
			continue;
		}
		if (!strcmp("SPLIT_DECK", command)) {
			split_deck_input(deck_list);
			continue;
		}
		if (!strcmp("REVERSE_DECK", command)) {
			reverse_input(deck_list);
			continue;
		}
		if (!strcmp("SHOW_DECK", command)) {
			show_deck_input(deck_list);
			continue;
		}
		if (!strcmp("SHOW_ALL", command)) {
			show_all_decks(deck_list);
			continue;
		}
		if (!strcmp("SORT_DECK", command)) {
			sort_deck_input(deck_list);
			continue;
		}
		if (!strcmp("EXIT", command)) {
			exit_program(deck_list);
			break;
		}
		INVALID_COMMAND
	}
	return 0;
}