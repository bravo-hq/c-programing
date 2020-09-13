CFLAGS = -g -ggdb3 -Wall -Werror -pedantic -std=gnu99
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c,%.o,$(SRCS))

test-future: $(OBJS)
	gcc $(CFLAGS) -o $@ $(OBJS)
%.o: %.c
	gcc $(CFLAGS) -c $<
deck.o: deck.h
cards.o: cards.h
eval.o: eval.h
future.o: future.h

.PHONY: clean
clean:
	rm -f test-future *.o *.c~ *.h~
