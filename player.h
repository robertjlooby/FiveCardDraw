#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "hand.h"

typedef struct Player_ {
	Hand *hand;
	int chips;
} Player;

#define player_chips(player) ((player)->chips)

void player_init(Player *player, int chips);
void player_destroy(Player *player, Deck *deck);
int player_bet(Player *player, int amt, int *pot);
void player_collect(Player *player, int *pot);
#endif
/* PLAYER_H_INCLUDED */
