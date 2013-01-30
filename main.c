#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "card.h"
#include "hand.h"
#include "deck.h"
#include "player.h"
#include "imp_scoring.h"
#include "monte_carlo.h"
#define NUM_AI 3
#define NUM_PLAYERS (NUM_AI+1)
#define USER_NUM NUM_AI
int get_dis_num(void);
void printchips(Player **players, int *ingame);
int ctoi(char c);
int max(int a, int b);

int main()
{
	int i, j, pot = 0, maxbet, dealer, last_playing;
	int playing[NUM_PLAYERS], bets[NUM_PLAYERS], ingame[NUM_PLAYERS];
	double best = 0.0;
	char c;
	Player *best_p = NULL;
	Player **players = (Player **)malloc(NUM_PLAYERS*sizeof(Player *));
	Player **ais = (Player **)malloc(NUM_AI*sizeof(Player *));
	Player *user = (Player *)malloc(sizeof(Player));
    Deck *deck = (Deck *)malloc(sizeof(Deck));

	for(i=0; i<NUM_PLAYERS; i++)
		ingame[i] = 1;
    deck_init(deck);
    deck_shuffle(deck, time(NULL));
	player_init(user, 100);
	players[USER_NUM] = user;
	for(i=0; i<NUM_AI; i++){
		ais[i] = (Player *)malloc(sizeof(Player));
		player_init(ais[i], 100);
		players[i] = ais[i];
	}
	dealer = 0;

	/*game loop start here*/
	while(ingame[USER_NUM]){
		deck_shuffle(deck, time(NULL));
		for(i=0; i<NUM_PLAYERS; i++){
			if(ingame[i]){
				playing[i] = 1;
				bets[i] = 0;
				hand_draw5((players[i])->hand, deck);
			}
		}

		hand_sort(user->hand);
		printf("Your hand:\n");
		hand_print(user->hand);
		mc_findbest(user->hand, true);

		/* first betting loop */
		maxbet = 0;
		for(i=0; i<NUM_PLAYERS; i++){
			int cur = (i+dealer)%NUM_PLAYERS;
			if(players[cur] == user){
				printf("How much would you like to bet (-1 to fold, %d minimum)?  ", maxbet);
				scanf("%d", &bets[cur]);
				while((c=getchar()) != '\n');/*flush new stdin*/
				if(bets[cur] < 0){
					playing[cur] = 0;
					last_playing = cur;
				}
				if(bets[cur] < maxbet)
					bets[cur] = maxbet;
				if(playing[cur])
					maxbet = max(player_bet(user, bets[cur], &pot), maxbet);
			}
			else{
				if(ingame[cur]){
					double score = imp_score_hand(players[cur]->hand);
					if(maxbet <= 5*score){
						bets[cur] = 5*score;
						maxbet = max(player_bet(players[cur], bets[cur], &pot), maxbet);
						printf("AI player #%d bets %d\n", cur, bets[cur]);
					}
					else if(maxbet <= 10*score){
						bets[cur] = maxbet;
						player_bet(players[cur], bets[cur], &pot);
						printf("AI player #%d bets %d\n", cur, bets[cur]);
					}
					else{/*maxbet > 10*score*/
						printf("AI player #%d folds\n", cur);
						playing[cur] = 0;
						last_playing = cur;
					}
				}
			}
		}
		for(i=0; i<NUM_PLAYERS; i++){
			int cur = (i+dealer)%NUM_PLAYERS;
			if(players[cur] == user && playing[cur]){
				int spread = maxbet - bets[cur];
				if(spread == 0)
					continue;
				printf("Would you like to call (-1 to fold, %d to call)?  ", spread);
				scanf("%d", &bets[cur]);
				while((c=getchar()) != '\n');/*flush new stdin*/
				if(bets[cur] < 0){
					playing[cur] = 0;
					last_playing = cur;
				}
				else
					player_bet(user, spread, &pot);
			}
			else{
				if(player_chips(players[cur]) > 0 && playing[cur] && ingame[cur]){
					double score = imp_score_hand(players[cur]->hand);
					int spread = maxbet - bets[cur];
					if(spread == 0)
						continue;
					if(maxbet <= 10*score){
						player_bet(players[cur], spread, &pot);
						printf("AI player #%d calls\n", cur);
					}
					else{/*maxbet > 10*score*/
						printf("AI player #%d folds\n", cur);
						playing[cur] = 0;
						last_playing = cur;
					}
				}
			}
		}

		/* discarding stage */
		for(i=0; i<NUM_AI; i++){
			if(ingame[i] && playing[i])
				hand_discard_multi(ais[i]->hand, mc_findbest(ais[i]->hand, false), deck);
		}
		if(playing[USER_NUM]){
			int todis;
			printf("Which cards (0-4) would you like to discard (ex. 023)?  ");
			todis = get_dis_num();
			hand_discard_multi(user->hand, todis, deck);
		}

		printf("\n--Players discard and draw--\n");

		for(i=0; i<NUM_PLAYERS; i++){
			if(ingame[i] && playing[i])
				hand_draw5(players[i]->hand, deck);
		}
		if(playing[USER_NUM]){
			printf("Your hand:\n");
			hand_print(user->hand);
			printf("Current hand score: %.2f\n", imp_score_hand(user->hand));
		}

		/* second betting loop */
		maxbet = 0;
		for(i=0; i<NUM_PLAYERS; i++){
			bets[i] = 0;
		}
		for(i=0; i<NUM_PLAYERS; i++){
			int cur = (i+dealer)%NUM_PLAYERS;
			if(player_chips(players[cur]) > 0 && players[cur] == user && playing[cur]){
				printf("How much would you like to bet (-1 to fold, %d minimum)?  ", maxbet);
				scanf("%d", &bets[cur]);
				while((c=getchar()) != '\n');/*flush new stdin*/
				if(bets[cur] < 0){
					playing[cur] = 0;
					last_playing = cur;
				}
				if(bets[cur] < maxbet)
					bets[cur] = maxbet;
				if(playing[cur])
					maxbet = max(player_bet(user, bets[cur], &pot), maxbet);
			}
			else{
				if(player_chips(players[cur]) >= 0 && ingame[cur] && playing[cur]){
					double score = imp_score_hand(players[cur]->hand);
					if(maxbet <= 5*score){
						bets[cur] = 5*score;
						maxbet = max(player_bet(players[cur], bets[cur], &pot), maxbet);
						printf("AI player #%d bets %d\n", cur, bets[cur]);
					}
					else if(maxbet <= 10*score){
						bets[cur] = maxbet;
						player_bet(players[cur], bets[cur], &pot);
						printf("AI player #%d bets %d\n", cur, bets[cur]);
					}
					else{/*maxbet > 10*score*/
						printf("AI player #%d folds\n", cur);
						playing[cur] = 0;
						last_playing = cur;
					}
				}
			}
		}
		for(i=0; i<NUM_PLAYERS; i++){
			int cur = (i+dealer)%NUM_PLAYERS;
			if(players[cur] == user && playing[cur]){
				int spread = maxbet - bets[cur];
				if(spread == 0)
					continue;
				printf("Would you like to call (-1 to fold, %d to call)?  ", spread);
				scanf("%d", &bets[cur]);
				while((c=getchar()) != '\n');/*flush new stdin*/
				if(bets[cur] < 0){
					playing[cur] = 0;
					last_playing = cur;
				}
				else
					player_bet(user, spread, &pot);
			}
			else{
				if(player_chips(players[cur]) >= 0 && playing[cur] && ingame[cur]){
					double score = imp_score_hand(players[cur]->hand);
					int spread = maxbet - bets[cur];
					if(spread == 0)
						continue;
					if(maxbet <= 10*score){
						player_bet(players[cur], spread, &pot);
						printf("AI player #%d calls\n", cur);
					}
					else{/*maxbet > 10*score*/
						printf("AI player #%d folds\n", cur);
						playing[cur] = 0;
						last_playing = cur;
					}
				}
			}
		}

		/* determine the best hand */
		best = 0;
		best_p = NULL;
		for(i=0; i<NUM_PLAYERS; i++){
			if(ingame[i] && playing[i]){
				double sc = imp_score_hand(players[i]->hand);
				if(sc > best){
					best = sc;
					best_p = players[i];
				}
			}
		}
		if(best_p == NULL){
			best_p = players[last_playing];/* last player to fold would be the winner */
			best = imp_score_hand(players[last_playing]->hand);
		}
		player_collect(best_p, &pot);
		printf("Winning score: %.2f\n", best);
		printf("Winning hand:\n");
		hand_print(best_p->hand);

		for(i=0; i<NUM_PLAYERS; i++){
			if(players[i] == best_p){
				if(players[i] == user){
					printf("You win!!\n");
				}
				else{
					printf("AI player %d wins.\n", i);
				}
			}
		}

		/* discard cards and eliminate broke players */
		for(i=0; i<NUM_PLAYERS; i++){
			if(ingame[i]){
				for(j=0; j<NUM_CARDS; j++){
					hand_discard(players[i]->hand, j, deck);
				}
				if(player_chips(players[i]) <= 0){
					ingame[i] = 0;
					if(players[i] != user)
						printf("AI player #%d eliminated\n", i);
					else
						printf("You lost!\n");
				}
			}
		}

		printchips(players, ingame);
		dealer++;
		dealer = dealer%NUM_PLAYERS;
		if(ingame[USER_NUM]){
			printf("Press enter to begin next hand (or q to quit):");
			c = getchar();
			if(c == 'q')
				break;
			if(c != '\n')
				while((c=getchar()) != '\n');/*flush new stdin*/
		}
		printf("\n\n\n");
	}
    /*game loop end here*/

    player_destroy(user, deck);
    for(i=0; i<NUM_AI; i++){
    	player_destroy(ais[i], deck);
    	/*free(ais[i]);*/
    }
	deck_destroy(deck);
	free(deck);
	free(user);
	free(ais);
	free(players);
    return 0;
}

int get_dis_num(void){
	char c;
	int num, numtot=0;
	int numarr[] = {0, 0, 0, 0, 0};
	while((c=getchar()) != '\n'){
		if(c<'0' || c>'4'){
			printf("Invalid input!! Only input numbers 0-4\n");
			return 0;
		}
		else{
			num = ctoi(c);
			if(numarr[num]){
				printf("Invalid input!! Can only discard a card once\n");
				return 0;
			}
			numarr[num] = 1;
			numtot += power(2, num);
		}
	}
	return numtot;
}

void printchips(Player **players, int *ingame){
	int i;
	printf("Chip standings:\n");
	for(i=0; i<NUM_AI; i++){
		if(ingame[i])
			printf("AI player #%d: %d\n", i, player_chips(players[i]));
	}
	printf("User        : %d\n", player_chips(players[i]));
}

int ctoi(char c){
	switch(c){
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		default:
			printf("Error! Function ctof only handles ints 0-4\n");
			return 0;
	}
}

int max(int a, int b){
	return a>b?a:b;
}
