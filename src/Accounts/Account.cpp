#include "Account.h"
#include <iomanip>
#include <sstream>

Account::~Account()
{
    for (auto &inv : investments)
    {
        delete inv;
    }
}

void Account::deposit(double amount, Economic_Factors ef)
{
    int idx = static_cast<int>(ef);
    Investment *depositing_investment = investments[idx];
    // std::cout << "Depositing " << amount << " into " << static_cast<int>(ef) << std::endl;
    if (depositing_investment && amount <= max_contribution())
    {
        depositing_investment->balance += amount;
    }
}

void Account::increment(int month)
{
    for (auto &investment : investments)
    {
        if (investment)
        {
            double monthly_return = investment->economic_factor->get_return(month, false);
            investment->balance *= (1 + monthly_return);
        }
    }
}

void Account::print_balances()
{
    for (int i = 0; i < num_factors; ++i)
    {
        if (investments[i])
        {
            std::cout << "Balance for " << static_cast<int>(static_cast<Economic_Factors>(i)) << ": $"
                      << std::fixed << std::setprecision(2)
                      << std::showbase << investments[i]->balance << std::endl;
        }
    }
};