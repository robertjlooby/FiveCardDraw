CFLAGS=-ansi -pedantic -Wall

all: poker

poker: main.o player.o imp_scoring.o monte_carlo.o card.o hand.o deck.o
	gcc $(CFLAGS) -o poker main.o player.o imp_scoring.o monte_carlo.o card.o hand.o deck.o

main.o: main.c player.h imp_scoring.h monte_carlo.h card.h hand.h deck.h
	gcc $(CFLAGS) -c main.c -I.

deck.o: deck.c deck.h card.h
	gcc $(CFLAGS) -c deck.c -I.

card.o: card.c card.h
	gcc $(CFLAGS) -c card.c -I.

player.o: player.c player.h hand.h
	gcc $(CFLAGS) -c player.c -I.

hand.o: hand.c hand.h card.h deck.h monte_carlo.h
	gcc $(CFLAGS) -c hand.c -I.

scoring.o: scoring.c scoring.h hand.h
	gcc $(CFLAGS) -c scoring.c -I.

imp_scoring.o: imp_scoring.c imp_scoring.h hand.h
	gcc $(CFLAGS) -c imp_scoring.c -I.

monte_carlo.o: monte_carlo.c monte_carlo.h hand.h imp_scoring.h card.h
	gcc $(CFLAGS) -c monte_carlo.c -I.

clean:
	\rm -f *.o poker *~
