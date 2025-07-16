#include <fstream>
#include "Period_Life_Data.h" // Include the updated header
#include "global_rng.h"

std::uniform_real_distribution<double> Period_Life_Data::dist(0.0, 1.0);

Period_Life_Data::Period_Life_Data(int birth_year, Sex sex)
{
    // Input validation: birth_year should be greater than DATA_FIRST_BIRTH_YEAR and less than 2020
    if (birth_year <= DATA_FIRST_BIRTH_YEAR || birth_year >= 2020)
    {
        std::cerr << "Error: birth_year (" << birth_year << ") must be greater than " << DATA_FIRST_BIRTH_YEAR << " and less than 2020." << std::endl;
        throw std::invalid_argument("Invalid birth_year in Period_Life_Data constructor.");
    }

    // figure out what file to open
    std::string path_name = "./data/";
    switch (sex)
    {
    case Sex::Male:
        path_name += "life_expectancy_male.csv";
        break;
    case Sex::Female:
        path_name += "life_expectancy_female.csv";
        break;
    }

    std::ifstream period_life_table;
    period_life_table.open(path_name);
    if (period_life_table.is_open())
    {
        std::string line;
        int line_number = 0;

        // skip to the important data
        int offset = ((birth_year - DATA_FIRST_BIRTH_YEAR) * DATA_MAX_AGE);

        while (std::getline(period_life_table, line) && line_number < offset)
        {
            line_number++;
        }

        for (int i = 0; i <= DATA_MAX_AGE - 1; ++i)
        {
            if (std::getline(period_life_table, line))
            {
                // isolate the q(x) value from the row, i.e. the probablity of dying at that age
                size_t last_comma_pos = line.find_last_of(',');
                std::string last_number_str = line.substr(last_comma_pos + 1);
                float qx = std::stod(last_number_str);
                probabilities_by_age[i] = qx;
            }
            else
            {
                std::cerr << "Error: Reached end of file prematurely or data missing for year " << birth_year << std::endl;
                break;
            }
        }

        period_life_table.close();
    }
    else
    {
        std::cerr << "Error: Could not open the period_life_table " << path_name << " for reading." << std::endl;
    }
}

// check if they died based on the probability associed with their age
bool Period_Life_Data::did_die_at_age(int age)
{
    double random_result = Period_Life_Data::dist(*global_RNG);
    float probability_of_death = probabilities_by_age[age > DATA_MAX_AGE ? DATA_MAX_AGE - 1 : age];

    if (random_result < probability_of_death)
    {
        return true;
    }

    return false;
}
