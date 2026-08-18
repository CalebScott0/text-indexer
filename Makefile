CC = cc
CFLAGS =  \
	 -Wall -Wextra -Wextra \
	 -pedantic -std=c17 -I. -g \
	 -fno-omit-frame-pointer \
	 -fsanitize=address,undefined \

INCLUDE = ./include
SRC = ./src
TESTS = ./tests

avl.o: $(SRC)/avl.c $(INCLUDE)/avl.h
	$(CC) $(CFLAGS) -c $<

avl_test: $(TESTS)/avl_tests.c avl.o
	$(CC) $(CFLAGS) $^ -o $@

run_test_avl: avl_test
	./$<

main: avl.o $(SRC)/main.c 
	$(CC) $(CFLAGS) $^ -o $@

run_main: main
	./$<

clean:
	rm -f *.o main *_test

.PHONY: clean run_main run_test_avl
