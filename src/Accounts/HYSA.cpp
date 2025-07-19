#include "HYSA.h"
#include "Accounts/Account.h"
#include "Economy/Economy.h"
#include "Household/Household.h"

HYSA::HYSA()
{
    balances[Economic_Factors::High_Savings_Rate] = 0.0;
}

double HYSA::max_contribution() // TODO: implement
{
    return std::numeric_limits<double>::max();
}

void HYSA::withdrawal(double amount, Economic_Factors ef){
    // TODO: consider tax implications
    // int idx = static_cast<int>(ef);
    // if (allowed_factors.test(idx) && amount <= balances[idx])
    // {
    //     balances[idx] -= amount;
    // }
};

double HYSA::tot()
{
    double total = balances[Economic_Factors::High_Savings_Rate];
    return total;
}
