CC = cc
CFLAGS =  \
	 -Wall -Wextra -Wextra \
	 -pedantic -std=c17 -I. -g \
	 -fno-omit-frame-pointer \
	 -fsanitize=address,undefined \

INCLUDE = ./include
SRC = ./src
TESTS = ./tests

# TODO: make usable with mac (fsanitize env vars and txt file?)
# 	make variables for the .o targets to clean up the below? */

utils.o: $(SRC)/utils.c $(INCLUDE)/utils.h
	$(CC) $(CFLAGS) -c $<

avl.o: $(SRC)/avl.c $(INCLUDE)/avl.h utils.o
	$(CC) $(CFLAGS) -c $<

hash.o: $(SRC)/hash.c $(INCLUDE)/hash.h utils.o
	$(CC) $(CFLAGS) -c $<

token.o: $(SRC)/token.c $(INCLUDE)/token.h
	$(CC) $(CFLAGS) -c $<

loc_test: $(TESTS)/location_tests.c utils.o
	$(CC) $(CFLAGS) $^ -o $@

test_location: loc_test
	./$<

avl_test: $(TESTS)/avl_tests.c avl.o utils.o
	$(CC) $(CFLAGS) $^ -o $@

test_avl: avl_test
	./$<

hash_test: $(TESTS)/hash_tests.c hash.o utils.o
	$(CC) $(CFLAGS) $^ -o $@

test_hash: hash_test
	./$<

main: $(SRC)/main.c hash.o avl.o utils.o token.o
	$(CC) $(CFLAGS) $^ -o $@

run_main: main
	./$<
#
clean:
	rm -f *.o main *_test

.PHONY: clean run_main test_avl test_location test_hash
