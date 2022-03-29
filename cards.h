// Copyright 2022 Daraban Albert-Timotei
#ifndef CHECKER_CARDS_H_
#define CHECKER_CARDS_H_

// Mesaje de eroare
#define DECK_INDEX_OUT_OF_BOUNDS \
printf("The provided index is out of bounds for the deck list.\n");
#define CARD_INDEX_OUT_OF_BOUNDS(index) \
printf("The provided index is out of bounds for deck %d.\n", index);
#define INVALID_CARD printf("The provided card is not a valid one.\n");
#define INVALID_COMMAND printf("Invalid command. Please try again.\n");
#define MAX_STRING_SIZE 69

typedef unsigned int uint;

typedef struct card card;
struct card
{
	char num;  // numarul carti
	/* Simbolul este retinut ca un nr de la 1 4 pentru a salva memorie
	si pentru a face compararea mai usoara.
	*/
	char symbol;
};

void
print_card(void *data);

void
add_cards(doubly_linked_list_t *deck, uint nr_cards);

int
del_card(doubly_linked_list_t *deck_list, uint deck_index, uint card_index);

void
shuffle_deck(doubly_linked_list_t *deck);

void
merge_decks(doubly_linked_list_t *deck_list, uint index1, uint index2);

int
compare_cards(void *p_card1, void *p_card2);

int
split_deck(doubly_linked_list_t *deck_list, uint deck_index, uint split_index);

#endif  // CHECKER_CARDS_H_
