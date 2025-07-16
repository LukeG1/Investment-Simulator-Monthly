#pragma once

#include "Accounts/Account.h"
#include "Economy/Economic_Factor.h"

// Declare the global stock_market variable as extern.
// This tells the compiler that the variable exists, but its definition
// (where memory is allocated for it) will be in a .cpp file.
class HYSA : public Account
{
public:
    // Constructor
    HYSA();

    // Override methods
    double max_contribution() override;
    void withdrawal(double amount, Economic_Factors ef) override;

    double tot();
};