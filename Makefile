CC = gcc

test: main.o loglib.o
	$(CC) -o test main.o loglib.o

.c.o:
	gcc -g -c $<

main.o: main.c log.h
	gcc -c main.c

loglib.o: loglib.c log.h
	gcc -c loglib.c

clean:
	rm *.o
