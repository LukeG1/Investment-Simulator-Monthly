#include "Accounts/Account.h"
#include "HYSA.h"
#include "Economy/Economy.h"

HYSA::HYSA()
{
    // TODO: consider making this into some kind of macro
    // investments[static_cast<int>(Economic_Factors::Cash)] = new Investment{0.0f, nullptr};
    investments[static_cast<int>(Economic_Factors::Stock_Market)] = new Investment{0.0f, &economy->stock_market};
    investments[static_cast<int>(Economic_Factors::Bonds)] = new Investment{0.0f, &economy->bonds};
}

double HYSA::max_contribution() // TODO: implement
{
    return 10'000.0f;
}

void HYSA::withdrawal(double amount, Economic_Factors ef)
{
    // TODO: consider tax implications
    int idx = static_cast<int>(ef);
    Investment *withdrawaling_investment = investments[idx];
    if (withdrawaling_investment && amount <= withdrawaling_investment->balance)
    {
        withdrawaling_investment->balance -= amount;
    }
}