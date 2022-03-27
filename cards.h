#ifndef CARDS_H
#define CARDS_H

// Error messages
#define DECK_INDEX_OUT_OF_BOUNDS printf("The provided index is out of bounds for the deck list.\n");
#define CARD_INDEX_OUT_OF_BOUNDS(index) printf("The provided index is out of bounds for deck %d.\n", index);
#define INVALID_CARD printf("The provided card is not a valid one.\n");
#define INVALID_COMMAND printf("Invalid command. Please try again.\n");
#define MAX_STRING_SIZE 69

typedef unsigned int uint;

typedef struct card card;
struct card
{
	int num; // number of the card
	char symbol; // shortcut for the simbol, will store only the first letter
};

void
print_card (void *data);

void
add_cards (doubly_linked_list_t *deck, uint nr_cards);

int
del_card (doubly_linked_list_t *deck_list, uint deck_index, uint card_index);

void
shuffle_deck (doubly_linked_list_t *deck);

void
merge_decks (doubly_linked_list_t *deck_list, uint index1, uint index2);

int
compare_cards (void *p_card1, void *p_card2);

int
split_deck(doubly_linked_list_t *deck_list, uint deck_index, uint split_index);

#endif // CARDS_H