#include "Account.h"
#include <iomanip>
#include <sstream>

void Account::deposit(double amount, Economic_Factors ef)
{
    // TODO: household considerations (how much can they deposit?)
    auto check_balance = balances.find(ef);
    if(check_balance != balances.end() && amount <=max_contribution()){
        check_balance->second += amount;
    }
    // std::cout << "Depositing " << amount << " into " << static_cast<int>(ef) << std::endl;
}

void Account::increment(int month)
{
    for (auto& pair : balances) {
        auto* factor = economy->factors[static_cast<int>(pair.first)];
        double monthly_return = factor->get_return(month, false);
        pair.second *= (1 + monthly_return);
    }
}

void Account::print_balances()
{

    for (const auto& pair : balances) {
        std::cout << "Balance for " << static_cast<int>(static_cast<Economic_Factors>(pair.first)) << ": $"
                  << std::fixed << std::setprecision(2)
                  << std::showbase << pair.second << std::endl;
    }
};


double Account::total_balance()
{
    double total = 0.0;
    for (const auto& pair : balances) {
        total += pair.second;
    }

    return total;
};
