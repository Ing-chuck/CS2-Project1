p1_ai: main.o point.o troop.o
	g++ -std=c++11 -o p1_ai main.o point.o troop.o

point.o: point.h point.cpp
	g++ -std=c++11 -c point.cpp

troop.o: troop.h troop.cpp point.h
	g++ -std=c++11 -c troop.cpp

main.o: main.cpp troop.h
	g++ -std=c++11 -c main.cpp

clean:
	rm p1_ai *.o
