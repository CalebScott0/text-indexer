CC = cc
CFLAGS =  \
	 -Wall -Wextra -Wextra \
	 -pedantic -std=c17 -I. -g \
	 -fno-omit-frame-pointer \
	 -fsanitize=address,undefined \

# TODO: cleaner file names with variables

alv.o: ./src/alv.c ./include/alv.h
	$(CC) $(CFLAGS) -c $< -o $@
	
main.o: ./src/main.c ./include/alv.h
	$(CC) $(CFLAGS) -c $< -o $@

main: main.o alv.o
	$(CC) $(CFLAGS) $^ -o $@

run_main: main
	./$<

clean:
	rm -f *.o

.PHONY: clean run_main

