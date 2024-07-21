# Compiler
CXX = g++
CXX_WIN = x86_64-w64-mingw32-g++

# Compiler flags
CXXFLAGS = -std=c++17 -static-libstdc++

# SFML Paths
SFML_INC_LINUX = /usr/include
SFML_LIB_LINUX = /usr/lib

SFML_INC_WIN = "/path/to/sfml"/include
SFML_LIB_WIN = "/path/to/sfml"/lib

# SFML Libraries
SFML_LIBS = -lsfml-graphics -lsfml-system -lsfml-window

# Source files
SRCS = ../src/main.cpp

# Target executables
TARGET_LINUX = ../Tetris-linux-mac
TARGET_WIN = ../Tetris-windows.exe

# Default target
all: $(TARGET_LINUX) $(TARGET_WIN)

# Rule to build the Linux target executable
$(TARGET_LINUX): $(SRCS)
	$(CXX) $(CXXFLAGS) -I$(SFML_INC_LINUX) -L$(SFML_LIB_LINUX) -o $(TARGET_LINUX) $(SRCS) $(SFML_LIBS)

# Rule to build the Windows target executable
$(TARGET_WIN): $(SRCS)
	$(CXX_WIN) $(CXXFLAGS) -I$(SFML_INC_WIN) -L$(SFML_LIB_WIN) -o $(TARGET_WIN) $(SRCS) $(SFML_LIBS)

# Rule to run the Linux executable
run: $(TARGET_LINUX)
	./$(TARGET_LINUX)

# Clean up build files
clean:
	rm -f $(TARGET_LINUX) 
	rm -f $(TARGET_WIN)

# Rule to clean->build->run for Linux
cbr: clean all run

# Prevent make from interpreting file names as targets
.PHONY: all run clean cbr


