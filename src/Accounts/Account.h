#pragma once

#include <iostream>
#include <array>
#include "Economy/Economic_Factor.h"
#include <Economy/Economy.h>

// #define ALLOW_ACCOUNT(type) (household.accounts[static_cast<int>(type)])

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