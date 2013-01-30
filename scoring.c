#include<stdio.h>
#include "scoring.h"

int score_hand(Hand *hand){
	int score = 0;
	if(hand->numCards < NUM_CARDS){
		printf("Only full hands can be scored.\n");
		return score;
	}
	hand_sort(hand);
	score = score_straight_flush(hand);
	if(score>0)
		return score;
	score = score_four_of_a_kind(hand);
	if(score>0)
		return score;
	score = score_full_house(hand);
	if(score>0)
		return score;
	score = score_flush(hand);
	if(score>0)
		return score;
	score = score_straight(hand);
	if(score>0)
		return score;
	score = score_three_of_a_kind(hand);
	if(score>0)
		return score;
	score = score_two_pair(hand);
	if(score>0)
		return score;
	score = score_pair(hand);
	if(score>0)
		return score;
	score = score_high_card(hand);
	if(score>0)
		return score;
	else
		return score;
}

int score_straight_flush(Hand *hand){
	if(score_flush(hand) > 0 && score_straight(hand) > 0){
		if(card_value(hand->cards[0]) == TWO && card_value(hand->cards[4]) == ACE){
			return STRAIGHT_FLUSH_RANK*13+card_value(hand->cards[3]);
		}
		else{
			return STRAIGHT_FLUSH_RANK*13+card_value(hand->cards[4]);
		}
	}
	else{
		return 0;
	}
}

int score_four_of_a_kind(Hand *hand){
	if((card_value(hand->cards[0]) == card_value(hand->cards[1]) &&
		card_value(hand->cards[0]) == card_value(hand->cards[2]) &&
		card_value(hand->cards[0]) == card_value(hand->cards[3])) ||
		(card_value(hand->cards[1]) == card_value(hand->cards[2]) &&
		card_value(hand->cards[1]) == card_value(hand->cards[3]) &&
		card_value(hand->cards[1]) == card_value(hand->cards[4]))){
			return FOUR_OF_A_KIND_CLASS*13+card_value(hand->cards[2]);
		}
	else{
		return 0;
	}
}

int score_full_house(Hand *hand){
	if(card_value(hand->cards[0]) == card_value(hand->cards[1]) &&
		card_value(hand->cards[3]) == card_value(hand->cards[4]) &&
		(card_value(hand->cards[0]) == card_value(hand->cards[2]) ||
		 card_value(hand->cards[4]) == card_value(hand->cards[2]))){
		 	return FULL_HOUSE_CLASS*13+card_value(hand->cards[2]);
		 }
	else{
		return 0;
	}
}

int score_flush(Hand *hand){
	if(card_suit(hand->cards[0]) == card_suit(hand->cards[1]) &&
		card_suit(hand->cards[0]) == card_suit(hand->cards[2]) &&
		card_suit(hand->cards[0]) == card_suit(hand->cards[3]) &&
		card_suit(hand->cards[0]) == card_suit(hand->cards[4])){
			return FLUSH_CLASS*13+card_value(hand->cards[4]);
		}
	else{
		return 0;
	}
}

int score_straight(Hand *hand){
	if(card_value(hand->cards[0]) == card_value(hand->cards[1])-1 &&
		card_value(hand->cards[0]) == card_value(hand->cards[2])-2 &&
		card_value(hand->cards[0]) == card_value(hand->cards[3])-3){
			if(card_value(hand->cards[0]) == card_value(hand->cards[4])-4){
				return STRAIGHT_CLASS*13+card_value(hand->cards[4]);
			}
			else if(card_value(hand->cards[0]) == TWO && card_value(hand->cards[4]) == ACE){
				return STRAIGHT_CLASS*13+card_value(hand->cards[3]);
			}
			else{
				return 0;
			}
	}
	else{
		return 0;
	}
}

int score_three_of_a_kind(Hand *hand){
	if((card_value(hand->cards[0]) == card_value(hand->cards[1]) &&
		card_value(hand->cards[0]) == card_value(hand->cards[2])) ||
		(card_value(hand->cards[2]) == card_value(hand->cards[3]) &&
		card_value(hand->cards[2]) == card_value(hand->cards[4]))){
			return THREE_OF_A_KIND_CLASS*13+card_value(hand->cards[2]);
		}
	else{
		return 0;
	}
}

int score_two_pair(Hand *hand){
	if((card_value(hand->cards[0]) == card_value(hand->cards[1]) ||
		card_value(hand->cards[1]) == card_value(hand->cards[2])) &&
		(card_value(hand->cards[2]) == card_value(hand->cards[3]) ||
		 card_value(hand->cards[3]) == card_value(hand->cards[4]))){
		 	return TWO_PAIR_CLASS*13+card_value(hand->cards[3]);
	}
	else{
		return 0;
	}
}

int score_pair(Hand *hand){
	if(card_value(hand->cards[0]) == card_value(hand->cards[1]) ||
		card_value(hand->cards[1]) == card_value(hand->cards[2])){
			return PAIR_CLASS*13+card_value(hand->cards[1]);
	}
	else if(card_value(hand->cards[2]) == card_value(hand->cards[3]) ||
			card_value(hand->cards[3]) == card_value(hand->cards[4])){
				return PAIR_CLASS*13+card_value(hand->cards[3]);
	}
	else{
		return 0;
	}
}

int score_high_card(Hand *hand){
	return HIGH_CARD_CLASS*13+card_value(hand->cards[4]);
}
