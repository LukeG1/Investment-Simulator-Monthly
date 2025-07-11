#pragma once
#include "Economic_Factor.h"

enum class Economic_Factors
{
    Stock_Market,
    Bonds,
    Cash,
    Gold,
    Silver,
    Real_Estate,
    Rent,
    COUNT
};
constexpr int num_factors = static_cast<int>(Economic_Factors::COUNT);

class Economy
{
public:
    // TODO: refactor to pointers
    // TODO: it seems like inflation adjusting everything would probably be a good idea for efficency
    Economic_Factor stock_market;
    Economic_Factor bonds;
    Economy();
    // Economic_Factor Cash;
    // Economic_Factor Real_Estate;
};

extern Economy economy;
