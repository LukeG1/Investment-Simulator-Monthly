#include "Accounts/Account.h"
#include "Brokerage.h"
#include "Economy/Economy.h"

Brokerage::Brokerage()
{
    investments[static_cast<int>(Economic_Factors::Stock_Market)] = new Investment{0.0f, &economy->stock_market};
    investments[static_cast<int>(Economic_Factors::Bonds)] = new Investment{0.0f, &economy->bonds};
}

double Brokerage::max_contribution()
{
    // Brokerage accounts typically have no contribution limits.
    // Returning a very large number to represent effectively unlimited contributions.
    return 1'000'000'000'000.0f; // A large number to signify no practical limit
}

void Brokerage::withdrawal(double amount, Economic_Factors ef)
{
    // TODO: consider tax implications for brokerage withdrawals
    int idx = static_cast<int>(ef);
    Investment *withdrawaling_investment = investments[idx];
    if (withdrawaling_investment && amount <= withdrawaling_investment->balance)
    {
        withdrawaling_investment->balance -= amount;
    }
};

double Brokerage::tot()
{
    // Calculate total balance from all invested economic factors
    double total = 0.0f;
    for (int i = 0; i < static_cast<int>(Economic_Factors::COUNT); ++i)
    {
        if (investments[i])
        {
            total += investments[i]->balance;
        }
    }
    return total;
}