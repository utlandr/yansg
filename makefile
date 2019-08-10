CFLAGS=-g -c -Wall -Iinclude
LDFLAGS=-g
LDLIBS=-lncurses

yasg: yasg.c
	gcc $(LDFLAGS) -o yasg yasg.c $(LDLIBS)
