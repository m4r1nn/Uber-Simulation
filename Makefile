
build:
	g++ --std=c++11 -Wall -Wextra -Wpedantic -c main.cpp -o main.o
	g++ --std=c++11 -Wall -Wextra -Wpedantic -c solver.cpp -o solver.o
	g++ --std=c++11 -Wall -Wextra -Wpedantic -c graph.cpp -o graph.o
	g++ --std=c++11 -Wall -Wextra -Wpedantic -c hashtable.cpp -o hashtable.o

	g++ *.o -o tema2

.PHONY: clean

run:
	./main

clean:
	rm out/*/*
	rm tema2
	rm *.o
	rm time.out
