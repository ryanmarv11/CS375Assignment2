all: clean main

main: main.o BestFirstSearch.o  
	g++ -g -Wall -Werror -std=c++14 main.o  BestFirstSearch.o -o BestFirstSearch
main.o: main.cpp BestFirstSearch.h 
	g++ -c -g -Wall -Werror -std=c++14 main.cpp -o main.o -DTEST14
BestFirstSearch.o: BestFirstSearch.cpp BestFirstSearch.h 
	g++ -c -g -Wall -Werror -std=c++14 BestFirstSearch.cpp -o BestFirstSearch.o   
run:all
	./BestFirstSearch
clean:
	rm -rf BestFirstSearch  *.o
memcheck:all
	valgrind --leak-check=full --track-origins=yes ./BestFirstSearch