all: stdExp

stdExp: standardExp.cpp
	g++ -c ./standardExp.cpp -o ./standardExp.o -O3 -I./include -I./../Libraries/eigen -I./../Libraries/json/include
	g++ -o _standardExp.out -O3 ./standardExp.o
