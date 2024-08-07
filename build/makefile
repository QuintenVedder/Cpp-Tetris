include makefile.variables

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


