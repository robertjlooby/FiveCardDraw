#ifndef DECK_H_INCLUDED
#define DECK_H_INCLUDED
#include "card.h"

typedef struct DeckCard_ {
	Card *card;
	struct DeckCard_ *next;
} DeckCard;

typedef struct Deck_ {
	DeckCard *top;
	DeckCard *bottom;
	int size;
	void (*destroy)(DeckCard *deckCard);
} Deck;

#define deck_size(deck) ((deck)->size)

void deck_init(Deck *deck);
void deck_destroy(Deck *deck);
Card *deck_deal(Deck *deck);
void deck_add_card(Deck *deck, Card *card);
Card *deck_remove_card(Deck *deck, Card *card);
void deck_shuffle(Deck *deck, unsigned int seed);
void deck_print(Deck *deck);

void swap(DeckCard *deckCard1, DeckCard *deckCard2);
DeckCard *deckCardAt(Deck *deck, int i);
#endif
/* DECK_H_INCLUDED */
