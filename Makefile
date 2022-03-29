CFLAG = -Wall -Wextra -std=c99 -g
EXEC = deck_manager

build: main

main: main.o cards.o Linkedlist.o input_functions.o
	gcc	${CFLAG} -o ${EXEC} $?

main.o: main.c
	gcc ${CFLAG} -c -o $@ $?

cards.o: cards.c
	gcc ${CFLAG} -c -o $@ $?

Linkedlist.o: Linkedlist.c
	gcc ${CFLAG} -c -o $@ $?

input_functions.o: input_functions.c
	gcc ${CFLAG} -c -o $@ $?

clean:
	rm -f *.o ${EXEC}