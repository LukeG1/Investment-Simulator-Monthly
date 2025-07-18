#include "Household.h"
#include "Accounts/Brokerage.h"
#include "Accounts/Checking.h"
#include "Accounts/HYSA.h"
#include "json.hpp"
#include <fstream> // For reading from a file
#include <map>     // For std::map (though nlohmann::json handles objects directly)
#include <vector>  // For std::vector

using json = nlohmann::json;

// Household::Household(int starting_age_years, int starting_age_months, int starting_income)
//     : starting_age_years(starting_age_years), starting_age_months(starting_age_months),
//     starting_income(starting_income)
// {
//     // TODO: implement all accounts from the enum and add verification or find a cleaner solution
//     accounts[static_cast<int>(Accounts::HYSA)] = new HYSA();
// };

Household::Household(std::string spec_path)
{
    std::ifstream infile(spec_path);
    if (!infile.is_open())
    {
        std::cerr << "Error: Could not open config.json\n";
    }

    json data;
    try
    {
        infile >> data; // Directly parse the file stream into the json object
        infile.close();
    }
    catch (const json::parse_error &e)
    {
        std::cerr << "JSON Parse Error: " << e.what() << std::endl;
        infile.close();
    }

    // TODO: validate spec

    birth_year = data["Contributors"][0]["age"]["birth_year"];
    starting_age_years = data["Contributors"][0]["age"]["years"];
    starting_age_months = data["Contributors"][0]["age"]["months"];
    starting_income = data["Contributors"][0]["income"];
    sex = data["Contributors"][0]["sex"] == "m" ? Sex::Male : Sex::Female;
    married = data["married"];

    period_life_data = new Period_Life_Data(birth_year, sex);
    // initalize accounts
    portfolio[Accounts::Checking] = new Checking();
    portfolio[Accounts::HYSA] = new HYSA();
    portfolio[Accounts::Brokerage] = new Brokerage();
}

void Household::increment_portfolio(int month)
{
    for (const auto &[account_type, account] : portfolio)
    {
        account->increment(month);
    }
}
