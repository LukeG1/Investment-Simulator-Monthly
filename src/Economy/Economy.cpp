#include "Economy.h"
#include "Economic_Factor.h"
#include <iostream>

#define INITALIZE_FACTOR(factor, path) ( factors[static_cast<int>(factor)] = new Economic_Factor(path) );


// Constructor definition
Economy::Economy(){
    // TODO: repeat for each factor
    INITALIZE_FACTOR(Economic_Factors::Stock_Market, "./data/dow_jones_historic.csv");
    INITALIZE_FACTOR(Economic_Factors::Inflation, "./data/inflation_historic.csv");
    INITALIZE_FACTOR(Economic_Factors::Bonds, "./data/corporate_bonds_historic.csv");
    INITALIZE_FACTOR(Economic_Factors::HYSA, "./data/hysa_analog_historic.csv"); // note this is kind of made up data, just half the fed rate
}
