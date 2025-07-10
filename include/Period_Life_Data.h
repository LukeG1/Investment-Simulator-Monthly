#pragma once

#include <array>
#include <string>
#include <iostream>
#include <random>

const int DATA_MAX_AGE = 111;
const int DATA_FIRST_BIRTH_YEAR = 1933;

// Enum for Sex
enum class Sex
{
    Male,
    Female,
};

// TODO: remove starting age
class Period_Life_Data
{
public:
    Period_Life_Data(int birth_year, Sex sex);
    bool did_die_at_age(int age);

private:
    // TODO: rename
    std::array<float, DATA_MAX_AGE> probabilities_by_age;
    static std::uniform_real_distribution<double> dist;
};