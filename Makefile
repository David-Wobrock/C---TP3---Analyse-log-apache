EXE=analog
INT=CommandReader.h #ApacheLogFileParser.h
SRC=$(INT:.h=.cpp)
OBJ=$(INT:.h=.o)
	
MainSRC=main.cpp
MainOBJ=$(MainSRC:.cpp=.o)
	
ECHO=@echo

Compilator=g++
CompilationsOptions=-Wall -pedantic
Linker=g++
LinkerOptions=

$(EXE): $(MainOBJ) $(OBJ)
	$(Linker) -o $(EXE) $(MainOBJ) $(OBJ) $(LinkerOptions)

$(MainOBJ): $(MainSRC) $(INT)
	$(ECHO) "Compilation de $(MainSRC)"
	$(Compilator) -o $(MainOBJ) -c $(MainSRC) $(CompilationsOptions)

%.o: %.cpp
	$(ECHO) "Compilation de $<"
	$(Compilator) -c $< $(CompilationsOptions)
	
# ***** TESTS ***** #
TestTARGET=tests
TestsSRCDir=./testsSrc/
TestsEXEDir=./Tests/

TestsSRC=$(TestsSRCDir)TCommandReader.cpp
TestsOBJ=$(TestsSRC:.cpp=.o)

CommandReaderTestDir=$(TestsEXEDir)Test_CommandReader/


TestsEXE=$(CommandReaderTestDir)TCommandReader

$(TestTARGET): $(TestsEXE)

# Comp : COMMAND READER test #
$(CommandReaderTestDir)TCommandReader: $(TestsSRCDir)TCommandReader.o CommandReader.o
	$(Linker) -o $(CommandReaderTestDir)TCommandReader $(TestsSRCDir)TCommandReader.o CommandReader.o

$(TestsSRCDir)TCommandReader.o: $(TestsSRCDir)TCommandReader.cpp
	$(Compilator) -o $(TestsSRCDir)TCommandReader.o -c $(TestsSRCDir)TCommandReader.cpp $(CompilationsOptions)
	
	
# ***** CLEAN ***** #
CLEAN=clean
RM=rm
RMFlags=-f
.PHONY: $(CLEAN)
$(CLEAN):
	$(RM) $(RMFlags) $(EXE) $(OBJ) $(MainOBJ) $(TestsEXE) $(TestsOBJ)