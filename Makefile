# Compiler and flags
CXX = g++
CXXFLAGS_DEBUG = -Wall -Isrc -g -std=c++20
CXXFLAGS_FAST = -Wall -Isrc -O3 -DNDEBUG -std=c++20

# Build Directory
BUILD_DIR = build

# Source files: find all .cpp files recursively in src/
SRC = $(shell find src -name "*.cpp")

# Object files: replace src/ with $(BUILD_DIR)/ and .cpp with .o
OBJ = $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

# Target executable name
TARGET = $(BUILD_DIR)/my_program

.PHONY: all debug release clean pre-build run bench demo

# Default target: release build
all release: CXXFLAGS = $(CXXFLAGS_FAST)
all release: pre-build $(TARGET) # Add pre-build dependency here

# Debug target: debug build
debug: CXXFLAGS = $(CXXFLAGS_DEBUG)
debug: pre-build $(TARGET) # Add pre-build dependency here

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

# Run the compiled program.
# This target now explicitly depends on $(TARGET) to ensure it exists,
# but it doesn't trigger a *rebuild* unless $(TARGET) is out of date.
# If you truly want 'run' to *never* build, even if the target is missing,
# then you remove the $(TARGET) dependency, but 'make run' would then fail if no executable exists.
# For typical usage, keeping $(TARGET) as a prerequisite is safer,
# as 'make' will only re-link if sources have changed.
run: $(TARGET) # Ensure the target executable exists and is up-to-date (based on last build)
	@echo "Running $(TARGET)..."
	@./$(TARGET)

# Benchmark the compiled program with hyperfine
bench: release # Ensure the program is built in release mode
	@echo "Benchmarking $(TARGET)..."
	@hyperfine ./$(TARGET) --warmup 2

# Demo target: Builds in release mode and then runs.
# This is the correct way to ensure a fresh release build before running.
demo: release
	@echo "Building and running demo..."
	@./$(TARGET)

# Clean up build artifacts (for manual cleaning)
clean:
	@echo "Manually cleaning build directory..."
	@rm -rf $(BUILD_DIR)