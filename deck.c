#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "deck.h"

void deck_init(Deck *deck){
	Suit suit;
	Value value;
	deck->top = NULL;
	deck->bottom = NULL;
	deck->size = 0;

	for(suit=CLUB; suit<=SPADE; suit++){
		for(value=TWO; value<=ACE; value++){
			Card *card = (Card *)malloc(sizeof(Card));
			card_init(card, suit, value);
			deck_add_card(deck, card);
		}
	}
}

void deck_destroy(Deck *deck){
	while(deck->size > 0){
		free(deck_deal(deck));
	}
}

Card *deck_deal(Deck *deck){
	Card *card = deck->top->card;
	DeckCard *oldtop = deck->top;
	deck->size--;
	deck->top = deck->top->next;
	free(oldtop);
	return card;
}

void deck_add_card(Deck *deck, Card *card){
	DeckCard *newDeckCard = (DeckCard *)malloc(sizeof(DeckCard));
	deck->size++;
	newDeckCard->card = card;
	newDeckCard->next = NULL;
	/*if the deck is currently empty*/
	if(deck->top == NULL){
		deck->top = newDeckCard;
	}else{
		deck->bottom->next = newDeckCard;
	}
	deck->bottom = newDeckCard;
}

Card *deck_remove_card(Deck *deck, Card *card){
	Card *remCard = NULL;
	DeckCard **current = (DeckCard **)malloc(sizeof(DeckCard *));
	DeckCard **prev = (DeckCard **)malloc(sizeof(DeckCard *));
	current = &deck->top;
	prev = NULL;
	while(*current != NULL && card_compare(card, (*current)->card) != 0){
		prev = current;
		current = &((*current)->next);
	}
	if(*current == NULL){
		return NULL;
	}
	else{
		deck->size--;
		remCard = (*current)->card;
		if(*current == deck->top){
			deck->top = deck->top->next;
		}
		if(*current == deck->bottom){
			deck->bottom = *prev;
		}
		if(prev != NULL)
			(*prev)->next = (*current)->next;
		return remCard;
	}
}

void deck_print(Deck *deck){
	DeckCard *current = deck->top;
	printf("\nDeck contents:\n");
	while(current != NULL){
		card_print(current->card);
		printf("\n");
		current = current->next;
	}
	printf("\n");
}

void deck_shuffle(Deck *deck, unsigned int seed){
	int i;
	srand(seed);
	for(i=deck->size-1; i>0; i--){
		swap(deckCardAt(deck, i), deckCardAt(deck, rand()%(i+1)));
	}
}

/* swaps the cards held by the DeckCards passed in */
void swap(DeckCard *deckCard1, DeckCard *deckCard2){
	Card *temp = deckCard1->card;
	deckCard1->card = deckCard2->card;
	deckCard2->card = temp;
}

DeckCard *deckCardAt(Deck *deck, int i){
	DeckCard *deckCard = deck->top;
	for(; i>0; i--){
		deckCard = deckCard->next;
	}
	return deckCard;
}
