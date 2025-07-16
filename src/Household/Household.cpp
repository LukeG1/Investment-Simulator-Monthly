#include "Household.h"
#include "Accounts/HYSA.h"

Household::Household(int starting_age_years, int starting_age_months, int starting_income)
    : starting_age_years(starting_age_years), starting_age_months(starting_age_months), starting_income(starting_income)
{
    // TODO: implement all accounts from the enum and add verification or find a cleaner solution
    accounts[static_cast<int>(Accounts::HYSA)] = new HYSA();
}