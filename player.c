#include<stdlib.h>
#include "player.h"

void player_init(Player *player, int chips){
	player->hand = (Hand *)malloc(sizeof(Hand));
	hand_init(player->hand);
	player->chips = chips;
}

void player_destroy(Player *player, Deck *deck){
	hand_destroy(player->hand, deck);
	free(player->hand);
	free(player);
}

int player_bet(Player *player, int amt, int *pot){
	if(amt > player_chips(player))
		amt = player_chips(player);
	player->chips -= amt;
	*pot += amt;
	return amt;
}

void player_collect(Player *player, int *pot){
	player->chips += *pot;
	*pot = 0;
}
