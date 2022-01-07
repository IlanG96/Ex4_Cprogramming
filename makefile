FLAGS=-Wall -g
CC=gcc


all: graph


graph:main.o graph.a
		$(CC) $(FLAGS) -o graph main.o graph.a


main.o:main.c
		$(CC)   $(FLAGS) -c main.c


graph.o: graph.c
		$(CC)   $(FLAGS) -c graph.c


graph.a: graph.o 
			ar -rcs graph.a graph.o
			ranlib graph.a


.PHONY: clean all

clean: 
	rm -f *o *a graph