#pragma once

#include <vector>
#include <array>
#include <string>

const int MAX_RETURN_HISTORY = 12 * 200; // maximum number of months to keep track of returns

class Economic_Factor
{
public:
    Economic_Factor(const std::string &file_path);

    double get_return(int month, bool include_inflation = true);

private:
    std::vector<float> raw_returns;
    std::array<float, MAX_RETURN_HISTORY> returns;

    // GBM parameters calculated from raw data
    double mu;    // drift (mean return)
    double sigma; // volatility (standard deviation of returns)

    // Private helper methods
    void calculateStatistics();
    // TODO: consider if its better to generate returns on the fly to avoid over generating
    void generateGBMReturns();
};
