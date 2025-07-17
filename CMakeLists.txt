# cmake_minimum_required(VERSION 3.16)
# project(Investment_Simulator LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# # Add all .cpp files in src/ recursively
# file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# # Include directories (so headers like src/Accounts/Account.h are found)
# include_directories(src)

# # Define the executable and give it the correct name
# add_executable(Investment_Simulator ${SOURCES})

cmake_minimum_required(VERSION 3.16)
project(Investment_Simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Multithreading Option ---
# This defines a CMake variable 'MULTITHREADING_ENABLED'.
# Its value will be set by the shell script via -DMULTITHREADING_ENABLED=ON/OFF.
# 'OFF' is the default if CMake is run directly without the script setting the variable.
option(MULTITHREADING_ENABLED "Enable multithreading features" OFF)

# Add all .cpp files in src/ recursively
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Include directories (so headers like src/Accounts/Account.h are found)
include_directories(src)

# Define the executable and give it the correct name
add_executable(Investment_Simulator ${SOURCES})

# --- Conditional Multithreading Setup for Investment_Simulator target ---
if(MULTITHREADING_ENABLED)
    message(STATUS "Multithreading enabled for Investment_Simulator.")
    # Define the preprocessor macro 'MULTITHREADING_ENABLED'
    # in your C++ code when the CMake variable MULTITHREADING_ENABLED is ON.
    target_compile_definitions(Investment_Simulator PRIVATE
        MULTITHREADING_ENABLED
    )

    # Find and link against the standard C++ threading library.
    find_package(Threads REQUIRED)
    target_link_libraries(Investment_Simulator PRIVATE Threads::Threads)
else()
    message(STATUS "Multithreading NOT enabled for Investment_Simulator.")
endif()
