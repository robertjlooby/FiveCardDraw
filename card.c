#include<stdio.h>
#include "card.h"
void card_init(Card *card, Suit suit, Value value){
	card->suit = suit;
	card->value = value;
}

void card_print(Card *card){
	if(card != NULL){
		printf("%s of %s", stringify_value(card_value(card)), stringify_suit(card_suit(card)));
	}
	else{
		printf("Empty spot");
	}
}

/* used in hand_sort to sort an array of Card * passed to qsort */
int hand_card_compare(const void *card1, const void *card2){
	if(*(Card **)card1==NULL)
		return 1;
	if(*(Card **)card2==NULL)
		return -1;
	return card_value(*(Card **)card1) - card_value(*(Card **)card2);
}

int card_compare(Card *card1, Card *card2){
	if(card1 == NULL)
		return 1;
	if(card2 == NULL)
		return -1;
	if(card_value(card1) != card_value(card2))
		return card_value(card1) - card_value(card2);
	else
		return card_suit(card1) - card_suit(card2);
}

char *stringify_suit(Suit suit){
	switch(suit){
		case CLUB:
			return "Clubs";
		case DIAMOND:
			return "Diamonds";
		case HEART:
			return "Hearts";
		case SPADE:
			return "Spades";
		default:
			return "Invalid Suit";
	}
}

char *stringify_value(Value value){
	switch(value){
		case TWO:
			return "Two";
		case THREE:
			return "Three";
		case FOUR:
			return "Four";
		case FIVE:
			return "Five";
		case SIX:
			return "Six";
		case SEVEN:
			return "Seven";
		case EIGHT:
			return "Eight";
		case NINE:
			return "Nine";
		case TEN:
			return "Ten";
		case JACK:
			return "Jack";
		case QUEEN:
			return "Queen";
		case KING:
			return "King";
		case ACE:
			return "Ace";
		default:
			return "Invalid Value";
	}
}
