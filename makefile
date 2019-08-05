CFLAGS=-g
LDFLAGS=-g
LDLIBS=-lncurses

snake: snake.c
	gcc $(LDFLAGS) -o snake snake.c $(LDLIBS)
