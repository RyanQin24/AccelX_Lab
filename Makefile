# Compiler to use
CXX = g++

# Compiler flags:
# -Wall     = show common warnings
#-Iincludes = include directory
CXXFLAGS = -Wall -Iincludes

# Final program name
TARGET = main.exe

# Object files to build before linking
OBJ = bin/main.o bin/CommandParser.o

# Default target.
# This runs when you type: mingw32-make
all: $(TARGET)

# Link step:
# main.exe depends on main.o and CommandParser.o
# If either .o file changes, relink main.exe
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Compile main.cpp into main.o
# Rebuild main.o if main.cpp or CommandParser.h changes
bin/main.o: main.cpp includes/CommandParser.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o bin/main.o

# Compile CommandParser.cpp into CommandParser.o
# Rebuild CommandParser.o if CommandParser.cpp or CommandParser.h changes
bin/CommandParser.o: CommandParser.cpp includes/CommandParser.h
	$(CXX) $(CXXFLAGS) -c CommandParser.cpp -o bin/CommandParser.o
