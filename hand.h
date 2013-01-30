#ifndef HAND_H_INCLUDED
#define HAND_H_INCLUDED
#include "card.h"
#include "deck.h"

#define NUM_CARDS 5
typedef struct Hand_ {
	Card **cards;
	int numCards;
} Hand;

void hand_init(Hand *hand);
void hand_destroy(Hand *hand, Deck *deck);
void hand_sort(Hand *hand);
void hand_draw(Hand *hand, Deck *deck);
void hand_draw5(Hand *hand, Deck *deck);
void hand_add_card(Hand *hand, Card *card);
void hand_discard(Hand *hand, int num, Deck *deck);
void hand_discard_multi(Hand *hand, int num, Deck *deck);
void hand_print(Hand *hand);
#endif
/* HAND_H_INCLUDED */
