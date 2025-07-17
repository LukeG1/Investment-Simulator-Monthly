#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Define the build directory
BUILD_DIR="build"

# Default build type
BUILD_TYPE="Release"

# Initialize multithreading variable (default: OFF)
MULTITHREADING_ENABLED="OFF"

# --- Process arguments ---

# First argument: Build type (debug or release)
if [ -n "$1" ]; then
    LOWER_ARG_TYPE=$(echo "$1" | tr '[:upper:]' '[:lower:]')
    case "$LOWER_ARG_TYPE" in
        debug)
            BUILD_TYPE="Debug"
            ;;
        release)
            BUILD_TYPE="Release"
            ;;
        *)
            echo "Error: Invalid build type specified: $1"
            echo "Usage: ./build.sh [debug|release] [enable_multithreading (use 'mt')]"
            exit 1
            ;;
    esac
fi

# Second argument: Enable multithreading
if [ -n "$2" ]; then
    LOWER_ARG_MT=$(echo "$2" | tr '[:upper:]' '[:lower:]')
    if [ "$LOWER_ARG_MT" == "mt" ]; then
        MULTITHREADING_ENABLED="ON"
    else
        echo "Error: Invalid multithreading flag: $2"
        echo "Usage: ./build.sh [debug|release] [enable_multithreading (use 'mt')]"
        exit 1
    fi
fi

# --- Auto-detect CPU cores for parallel building ---
# This section now runs unconditionally to set PARALLEL_LEVEL
PARALLEL_LEVEL=""
if command -v nproc &> /dev/null; then
    PARALLEL_LEVEL=$(nproc)
    echo "Auto-detecting CPU cores: Using $PARALLEL_LEVEL parallel jobs."
elif command -v sysctl &> /dev/null && sysctl -n hw.ncpu &> /dev/null; then
    PARALLEL_LEVEL=$(sysctl -n hw.ncpu)
    echo "Auto-detecting CPU cores (macOS): Using $PARALLEL_LEVEL parallel jobs."
else
    echo "Warning: Could not auto-detect number of CPU cores. Building without explicit parallel flag."
    PARALLEL_LEVEL="" # Ensure it's empty so -j isn't passed
fi

# --- Construct CMake build command flags ---
CMAKE_BUILD_FLAGS=""
if [ -n "$PARALLEL_LEVEL" ]; then
    CMAKE_BUILD_FLAGS+=" --parallel $PARALLEL_LEVEL"
fi

echo "--- Configuring CMake project for $BUILD_TYPE mode ---"
echo "Multithreading: $MULTITHREADING_ENABLED"
cmake -S . -B "$BUILD_DIR" \
      -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
      -DMULTITHREADING_ENABLED="$MULTITHREADING_ENABLED" # Pass MT flag to CMake

echo "" # Add an empty line for better readability

echo "--- Building project ---"
cmake --build "$BUILD_DIR" $CMAKE_BUILD_FLAGS

echo ""
echo "--- Build process completed for $BUILD_TYPE ---"
