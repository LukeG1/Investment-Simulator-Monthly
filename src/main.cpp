#include "Economy/Economy.h"
#include "Household/Household.h"
#include "Simulation/simulation.h"
#include "global_rng.h"
#include <random>

int num_simulations = 1;

#ifndef MULTITHREADING_ENABLED
// this is the economy that will be accessed everywhere
// TODO: should probably be refactored to not be global, or thread_local
// household could also be thread_local therefore not passed so much?
thread_local std::mt19937 *global_RNG;
thread_local Economy *economy;
thread_local Household *household;
int main(int argc, char *argv[])
{
    // TODO: check that there is exactly one argument
    global_RNG = new std::mt19937(std::random_device{}());
    economy = new Economy();
    household = new Household(argv[1]);

    for (auto _ = 0; _ < num_simulations; _++)
        simulate_lifetime();
        // reset somehow?

    return 0;

}
#endif

#ifdef MULTITHREADING_ENABLED

#include <iostream>
#include <vector>
#include <thread>
#include <numeric> // For std::iota

// thread_local variables
thread_local std::mt19937 *global_RNG;
thread_local Economy *economy;
thread_local Household *household;

// Function that each thread will execute
void run_simulations_for_thread(int num_simulations_per_thread, const char
*household_spec_file)
{
    // std::cout << "before globals" << std::endl;
    global_RNG = new std::mt19937(std::random_device{}());
    economy = new Economy();
    household = new Household(household_spec_file);
    // std::cout << "after globals" << std::endl;

    for (int i = 0; i < num_simulations_per_thread; ++i)
    {
        simulate_lifetime();
    }

    // Clean up per-thread resources
    delete household;
    delete economy;
    delete global_RNG;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <household_spec_file>" <<
        std::endl; return 1;
    }

    const int total_simulations = num_simulations;
    unsigned int num_threads = std::thread::hardware_concurrency(); // Get

    int simulations_per_thread = total_simulations / num_threads;
    int remaining_simulations = total_simulations % num_threads;

    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    for (unsigned int i = 0; i < num_threads; ++i)
    {
        int current_thread_sims = simulations_per_thread;
        if (i < remaining_simulations)
        { // Distribute remaining simulations to the first few threads
            current_thread_sims++;
        }
        threads.emplace_back(run_simulations_for_thread, current_thread_sims,
        argv[1]);
    }

    for (std::thread &t : threads)
    {
        if (t.joinable())
        {
            t.join();
        }
    }

    std::cout << total_simulations << " lifetime simulations completed using " << num_threads << " threads." << std::endl; return 0;
}
#endif
