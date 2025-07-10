#include "simulation.h"
#include "Period_Life_Data.h"
#include "global_rng.h"

// initalize the global randomness with a seed
// could also be replaced with .seed(<a number>)
std::mt19937 global_RNG{std::random_device{}()};

int main()
{
    auto period_life_data = Period_Life_Data(2002, Sex::Male);
    for (auto _ = 0; _ < 1; _++)
        simulate_lifetime(period_life_data);
    return 0;
}