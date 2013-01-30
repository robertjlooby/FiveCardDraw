#ifndef IMP_SCORING_H_INCLUDED
#define IMP_SCORING_H_INCLUDED

#include "hand.h"
#define IMP_STRAIGHT_FLUSH_RANK 4.3
#define IMP_FOUR_OF_A_KIND_CLASS 4.2
#define IMP_FULL_HOUSE_CLASS 4.1
#define IMP_FLUSH_CLASS 4
#define IMP_STRAIGHT_CLASS 3.9
#define IMP_THREE_OF_A_KIND_CLASS 3.2
#define IMP_TWO_PAIR_CLASS 2.2
#define IMP_PAIR_CLASS 1
#define IMP_HIGH_CARD_CLASS 0

double imp_score_hand(Hand *hand);

double imp_score_straight_flush(Hand *hand);
double imp_score_four_of_a_kind(Hand *hand);
double imp_score_full_house(Hand *hand);
double imp_score_flush(Hand *hand);
double imp_score_straight(Hand *hand);
double imp_score_three_of_a_kind(Hand *hand);
double imp_score_two_pair(Hand *hand);
double imp_score_pair(Hand *hand);
double imp_score_high_card(Hand *hand);

#endif
/* IMP_SCORING_H_INCLUDED */
