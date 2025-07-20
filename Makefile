all: 1dMaps driftVariance driftVarianceNarrow x2driftVariance corrFunction densityEvolution densityEvolutionNarrow

1dMaps: src/1dMaps.cpp
	g++ -c ./src/1dMaps.cpp -o ./lib/1dMaps.o -O3 -I./include -I./../Libraries/eigen

driftVariance: src/driftVariance.cpp
	g++ -c ./src/driftVariance.cpp -o ./lib/driftVariance.o -O3 -I./include -I./../Libraries/eigen -I./../Libraries/json/include
	g++ -o _driftVariance.out -O3 ./lib/driftVariance.o ./lib/1dMaps.o

driftVarianceNarrow: src/driftVarianceNarrow.cpp
	g++ -c ./src/driftVarianceNarrow.cpp -o ./lib/driftVarianceNarrow.o -O3 -I./include -I./../Libraries/eigen -I./../Libraries/json/include
	g++ -o _driftVarianceNarrow.out -O3 ./lib/driftVarianceNarrow.o ./lib/1dMaps.o

x2driftVariance: src/x2driftVariance.cpp
	g++ -c ./src/x2driftVariance.cpp -o ./lib/x2driftVariance.o -O3 -I./include -I./../Libraries/eigen -I./../Libraries/json/include
	g++ -o _x2driftVariance.out -O3 ./lib/x2driftVariance.o ./lib/1dMaps.o

corrFunction: src/corrFunction.cpp
	g++ -c ./src/corrFunction.cpp -o ./lib/corrFunction.o -O3 -I./include -I./../Libraries/eigen -I./../Libraries/json/include
	g++ -o _corrFunction.out -O3 ./lib/corrFunction.o ./lib/1dMaps.o

densityEvolution: src/densityEvolution.cpp
	g++ -c ./src/densityEvolution.cpp -o ./lib/densityEvolution.o -O3 -I./include -I./../Libraries/eigen -I./../Libraries/json/include
	g++ -o _densityEvolution.out -O3 ./lib/densityEvolution.o ./lib/1dMaps.o

densityEvolutionNarrow: src/densityEvolutionNarrow.cpp
	g++ -c ./src/densityEvolutionNarrow.cpp -o ./lib/densityEvolutionNarrow.o -O3 -I./include -I./../Libraries/eigen -I./../Libraries/json/include
	g++ -o _densityEvolutionNarrow.out -O3 ./lib/densityEvolutionNarrow.o ./lib/1dMaps.o