# Compiler and flags
CXX = g++
CXXFLAGS_DEBUG = -Wall -Iinclude -g -std=c++20
CXXFLAGS_FAST  = -Wall -Iinclude -O3 -DNDEBUG -std=c++20

# Build Directory
BUILD_DIR = build

# Source files: find all .cpp files recursively in src/
SRC = $(shell find src -name "*.cpp")

# Object files: replace src/ with $(BUILD_DIR)/ and .cpp with .o
OBJ = $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

# Target executable name
TARGET = $(BUILD_DIR)/my_program

.PHONY: all debug fast clean pre-build run

# Default target: debug build
all debug: CXXFLAGS = $(CXXFLAGS_DEBUG)
all debug: pre-build $(TARGET) # Add pre-build dependency here

# Fast target: optimized build
fast: CXXFLAGS = $(CXXFLAGS_FAST)
fast: pre-build $(TARGET) # Add pre-build dependency here

# Pre-build step to clean the build directory
pre-build:
	@echo "Cleaning build directory before build..."
	@rm -rf $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)

# Rule to create the build directory (redundant with pre-build, but harmless)
$(BUILD_DIR):
	@mkdir -p $@

# Rule to compile individual source files into object files
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to link object files into the final executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

# Run the compiled program (now uses the fast build)
run: fast # Ensure the program is built in fast mode
	@echo "Running $(TARGET)..."
	@./$(TARGET)

# Clean up build artifacts (for manual cleaning)
clean:
	@echo "Manually cleaning build directory..."
	@rm -rf $(BUILD_DIR)