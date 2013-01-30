#ifndef SCORING_H_INCLUDED
#define SCORING_H_INCLUDED

#include "hand.h"
#define STRAIGHT_FLUSH_RANK 9
#define FOUR_OF_A_KIND_CLASS 8
#define FULL_HOUSE_CLASS 7
#define FLUSH_CLASS 6
#define STRAIGHT_CLASS 5
#define THREE_OF_A_KIND_CLASS 4
#define TWO_PAIR_CLASS 3
#define PAIR_CLASS 2
#define HIGH_CARD_CLASS 1

int score_hand(Hand *hand);

int score_straight_flush(Hand *hand);
int score_four_of_a_kind(Hand *hand);
int score_full_house(Hand *hand);
int score_flush(Hand *hand);
int score_straight(Hand *hand);
int score_three_of_a_kind(Hand *hand);
int score_two_pair(Hand *hand);
int score_pair(Hand *hand);
int score_high_card(Hand *hand);
#endif
/* SCORING_H_INCLUDED */
