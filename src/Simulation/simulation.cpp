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
#define WITHDRAW(account, ef, amount) (account)
// #define TRANSFER(from_account, from_ef, to_account, to_ef, amount) ()

thread_local HYSA *hysa;
void simulate_month(int index)
{
    // step 1: earn income
    double income = household->starting_income/12.0; // actually compute income
    DEPOSIT(Accounts::Checking, Economic_Factors::Cash, income);
    int cash_on_hand = household->portfolio[Accounts::Checking]->total_balance();

    // step 2: pay expenses
    double expenses = 1000; // actually compute expenses
    WITHDRAW(Accounts::Checking, Economic_Factors::Cash, expenses);

    // step 3: distribute remainder according to the strategy



    // step N: increment all accounts
    household->increment_portfolio(index);
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
