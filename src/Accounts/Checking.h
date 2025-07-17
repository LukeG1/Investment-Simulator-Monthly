#pragma once

#include "Accounts/Account.h"
#include "Economy/Economic_Factor.h"

class Checking : public Account
{
public:
    Checking();

    // Override methods
    double max_contribution() override;
    void withdrawal(double amount, Economic_Factors ef) override;
};
