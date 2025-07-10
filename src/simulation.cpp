#include "foo.h"
#include <iostream>
#include <random>
#include <chrono>
#include <Period_Life_Data.h>
#include "global_rng.h"

void simulate_month() {}

void simulate_lifetime(Period_Life_Data period_life_data)
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
        int month_of_death_test = distrib_month(global_RNG); // Random month for an attempt (0-11)

        for (int month_index = 0; month_index < 12; ++month_index)
        {
            // Check if this is the designated month for an attempted murder AND if it's successful
            if (month_index == month_of_death_test && period_life_data.did_die_at_age(years_old))
            {
                // The user died
                std::cout << "Final Age (years, months): (" << years_old << ", " << month_index << ")" << std::endl;
                return; // Exit the function
            }

            simulate_month();

            months_old++;
        }

        years_old++;
    }
}