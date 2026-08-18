CC = cc
CFLAGS =  \
	 -Wall -Wextra -Wextra \
	 -pedantic -std=c17 -I. -g \
	 -fno-omit-frame-pointer \
	 -fsanitize=address,undefined \

INCLUDE = ./include
SRC = ./src

avl.o: $(SRC)/avl.c $(INCLUDE)/avl.h
	$(CC) $(CFLAGS) -c $<

main: avl.o $(SRC)/main.c 
	$(CC) $(CFLAGS) $^ -o $@

run_main: main
	./$<

clean:
	rm -f *.o main

.PHONY: clean run_main

