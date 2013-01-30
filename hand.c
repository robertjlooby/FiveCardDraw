#include<stdlib.h>
#include<stdio.h>
#include "hand.h"
#include "monte_carlo.h"

void hand_init(Hand *hand){
	int i;
	hand->numCards = 0;
	hand->cards = (Card **)malloc(NUM_CARDS*sizeof(Card *));
	for(i=0; i<NUM_CARDS; i++){
		hand->cards[i] = NULL;
	}
}

void hand_destroy(Hand *hand, Deck *deck){
	int i;
	for(i=0; i<NUM_CARDS; i++){
		deck_add_card(deck, hand->cards[i]);
	}
	free(hand->cards);
}


void hand_sort(Hand *hand){
	qsort((void *)hand->cards, NUM_CARDS, sizeof(Card *), &hand_card_compare);
}

void hand_draw(Hand *hand, Deck *deck){
	hand_sort(hand);
	if(hand->numCards < NUM_CARDS){
		hand->cards[hand->numCards++] = deck_deal(deck);
		return;
	}
}

/* draws cards to fill empty spots in hand */
void hand_draw5(Hand *hand, Deck *deck){
	int i;
	hand_sort(hand);
	for(i=0; i<NUM_CARDS; i++){
		hand_draw(hand, deck);
	}
}

void hand_add_card(Hand *hand, Card *card){
	if(card != NULL){
		hand->cards[hand->numCards++] = card;
	}
}

void hand_discard(Hand *hand, int num, Deck *deck){
	if(hand->cards[num] != NULL){
		deck_add_card(deck, hand->cards[num]);
		hand->cards[num] = NULL;
		hand->numCards--;
	}
}
/* num is the decimal rep. of the binary cards to discard,
ex. if num = 7 = 00111 then cards 2,3,4 will be discarded*/
void hand_discard_multi(Hand *hand, int num, Deck *deck){
	int k;
	for(k=NUM_CARDS-1; k>=0; k--){
		if(num >= power(2, k)){
			num -= power(2, k);
			hand_discard(hand, k, deck);
		}
	}
}

void hand_print(Hand *hand){
	int i;
	for(i=0; i<NUM_CARDS; i++){
		printf("%d: ", i);
		card_print(hand->cards[i]);
		printf("\n");
	}
	printf("\n");
}
