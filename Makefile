EXE=analog
INT=CommandReader.h ApacheLogFileParser.h GraphString.h
SRC=$(INT:.h=.cpp)
OBJ=$(INT:.h=.o)
	
MainSRC=main.cpp
MainOBJ=$(MainSRC:.cpp=.o)
	
ECHO=@echo

Compilator=@g++
CompilationsOptions=-Wall -pedantic -std=c++11
Linker=@g++
LinkerOptions=

$(EXE): $(MainOBJ) $(OBJ)
	$(ECHO) "Edition des liens de $(EXE)"
	$(Linker) -o $(EXE) $(MainOBJ) $(OBJ) $(LinkerOptions)

$(MainOBJ): $(MainSRC) $(INT)
	$(ECHO) "Compilation de $(MainSRC)"
	$(Compilator) -o $(MainOBJ) -c $(MainSRC) $(CompilationsOptions)

%.o: %.cpp
	$(ECHO) "Compilation de $<"
	$(Compilator) -c $< $(CompilationsOptions)
	
# ***** TESTS ***** #
TestTARGET=tests
TestsSRCDir=./Unit_Tests/
TestsEXEDir=$(TestsSRCDir)

TestsSRC=$(TestsSRCDir)TCommandReader.cpp TGraphString.cpp
TestsOBJ=$(TestsSRC:.cpp=.o)

TestsEXE=$(TestsEXEDir)TCommandReader $(TestsEXEDir)TGraphString

$(TestTARGET): $(TestsEXE)

# Compilation : COMMAND READER test #
$(TestsEXEDir)TCommandReader: $(TestsSRCDir)TCommandReader.o CommandReader.o
	$(ECHO) "Edition des liens de $(TestsEXEDir)TCommandReader"
	$(Linker) -o $(TestsEXEDir)TCommandReader $(TestsSRCDir)TCommandReader.o CommandReader.o

$(TestsSRCDir)TCommandReader.o: $(TestsSRCDir)TCommandReader.cpp
	$(ECHO) "Compilation de $(TestsSRCDir)TCommandReader.cpp"
	$(Compilator) -o $(TestsSRCDir)TCommandReader.o -c $(TestsSRCDir)TCommandReader.cpp $(CompilationsOptions)

# Compilation : GRAPH STRING test #
$(TestsEXEDir)TGraphString: $(TestsSRCDir)TGraphString.o GraphString.o
	$(ECHO) "Edition des liens de $(TestsEXEDir)TGraphString"
	$(Linker) -o $(TestsEXEDir)TGraphString $(TestsSRCDir)TGraphString.o GraphString.o

$(TestsSRCDir)TGraphString.o: $(TestsSRCDir)TGraphString.cpp
	$(ECHO) "Compilation de $(TestsSRCDir)TGraphString.cpp"
	$(Compilator) -o $(TestsSRCDir)TGraphString.o -c $(TestsSRCDir)TGraphString.cpp $(CompilationsOptions)
	
# ***** CLEAN ***** #
CLEAN=clean
RM=rm
RMFlags=-f

.PHONY: $(CLEAN)
$(CLEAN):
	$(RM) $(RMFlags) $(EXE) $(OBJ) $(MainOBJ) $(TestsEXE) $(TestsOBJ)