#pragma once
#include "Economic_Factor.h"

enum class Economic_Factors
{
    Stock_Market,
    Bonds,
    Inflation,
    Cash = Inflation,
    Gold,
    Silver,
    Real_Estate,
    Rent,
    HYSA,
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
