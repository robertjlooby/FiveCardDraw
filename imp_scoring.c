#include<stdio.h>
#include "imp_scoring.h"

/* returns the score of the hand.
each function assumes all the ones executed
before it have returned 0. Ex a hand with
three of a kind will return nonzero for
score_two_pair but is only called if
score_three_of_a_kind has returned 0 */
double imp_score_hand(Hand *hand){
	double score = 0;
	if(hand->numCards < NUM_CARDS){
		printf("Only full hands can be scored.\n");
		return score;
	}
	hand_sort(hand);
	score = imp_score_straight_flush(hand);
	if(score>0)
		return score;
	score = imp_score_four_of_a_kind(hand);
	if(score>0)
		return score;
	score = imp_score_full_house(hand);
	if(score>0)
		return score;
	score = imp_score_flush(hand);
	if(score>0)
		return score;
	score = imp_score_straight(hand);
	if(score>0)
		return score;
	score = imp_score_three_of_a_kind(hand);
	if(score>0)
		return score;
	score = imp_score_two_pair(hand);
	if(score>0)
		return score;
	score = imp_score_pair(hand);
	if(score>0)
		return score;
	score = imp_score_high_card(hand);
	if(score>0)
		return score;
	else
		return score;
}

double imp_score_straight_flush(Hand *hand){
	if(imp_score_flush(hand) > 0 && imp_score_straight(hand) > 0){
		if(card_value(hand->cards[0]) == TWO && card_value(hand->cards[4]) == ACE){
			return IMP_STRAIGHT_FLUSH_RANK+card_value(hand->cards[3])/130.0;
		}
		else{
			return IMP_STRAIGHT_FLUSH_RANK+card_value(hand->cards[4])/130.0;
		}
	}
	else{
		return 0;
	}
}

double imp_score_four_of_a_kind(Hand *hand){
	if((card_value(hand->cards[0]) == card_value(hand->cards[1]) &&
		card_value(hand->cards[0]) == card_value(hand->cards[2]) &&
		card_value(hand->cards[0]) == card_value(hand->cards[3])) ||
		(card_value(hand->cards[1]) == card_value(hand->cards[2]) &&
		card_value(hand->cards[1]) == card_value(hand->cards[3]) &&
		card_value(hand->cards[1]) == card_value(hand->cards[4]))){
			return IMP_FOUR_OF_A_KIND_CLASS+card_value(hand->cards[2])/130.0;
		}
	else{
		return 0;
	}
}

double imp_score_full_house(Hand *hand){
	if(card_value(hand->cards[0]) == card_value(hand->cards[1]) &&
		card_value(hand->cards[3]) == card_value(hand->cards[4]) &&
		(card_value(hand->cards[0]) == card_value(hand->cards[2]) ||
		 card_value(hand->cards[4]) == card_value(hand->cards[2]))){
		 	return IMP_FULL_HOUSE_CLASS+card_value(hand->cards[2])/130.0;
		 }
	else{
		return 0;
	}
}

double imp_score_flush(Hand *hand){
	if(card_suit(hand->cards[0]) == card_suit(hand->cards[1]) &&
		card_suit(hand->cards[0]) == card_suit(hand->cards[2]) &&
		card_suit(hand->cards[0]) == card_suit(hand->cards[3]) &&
		card_suit(hand->cards[0]) == card_suit(hand->cards[4])){
			return IMP_FLUSH_CLASS+card_value(hand->cards[4])/130.0;
		}
	else{
		return 0;
	}
}

double imp_score_straight(Hand *hand){
	if(card_value(hand->cards[0]) == card_value(hand->cards[1])-1 &&
		card_value(hand->cards[0]) == card_value(hand->cards[2])-2 &&
		card_value(hand->cards[0]) == card_value(hand->cards[3])-3){
			if(card_value(hand->cards[0]) == card_value(hand->cards[4])-4){
				return IMP_STRAIGHT_CLASS+card_value(hand->cards[4])/130.0;
			}
			else if(card_value(hand->cards[0]) == TWO && card_value(hand->cards[4]) == ACE){
				return IMP_STRAIGHT_CLASS+card_value(hand->cards[3])/130.0;
			}
			else{
				return 0;
			}
	}
	else{
		return 0;
	}
}

double imp_score_three_of_a_kind(Hand *hand){
	if((card_value(hand->cards[0]) == card_value(hand->cards[1]) &&
		card_value(hand->cards[0]) == card_value(hand->cards[2])) ||
		(card_value(hand->cards[2]) == card_value(hand->cards[3]) &&
		card_value(hand->cards[2]) == card_value(hand->cards[4])) ||
		(card_value(hand->cards[1]) == card_value(hand->cards[2]) &&
		card_value(hand->cards[1]) == card_value(hand->cards[3]))){
			return IMP_THREE_OF_A_KIND_CLASS+card_value(hand->cards[2])/130.0;
		}
	else{
		return 0;
	}
}

double imp_score_two_pair(Hand *hand){
	if((card_value(hand->cards[0]) == card_value(hand->cards[1]) ||
		card_value(hand->cards[1]) == card_value(hand->cards[2])) &&
		(card_value(hand->cards[2]) == card_value(hand->cards[3]) ||
		card_value(hand->cards[3]) == card_value(hand->cards[4]))){
		 	return IMP_TWO_PAIR_CLASS+card_value(hand->cards[3])/26.0;
		}
	else{
		return 0;
	}
}

double imp_score_pair(Hand *hand){
	if(card_value(hand->cards[0]) == card_value(hand->cards[1]) ||
		card_value(hand->cards[1]) == card_value(hand->cards[2])){
			return IMP_PAIR_CLASS+card_value(hand->cards[1])/13.0;
	}
	else if(card_value(hand->cards[2]) == card_value(hand->cards[3]) ||
			card_value(hand->cards[3]) == card_value(hand->cards[4])){
				return IMP_PAIR_CLASS+card_value(hand->cards[3])/13.0;
	}
	else{
		return 0;
	}
}

double imp_score_high_card(Hand *hand){
	return IMP_HIGH_CARD_CLASS+card_value(hand->cards[4])/130.0;
}
