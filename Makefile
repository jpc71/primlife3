# Makefile for Primordial Life Key Generator

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Target executable
TARGET = keygen.exe

# Source files
SOURCES = keygen.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Clean build artifacts
clean:
	del /Q *.o $(TARGET) 2>nul || echo Clean complete

# Run the program
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
