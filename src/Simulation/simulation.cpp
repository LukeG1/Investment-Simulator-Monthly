#include <iostream>
#include <random>
#include <chrono>
#include "Mortality/Period_Life_Data.h"
#include "global_rng.h"
#include "Accounts/HYSA.h"

auto account = HYSA();

void simulate_month(int index)
{
    account.deposit(100, Economic_Factors::Stock_Market);
    account.increment(index);
}

// TODO: it would be nice if simulate_lifetime took a household, a government, and an economy
void simulate_lifetime(Period_Life_Data period_life_data)
{
    // rng for the month of attempted murder (0-11 for January-December)
    std::uniform_int_distribution<> distrib_month(0, 11);

    const int starting_age_years = 26;
    int years_old = starting_age_years;
    int month_count = 0;

    while (true) // alive
    {
        int month_of_death_test = distrib_month(global_RNG); // Random month for an attempt (0-11)

        for (int month_of_year = 0; month_of_year < 12; ++month_of_year)
        {
            // Check if this is the designated month for an attempted murder AND if it's successful
            if (month_of_year == month_of_death_test && period_life_data.did_die_at_age(years_old))
            {
                // The user died
                // std::cout << "Final Age (years, months): (" << years_old << ", " << month_of_year << ")" << std::endl;
                // account.print_balances();
                return; // Exit the function
            }

            simulate_month(month_count);

            month_count++;
        }

        years_old++;
    }
}