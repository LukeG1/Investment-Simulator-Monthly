#include "Account.h"
#include <iomanip>
#include <sstream>

void Account::deposit(double amount, Economic_Factors ef)
{
    // TODO: household considerations (how much can they deposit?)
    auto check_balance = balances.find(ef);
    if (check_balance != balances.end() && amount <= max_contribution())
    {
        check_balance->second += amount;
    }
    // std::cout << "Depositing " << amount << " into " << static_cast<int>(ef) << std::endl;
}

void Account::increment(int month)
{
    // TODO: remove extra map index
    for (const auto &[ef, balance] : balances)
    {
        auto *factor = economy->factors[static_cast<int>(ef)];
        double monthly_return = factor->get_return(month, false);
        balances[ef] *= (1 + monthly_return);
    }
}

void Account::print_balances()
{
    for (const auto &[ef, balance] : balances)
    {
        std::cout << "Balance for " << static_cast<int>(static_cast<Economic_Factors>(ef)) << ": $" << std::fixed
                  << std::setprecision(2) << std::showbase << balance << std::endl;
    }
};

double Account::total_balance()
{
    double total = 0.0;
    for (const auto &[ef, balance] : balances)
    {
        total += balance;
    }

    return total;
};
