#include <iostream>
#include <random>
#include <chrono>
#include "Accounts/Account.h"
#include "Mortality/Period_Life_Data.h"
#include "global_rng.h"
#include "Accounts/HYSA.h"
#include "simulation.h"
#include "Household/Household.h"

#define DEPOSIT(account, ef, amount) (household->portfolio[account]->deposit(amount, ef))

thread_local HYSA *hysa;
void simulate_month(int index)
{
    double income = household->starting_income/12.0;
    DEPOSIT(Accounts::Checking, Economic_Factors::Cash, income);





    // TODO: increment all accounts
    // household->increment_portfolio();
}

// TODO: it would be nice if simulate_lifetime took a household, a government, and an economy
void simulate_lifetime()
{
    hysa = new HYSA();
    std::uniform_int_distribution<> distrib_month(0, 11);

    int years_old = household->starting_age_years;
    // TODO: take into account starting age months
    int month_count = 0;

    while (true) // alive
    {
        int month_of_death_test = distrib_month(*global_RNG);

        for (int month_of_year = 0; month_of_year < 12; ++month_of_year)
        {
            // Check if this is the designated month for an attempted murder AND if it's successful
            if (month_of_year == month_of_death_test && household->period_life_data->did_die_at_age(years_old))
            {
                // The user died
                // std::cout << "Final Age (years, months): (" << years_old << ", " << month_of_year << ")" << std::endl;
                // hysa->print_balances();
                delete hysa;
                return; // Exit the function
            }

            simulate_month(month_count);

            month_count++;
        }

        years_old++;
    }
}
