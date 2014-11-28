COMPILATIONOPTIONS=-Wall -pedantic

analog: main.o CommandReader.o
	g++ -o analog main.o CommandReader.o

main.o: main.cpp CommandReader.h
	g++ -o main.o -c main.cpp $(COMPILATIONOPTIONS)

CommandReader.o: CommandReader.cpp
	g++ -o CommandReader.o -c CommandReader.cpp $(COMPILATIONOPTIONS)