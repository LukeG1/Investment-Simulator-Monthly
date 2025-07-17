#include "Accounts/Account.h"
#include "HYSA.h"
#include "Economy/Economy.h"

HYSA::HYSA()
{
    ALLOW_ACCOUNT(Economic_Factors::Stock_Market);
}

double HYSA::max_contribution() // TODO: implement
{
    return std::numeric_limits<double>::max();
}

void HYSA::withdrawal(double amount, Economic_Factors ef)
{
    // TODO: consider tax implications
    int idx = static_cast<int>(ef);
    if (allowed_factors.test(idx) && amount <= balances[idx])
    {
        balances[idx] -= amount;
    }
};

double HYSA::tot()
{
    double total = balances[static_cast<int>(Economic_Factors::Stock_Market)];
    return total;
}
