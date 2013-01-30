#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

typedef enum Suit_ {CLUB, DIAMOND, HEART, SPADE} Suit;
typedef enum Value_ {TWO=1, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE} Value;

typedef struct Card_{
	Value value;
	Suit suit;
	} Card;

#define card_value(card) ((card)->value)
#define card_suit(card) ((card)->suit)

void card_init(Card *card, Suit suit, Value value);
void card_print(Card *card);
int hand_card_compare(const void *card1, const void *card2);
int card_compare(Card *card1, Card *card2);
char *stringify_suit(Suit suit);
char *stringify_value(Value value);
#endif
/* CARD_H_INCLUDED */
