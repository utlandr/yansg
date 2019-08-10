CC=gcc
CFLAGS=-g -Wall 
LDLIBS=-lncurses

yasg: yasg.c yasg.h
	$(CC) $(CFLAGS) $(LDLIBS) -o yasg yasg.c 

clean:
	rm yasg
