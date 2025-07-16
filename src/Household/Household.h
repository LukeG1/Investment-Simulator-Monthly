#pragma once
#include "Accounts/Account.h"

#define ACCOUNT(type) (household.accounts[static_cast<int>(type)])

// what does a household have?

// contributors (period life data)
// accounts
// household factors

// TODO: convert the above to a config file that household can read in

class Household
{
public:
    Household(int starting_age_years, int starting_age_months, int starting_income);
    // A household should have all the accounts wheather or not they are used for simplicity
    // different strategies may end up employing different accounts
    std::array<Account *, 5> accounts{};
    const int starting_age_years;
    const int starting_age_months;
    const int starting_income;

    // TODO: household debug print function
};