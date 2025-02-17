# Compiler und Flags 
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2

# Targets
TARGET = word_counter_tests
SOURCES = tests.cpp
#HEADERS = RedBlackTree.h
OBJECTS = $(SOURCES:.cpp=.o)

# Standard Build
all: $(TARGET)

# Erstelle das Hauptprogramm
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	./$(TARGET)

# Kompiliere Objektdateien
#%.o: %.cpp $(HEADERS)
#	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean-up
clean:
	rm -f $(OBJECTS) $(TARGET) test_input.txt test_output.txt

# Phony Targets
.PHONY: all clean
