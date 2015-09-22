#MAKEFILE FOR PROJECT2

project2: driver.o llist.o
	g++ driver.o llist.o -o project2

driver.o: driver.cpp
	g++ -c driver.cpp

llist.o: llist.cpp
	g++ -c llist.cpp

debug:
	g++ -c -D_DEBUGMODE llist.cpp
	g++ -c -D_DEBUGMODE driver.cpp
	g++ llist.o driver.o -o project2Debug

clean:
	rm *.o project2

cleanDebug:
	rm *.o project2Debug

