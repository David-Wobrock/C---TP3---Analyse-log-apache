CompilationsOptions=-Wall -pedantic

analog: main.o CommandReader.o
	g++ -o analog main.o CommandReader.o

main.o: main.cpp CommandReader.h
	g++ -o main.o -c main.cpp $(CompilationsOptions)

CommandReader.o: CommandReader.cpp CommandReader.h
	g++ -o CommandReader.o -c CommandReader.cpp $(CompilationsOptions)
	
# ***** TESTS ***** #
testsSrcDir=./testsSrc/
CommandReaderTestDir=./Tests/Test_CommandReader/

tests: $(CommandReaderTestDir)TCommandReader

$(CommandReaderTestDir)TCommandReader: $(testsSrcDir)TCommandReader.o CommandReader.o
	g++ -o $(CommandReaderTestDir)TCommandReader $(testsSrcDir)TCommandReader.o CommandReader.o

$(testsSrcDir)TCommandReader.o: $(testsSrcDir)TCommandReader.cpp
	g++ -o $(testsSrcDir)TCommandReader.o -c $(testsSrcDir)TCommandReader.cpp $(CompilationsOptions)
	
	
# ***** CLEAN ***** #
.PHONY: clean
clean:
	rm -f analog #...