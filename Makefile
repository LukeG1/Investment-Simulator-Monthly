# Compiler and flags
CXX = g++
CXXFLAGS_DEBUG = -Wall -Iinclude -g -std=c++20
CXXFLAGS_FAST  = -Wall -Iinclude -O3 -DNDEBUG -std=c++20

# Mode selection
MODE ?= debug

ifeq ($(MODE),debug)
	CXXFLAGS := $(CXXFLAGS_DEBUG)
else ifeq ($(MODE),fast)
	CXXFLAGS := $(CXXFLAGS_FAST)
else
	$(error Unknown MODE '$(MODE)'. Valid options are 'debug' or 'fast')
endif

# File and target definitions
SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = build/my_program

# Force rebuild if MODE changes
MODE_FILE = build/.mode_$(MODE)

all: $(TARGET)

# Rule to build the target
$(TARGET): $(SRC) $(MODE_FILE)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Create a marker file to track the current mode
$(MODE_FILE):
	@mkdir -p build
	@rm -f build/.mode_*  # Remove old mode marker
	@touch $@

clean:
	rm -f build/my_program build/.mode_*

# Shortcuts
fast:
	$(MAKE) MODE=fast

debug:
	$(MAKE) MODE=debug
