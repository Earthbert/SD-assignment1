// Copyright 2022 Daraban Albert-Timotei
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Linkedlist.h"
#include "utils.h"
#include "cards.h"
#include "input_functions.h"

int main() {
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
			deck_number(deck_list);
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
		fgets(command, MAX_STRING_SIZE, stdin);   // Sa citeasca pana la \n
		INVALID_COMMAND
	}
	return 0;
}
