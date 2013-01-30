This is my final project for CSPP 51040 - C Programming in Fall 2012
It is a 5 card draw game with 3 AI players written in C.  It utilizes a monte carlo simulation to
advise the player and AI on which cards to discard and how to bet.

A makefile is included in this directory.  To remove all *.o, *.~, and executables, run 'make clean'.
To compile the program, run 'make all'.
To run the program, run './poker'.

This directory contains headers and source code files for abstractions of the card, hand, deck, and player.
Also included is the main.c, the monte_carlo files, and two different scoring files, scoring.c and
an improved version imp_scoring.c.  Only the improved version is used in the final source code
of the project.

The main method of the program creates all the necessary data structures for the game, then enters the loop
contaning the game logic.  At each iteration of the loop, the necessary variables are initialized and the
deck is shuffled.  Each player is then delt 5 cards.  The user is advised on the strength of their hand
by the monte carlo simulation of 1000 draws for every possible discard.  The game then enters the first
round of betting.  Betting begins with the dealer, which rotates 1 player each hand.  Each player is given
a chance to fold or bid, where their bid must be at least as much as the maximum bid so far.  After each
player is given a chance to bid, each player who bid less than the maximum bid has the chance to call.
A player who runs out of chips during a bidding round is not eliminated unless they lose the hand.  The
AI players prefer to bid 5x their hand score, but will bid up to 10x their hand score before folding.  After
all players have had the chance to call, each player discards and draws up to 5 cards.  The AI players follow
the advice of the monte carlo advisor exactly.  After each player has their final hand, there is a second
round of bidding with the same format as the first.  Following this, the hand with the highest score is
declared the winner, they collect all the chips in the pot, and all the cards are returned to the deck.
The game continues in this loop until either the player quits or has no chips left.

The improved scoring algorithm has several small changes from the original, linear algorithm.
The main difference is the use of a nonlinear value scale for the hands.  The new scale increases
greatly up to three of a kind, and then levels off.  Witin each class there is not as much variation
as the original especially for the higher hands.  The reasoning for this is that it is better to shoot
for a pair of aces than a pair of twos, but much better to shoot for three of a kind or higher than any
lower hand.
