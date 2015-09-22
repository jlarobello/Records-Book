
project1: main.o record_functions.o
	cc main.o record_functions.o -o project1

main.o: main.c
	cc -strict -c main.c

record_functions.o: record_functions.c
	cc -strict -c record_functions.c

clean:
	rm *.o project1
