CFLAG = -Wall -Wextra -std=c99 -g

build: main

main: main.o cards.o Linkedlist.o
	gcc	${CFLAG} -o decks_manager $?

main.o: main.c
	gcc ${CFLAG} -c -o $@ $?

cards.o: cards.c
	gcc ${CFLAG} -c -o $@ $?

Linkedlist.o: Linkedlist.c
	gcc ${CFLAG} -c -o $@ $?

clean:
	rm -f *.o decks_manager