#include "Simulation/simulation.h"
#include "Mortality/Period_Life_Data.h"
#include "global_rng.h"
#include "Economy/Economic_Factor.h"
#include "Economy/Economy.h"
#include "Accounts/HYSA.h"
#include "Household/Household.h"

// initalize the global randomness with a seed
std::mt19937 global_RNG{std::random_device{}()};

// this is the economy that will be accessed everywhere
Economy economy;

int main()
{
    auto household = Household(26, 0, 100'000);

    auto period_life_data = Period_Life_Data(2002, Sex::Male);
    for (auto _ = 0; _ < 100'000; _++)
        simulate_lifetime(period_life_data);
    return 0;
}