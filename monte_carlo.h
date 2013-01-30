#ifndef MONTE_CARLO_H_INCLUDED
#define MONTE_CARLO_H_INCLUDED
#include "hand.h"
#include "imp_scoring.h"
#include "card.h"
#define NUM_TRIALS 1000
typedef int bool;
#define true 1
#define false 0

int mc_findbest(Hand *hand, bool player);
void mc_card_pos(int n);
int power(int base, int exponent);
#endif
/* MONTE_CARLO_H_INCLUDED */
