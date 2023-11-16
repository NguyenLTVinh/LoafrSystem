# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -I. -std=c++17

# Source files
SOURCES = $(wildcard */*.cc) main.cc

# Object files
OBJECTS = $(SOURCES:.cc=.o)

# Executable name
EXEC = loafr

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXEC)
