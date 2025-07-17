#include "Account.h"
#include <iomanip>
#include <sstream>

void Account::deposit(double amount, Economic_Factors ef)
{
    // TODO: household considerations (how much can they deposit?)
    int idx = static_cast<int>(ef);
    if (allowed_factors.test(idx) && amount <= max_contribution())
    {
        balances[idx] += amount;
    }
    // std::cout << "Depositing " << amount << " into " << static_cast<int>(ef) << std::endl;
}

void Account::increment(int month)
{
    for(int i =0; i<num_factors; i++){
        // not sure if this should stay long term
        if(!economy->factors[i])
            continue;
        double monthly_return = economy->factors[i]->get_return(month, false);
        balances[i] *= (1 + monthly_return);
    }
}

void Account::print_balances()
{

    for (int i = 0; i < balances.size(); ++i)
    {
        if (allowed_factors.test(i))
        {
            std::cout << "Balance for " << static_cast<int>(static_cast<Economic_Factors>(i)) << ": $"
                      << std::fixed << std::setprecision(2)
                      << std::showbase << balances[i] << std::endl;
        }
    }
};
