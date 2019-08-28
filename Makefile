# Im still learning how to use make. Don't laugh at me

# Compiler
CC=gcc

# C flags:
# 	-g	Add debugger info to the executable
# 	-Wall	Include most of the compiler warnings
CFLAGS=-g -Wall 

# include ncurces library dependency
# LESSON: libs have to be specified at the end
LDLIBS=-lncurses

# Build executable from object file
yasg: yasg.o
	$(CC) $(CFLAGS) -o yasg yasg.o $(LDLIBS) 

# To build the object file, we need to compile the source files
yasg.o: yasg.c yasg.h
	$(CC) $(CFLAGS) -c yasg.c yasg.h $(LDLIBS) 

# Cleanup everything (executable and object files)
clean:
	rm -f yasg 
	rm -f *.o 	
	rm -f *~ 	
	rm -f *.gch 	

