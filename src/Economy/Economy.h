#pragma once
#include "Economic_Factor.h"

enum class Economic_Factors
{
    Total_Inflation,
    Total_Stock_Market,
    International_Markets,
    Corporate_Bonds,
    Federal_Bonds,
    Cash = Total_Inflation, // this is dumb, cash needs a flat EF
    High_Savings_Rate,
    Gold,
    Silver,
    Real_Estate, // even this one has pretty bad quarterly data
    // Income_Growth,
    // Rent,
    COUNT
};
constexpr int num_factors = static_cast<int>(Economic_Factors::COUNT);

class Economy
{
  public:
    // TODO: it seems like inflation adjusting everything would probably be a good idea for efficency
    Economy();
    std::array<Economic_Factor *, num_factors> factors{};
};

extern thread_local Economy *economy; // TODO: refactor to pointer
