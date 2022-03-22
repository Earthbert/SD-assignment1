CFLAG = -Wall -Wextra -std=c99

all: main

main: main.o Linkedlist.o cards.o
	gcc	${CFLAG} -o $@ $?

main.o: main.c
	gcc ${CFLAG} -c -o $@ main.c

Linkedlist.o: Linkedlist.c
	gcc ${CFLAG} -c -o $@ Linkedlist.c

cards.o: cards.c
	gcc ${CFLAG} -c -o $@ cards.c

clean:
	rm -f *.o main