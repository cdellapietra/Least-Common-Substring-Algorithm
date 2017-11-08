all : Dynamic Memoized

Dynamic : dynamic.cpp
	g++ -std=c++11 -c dynamic.cpp
	g++ -std=c++11 -o Dynamic dynamic.o

Memoized : memoized.cpp
	g++ -std=c++11 -c memoized.cpp
	g++ -std=c++11 -o Memoized memoized.o

clean :
	rm -f *.o Dynamic Memoized core.*
