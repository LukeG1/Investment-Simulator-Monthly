#pragma once

#include <iostream>
#include <array>
#include "Economy/Economic_Factor.h"
#include "Economy/Economy.h"

class Investment
{
public:
    double balance;
    Economic_Factor *economic_factor;
};

// TODO: households need to be factored in somehow, i.e. where do deposits and withdrawls come from / go?
class Account
{
protected:
    // TODO: consider better pointers
    // TODO: also consider profiling this with a map instead of array since it is technically sparse though small
    std::array<Investment *, num_factors> investments{};

public:
    virtual ~Account();
    void deposit(double amount, Economic_Factors ef);
    void increment(int month);
    void print_balances();

    // abstract methods
    virtual double max_contribution() = 0;
    virtual void withdrawal(double amount, Economic_Factors ef) = 0;
};