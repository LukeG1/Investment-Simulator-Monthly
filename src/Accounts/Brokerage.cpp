#include "Accounts/Account.h"
#include "Brokerage.h"
#include "Economy/Economy.h"
#include "Household/Household.h"

Brokerage::Brokerage()
{
    balances[Economic_Factors::Stock_Market] = 0.0;
    balances[Economic_Factors::Bonds] = 0.0;
}

double Brokerage::max_contribution() // TODO: implement
{
    return std::numeric_limits<double>::max();
}

void Brokerage::withdrawal(double amount, Economic_Factors ef)
{
};
