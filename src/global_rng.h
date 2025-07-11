#pragma once

#include <random>

// could also be replaced with .seed(<a number>)
// by refactoring this to thread_local multithreading could be relatively simple?
extern std::mt19937 global_RNG;
