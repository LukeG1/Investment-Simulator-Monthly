#include "Economy.h"
#include "Economic_Factor.h"

// Constructor definition
Economy::Economy()
    : stock_market("./data/dow_jones_historic.csv"),
      bonds("./data/dow_jones_historic.csv") {};
