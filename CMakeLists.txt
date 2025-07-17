cmake_minimum_required(VERSION 3.16)
project(Investment_Simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add all .cpp files in src/ recursively
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Include directories (so headers like src/Accounts/Account.h are found)
include_directories(src)

# Define the executable and give it the correct name
add_executable(Investment_Simulator ${SOURCES})
