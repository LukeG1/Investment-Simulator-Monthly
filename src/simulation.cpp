#include "foo.h"
#include <iostream>
#include <random>
#include <chrono>

bool attempt_murder(int age)
{
    // rng for death chance
    std::random_device rd;                           // create random generator
    std::mt19937 gen(rd());                          // Seed with a random_device
    std::uniform_int_distribution<> distrib(0, 100); // set min and max

    // TODO: Fill in with period
    float random_number = distrib(gen) / 100.0;
    if (random_number < .03)
    {
        return true;
    }
    return false;
}

void simulate_month() {}

void simulate_lifetime()
{
    // rng for the month of attempted murder (0-11 for January-December)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib_month(0, 11);

    const int starting_age_years = 26;
    int years_old = starting_age_years;
    int months_old = 0;

    while (true) // alive
    {
        int month_of_attempted_murder = distrib_month(gen); // Random month for an attempt (0-11)

        for (int month_index = 0; month_index < 12; ++month_index)
        {
            // Check if this is the designated month for an attempted murder AND if it's successful
            if (month_index == month_of_attempted_murder && attempt_murder(years_old))
            {
                // The user died
                // std::cout << "Final Age (years, months): (" << years_old << ", " << month_index << ")" << std::endl;
                return; // Exit the function
            }

            simulate_month();

            months_old++;
        }

        years_old++;
    }
}