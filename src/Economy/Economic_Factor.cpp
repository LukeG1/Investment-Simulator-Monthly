#include "Economic_Factor.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <numeric>
#include <random>
#include <stdexcept>
#include "global_rng.h"

// TODO: this needs a lot of testing
Economic_Factor::Economic_Factor(const std::string &file_path)
{
    std::ifstream infile(file_path);
    if (!infile.is_open())
    {
        throw std::runtime_error("Could not open return data file.");
    }

    std::string line;
    while (std::getline(infile, line))
    {
        if (!line.empty())
        {
            try
            {
                double value = std::stof(line);
                raw_returns.push_back(value);
            }
            catch (const std::invalid_argument &)
            {
                std::cerr << "Skipping invalid line in CSV: " << line << std::endl;
            }
        }
    }
    infile.close();

    if (raw_returns.empty())
    {
        throw std::runtime_error("Return data file is empty or invalid.");
    }

    // Calculate statistics from raw returns for GBM simulation
    calculateStatistics();

    // Generate simulated returns using GBM
    generateGBMReturns();
}

double Economic_Factor::get_return(int month, bool include_inflation)
{
    double current_return = returns[month];
    return include_inflation ? current_return - 0.02f : current_return;
}

void Economic_Factor::calculateStatistics()
{
    // Calculate mean return
    double sum = std::accumulate(raw_returns.begin(), raw_returns.end(), 0.0f);
    mu = sum / raw_returns.size();

    // Calculate standard deviation
    double variance = 0.0f;
    for (double return_val : raw_returns)
    {
        variance += (return_val - mu) * (return_val - mu);
    }
    variance /= raw_returns.size();
    sigma = std::sqrt(variance);
}

void Economic_Factor::generateGBMReturns()
{
    // Get reference to global RNG (assuming it's accessible)
    std::normal_distribution<double> normal_dist(0.0f, 1.0f);

    for (int i = 0; i < MAX_RETURN_HISTORY; ++i)
    {
        // Generate random standard normal variable
        double z = normal_dist(*global_RNG);

        // GBM log returns: log(1 + r_t) = (mu - 0.5 * sigma^2) + sigma * z
        double log_return = (mu - 0.5f * sigma * sigma) + sigma * z;

        // Convert log returns to arithmetic returns: r_t = exp(log_return) - 1
        returns[i] = std::exp(log_return) - 1.0f;
    }
}