# Compiler to use
CXX = g++

# Compiler flags:
# -Wall     = show common warnings
#-Iincludes = include directory
CXXFLAGS = -Wall -Iincludes

# Final program name
TARGET = main.exe

# Object files to build before linking
OBJ = bin/main.o bin/CommandParser.o bin/TimeSeries.o bin/Trapezoidal.o bin/Back4pt.o

# Default target.
# This runs when you type: mingw32-make
all: $(TARGET)

# Link step:
# main.exe depends on object files
# If either .o file changes, relink main.exe
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Compile main.cpp into main.o
# Rebuild main.o if main.cpp or CommandParser.h changes
bin/main.o: main.cpp includes/CommandParser.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o bin/main.o

# Compile CommandParser.cpp into CommandParser.o
# Rebuild CommandParser.o if CommandParser.cpp, CommandParser.h, or TimeSeries.h changes
bin/CommandParser.o: CommandParser.cpp includes/CommandParser.h includes/TimeSeries.h
	$(CXX) $(CXXFLAGS) -c CommandParser.cpp -o bin/CommandParser.o

# Compile TimeSeries.cpp into TimeSeries.o
bin/TimeSeries.o: TimeSeries.cpp includes/TimeSeries.h includes/Trapezoidal.h includes/Back4pt.h
	$(CXX) $(CXXFLAGS) -c TimeSeries.cpp -o bin/TimeSeries.o

# Compile Trapezoidal.cpp into Trapezoidal.o
bin/Trapezoidal.o: includes/Trapezoidal.h Integral_Op/Trapezoidal.cpp
	$(CXX) $(CXXFLAGS) -c Integral_Op/Trapezoidal.cpp -o bin/Trapezoidal.o

# Compile Back4pt.cpp into Back4pt.o
bin/Back4pt.o: includes/Back4pt.h Integral_Op/Back4pt.cpp
	$(CXX) $(CXXFLAGS) -c Integral_Op/Back4pt.cpp -o bin/Back4pt.o