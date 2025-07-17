#include "Accounts/Account.h"
#include "Checking.h"
#include "Economy/Economy.h"
#include "Household/Household.h"

Checking::Checking()
{
    balances[Economic_Factors::Cash] = 0.0;
}

double Checking::max_contribution() // TODO: implement
{
    return std::numeric_limits<double>::max();
}

void Checking::withdrawal(double amount, Economic_Factors ef)
{
};
