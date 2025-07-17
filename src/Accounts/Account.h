#pragma once

#include <iostream>
#include <array>
#include <bitset>
#include "Economy/Economic_Factor.h"
#include <Economy/Economy.h>
#include <unordered_map>

// TODO : this has to be updated and the household list has to be updated in the same order, that sucks
enum class Accounts
{
    HYSA,
    Checking,
    Brokerage,
    Traditional_401k,
    Roth_401k,
    Traditional_IRA,
    Roth_IRA,
    HSA,
    Annuity,
    Cash,
    Precious_Assets,
    Real_Estate,
    COUNT
};

constexpr int num_accounts = static_cast<int>(Accounts::COUNT);

// TODO: households need to be factored in somehow, i.e. where do deposits and withdrawls come from / go?
class Account
{
protected:
    std::unordered_map<Economic_Factors, double> balances;

public:
    void deposit(double amount, Economic_Factors ef);
    void increment(int month);
    void print_balances();
    double total_balance();

    // abstract methods
    virtual double max_contribution() = 0;
    // TBD how this will work
    virtual void withdrawal(double amount, Economic_Factors ef) = 0;
};
