#pragma once

#include "Accounts/Account.h"
#include "json.hpp"
#include "Mortality/Period_Life_Data.h"
#include <string>

#define ACCOUNT(type) (household.accounts[static_cast<int>(type)])

// what does a household have?

// contributors (period life data)
// accounts
// household factors

// TODO: convert the above to a config file that household can read in

class Household
{
public:
    // Household(int starting_age_years, int starting_age_months, int starting_income);
    Household(std::string spec_path);

    void increment_portfolio(int month);
    // A household should have all the accounts wheather or not they are used for simplicity
    // different strategies may end up employing different accounts
    std::array<Account *, 5> accounts{};
    // TODO: would be nice if these could be const
    // TODO: extract into a contributor list?
    int birth_year;
    int starting_age_years;
    int starting_age_months;
    int starting_income;
    Sex sex;
    bool married;

    Period_Life_Data *period_life_data; // TODO: this should be a vector of period life data for each contributor


    std::unordered_map<Accounts, Account*> portfolio;
    // TODO: household debug print function
};

extern thread_local Household *household;
