#include "Economy.h"
#include "Economic_Factor.h"
#include <iostream>

#define INITALIZE_FACTOR(factor, path) (factors[static_cast<int>(factor)] = new Economic_Factor(path));

// Constructor definition
Economy::Economy()
{
    // TODO: repeat for each factor
    INITALIZE_FACTOR(Economic_Factors::Total_Inflation, "./data/inflation_historic.csv");
    INITALIZE_FACTOR(Economic_Factors::Total_Stock_Market, "./data/total_market_historic.csv");
    INITALIZE_FACTOR(Economic_Factors::International_Markets, "./data/international_market_historic.csv");
    INITALIZE_FACTOR(Economic_Factors::Corporate_Bonds, "./data/corporate_bonds_historic.csv");
    INITALIZE_FACTOR(Economic_Factors::Federal_Bonds, "./data/federal_bonds_historic.csv");
    // note this is kind of made up data, just half the fed rate
    INITALIZE_FACTOR(Economic_Factors::High_Savings_Rate, "./data/hysa_analog_historic.csv");
    INITALIZE_FACTOR(Economic_Factors::Gold, "./data/gold_historic.csv");
    INITALIZE_FACTOR(Economic_Factors::Silver, "./data/silver_historic.csv");
    INITALIZE_FACTOR(Economic_Factors::Real_Estate, "./data/real_estate_historic.csv");
}
