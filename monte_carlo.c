#include "monte_carlo.h"
#include "card.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
int power(int base, int exponent);

int mc_findbest(Hand *hand, bool player){
	int i, j, k, n;
	double score = 0.0;
	int best=0;
	double best_ev=0;
	Hand *handcopy = (Hand *)malloc(sizeof(Hand));
	Deck *deck = (Deck *)malloc(sizeof(Deck));

	hand_init(handcopy);
    deck_init(deck);
    if(hand->numCards < NUM_CARDS){
    	printf("Error: Can only advise on a full hand.\n");
    	return 0;
    }
    hand_sort(hand);

    for(i=0; i<=31; i++){/*0-31 corresponds to 00000-11111 in binary, 1 means discard that card*/
    	unsigned int seed = time(NULL);
    	score = 0;
    	for(j=0; j<NUM_TRIALS; j++){
			for(k=0; k<NUM_CARDS; k++){
				hand_add_card(handcopy, deck_remove_card(deck, hand->cards[k]));
			}
			if(handcopy->numCards < NUM_CARDS){
				hand_print(hand);
				hand_print(handcopy);
				printf("Error: Could not find all cards in deck");
				return 0;
			}
			seed = (seed+5);
			deck_shuffle(deck, seed);
			n=i;
			for(k=NUM_CARDS-1; k>=0; k--){
				if(n >= power(2, k)){
					n -= power(2, k);
					hand_discard(handcopy, k, deck);
				}
			}
			hand_draw5(handcopy, deck);
			score += imp_score_hand(handcopy);
			for(k=0; k<NUM_CARDS; k++){
				hand_discard(handcopy, k, deck);
			}
    	}
    	if(score/NUM_TRIALS > best_ev){
    		best = i;
    		best_ev = score/NUM_TRIALS;
    	}
    }

	if(player){
		printf("Current hand score: %.2f\n", imp_score_hand(hand));
		printf("Best expected hand score: %.2f\n", best_ev);
		printf("Advise discarding cards:\n");
		for(k=NUM_CARDS-1; k>=0; k--){
			if(best >= power(2, k)){
				best -= power(2, k);
				printf("\t");
				printf("%d: ", k);
				card_print(hand->cards[k]);
				printf("\n");
			}
		}
		printf("\n");
	}
    hand_destroy(handcopy, deck);
    free(handcopy);
    deck_destroy(deck);
    free(deck);
    return best;
}

int power(int base, int exponent){
	int i, result = 1;
	if(exponent < 0){
		return result;
	}
	else{
		for(i=0; i<exponent; i++){
			result *= base;
		}
		return result;
	}
}
