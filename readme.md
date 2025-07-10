# Motivation

I've struggled over decisions like Roth or traditional, rent or buy, stock bond ratios, standard or itemized, when to start social secutiry benifits, are annuities a scam, and countless more. Every answer to these questions is probably the best choise for someone, but you still hear people saying oposite things to people in the same situation. I think that is partially because people have different goals, which is valid, but it's also becauase most people are making educated guesses based on gut feeling. I want a more empirically proven answer if I'm going to steak my livelehood on it. While this project obviosly wouldnt be the first to do such a thing, I want it to be comprehensive and simple enough to not just answer questions like these, but provide an optimal path based on anyone's inputs, to achieve thier goals.

# Overview

This project will be a montecarlo simulator of a person's entire financial life, running computations on a monthly basis to emulate what may happen in real life until the household either runs out of money or they reach their life expectancy.
The secondary objective is to then use the results of that simulation to try messing with the inputs that are able to change until the ideal retirement strategy is found for that household

# PPF

The goal of the project being to provide a user a path to their retirement goals that is most likley to succede, it feels important to define what I see as the most rational main goal. which is minimizing what I've been calling PPF: Probabilty of Portfolio Failure. $\hat{P} = \frac{\# \text{ of portfolio failures before death}}{\text{total number of simulations}}$ The more I've thought about it the more rational it feels to choose a path that has any ammount lower PPF, even if it means a significant sacrifice in potiental portfolio value.

## Alternate Goals

-   Max median portfolio value
-   are there even any others?

# Output Aggregation

The dificulty with simulating something over a term as long as a person's life is the quantity of data you need to get a stable result. Given that the values I'm dealing with don't need to be particularly precise, I will use approximations where appropriate. My Distribution Learner, inspired by [this python library](https://github.com/cxxr/LiveStats/blob/master/livestats/livestats.py), which itsef is partially based on [this paper](https://www.cs.wustl.edu/~jain/papers/ftp/psqr.pdf), should give me the best balance of time and space complexity, with $O(1)$ updates and minimal storage needs.
To determine when a metric has "stabilized," I use a heuristic grounded in the Central Limit Theorem (CLT). It estimates either (1) the probability that the current estimate is within a fixed range of the true mean, or (2) the size of the interval around the mean within which I can be a given percentage certain. This provides a practical, interpretable measure of statistical confidence without requiring full knowledge of the underlying distribution.

## What the distribution learner tracks:

-   `mean`: Running mean of observed outcomes.
-   `count`: Total number of outcomes added.
-   `minVal`: Minimum observed value.
-   `maxVal`: Maximum observed value.
-   `varM2`: Second central moment (for variance calculation).
-   `skewM3`: Third central moment (for skewness calculation).
-   `kurtM4`: Fourth central moment (for kurtosis calculation).
-   `quantiles`: Map of quantile estimators (`0.25`, `0.5`, `0.75`) using the P² algorithm.
-   `precisionTarget`: Target width for confidence interval (used in stability checking).
-   `meanStability`: `StabilityChecker` instance tracking convergence of the mean.

## Modes of operation

There will be 2 modes of operation, when exploring differnt paths, the only thing that really matters is tracking a user's goal. In the case of PPF that would requre very little data, just 2 ints. Once an optimal path is found and you really want to explore it though, each investment within each account would need to be tracked with one of these Distribution Learners, which could then be summarized and checked for stability incrementally. This would provide much more information for a user to explore. and to inform what the impact of this strategy would be. All that being said if the cost of running the distribution learner everywhere is minimal the extra data would be very cool to see.

# Data Locations

> Eventually I'd like to compile all the needed outside data into a single sqllite db that could be frequently updated in a semi automatic way

## Historic Data

-   [CPI](https://fred.stlouisfed.org/series/CPIAUCSL) 1950+
-   [Inflation](https://fred.stlouisfed.org/series/FPCPITOTLZGUSA) 1965+
-   [Dow Jones](https://fred.stlouisfed.org/series/M1109BUSM293NNBR)(total market analog) 1915+
-   Still looking for better stock market representations
-   Still looking for annuity data
-   [Home Prices](https://fred.stlouisfed.org/series/MSPUS) 1965+
-   Still looking for rent data
-   [Moody's AAA Corporate bonds](https://fred.stlouisfed.org/series/AAA) 1920+
-   Still looking for good federal bond data
-   [Income](https://fred.stlouisfed.org/series/MEHOINUSA672N) 1985+
-   [Gold](https://nma.org/wp-content/uploads/2016/09/historic_gold_prices_1833_pres.pdf) 1850+
-   Still looking for silver and other precious metals
-   Still looking for data on HYSAs / General interest rate data

## Tax Data

> TBD

## Social Security data

> TBD

## Life Expectancy / Health

-   [Male](https://www.mortality.org/File/GetDocument/hmd.v6/USA/STATS/mltper_1x1.txt)
-   [Female](https://www.mortality.org/File/GetDocument/hmd.v6/USA/STATS/fltper_1x1.txt)
-   Still looking for data on multipliers for good or poor habits / health / family history
-   Still looking for data on medical expenses?

# Project Structure

## Household

A household is the central part of a simulation, everything connects back to it, money flows in and out of it, etc.

## Household factor

A household tracks a list of household factors, each being something that affects the finances of a house. An example may be one members income, or an expense, or social security, or taxes.

## Ecnomic Factor

An economic factor is where the historic data comes in. An example would be inflation. For each month of the simulation a new return value for each economic factor is detirmined, and that is used to increment a household's portfolio
The return values will be generated with Geometric Brownian Motion (GBM) CITATION OR SOMRTHING BETTER

## Account

A household also has a list of accounts, such as an HYSA, RothIRA, 401k, mortgage, etc. Each matching the rules of that account in real life, such as tax implications and allowed economic factors

## Investment

Each account holds a series of investments based on what is allowed by the account and what is being utilized by the household, it contains a refrence to the relevalant economic factor, and a simple integer for it's current value.

## Simulation

This takes a household and data informed economic factors to run actual month by month simulations on a household until life expectancy, repeating until some count or stability metric is reached. Each thread can contain it's own simulation with copies of the source household and seeds of randomness for the economic factors and life expectancy

## Structure

thread 1: data collection thread
thread 2: historic data simulation thread
thread 3+: simulation threads

# Figuring out the inputs

you may know how much you make now, that you want to some day buy a house, have kids, etc,
but how should that be accounted for, carreer growth / changes etc
life expectancy like above

# Using the tool

runs based on a configuration file that has all the input info and settings for the simulation
choose what to save, like maybe only save means to save time for each investment to avoid complication

# My notes:

-   Period_Life_Data could be used in an inheritance account to represent the parent
-   also the 'household' may technically need 2 of them for the 2 members

## Steps

1. Get a multithreded loop going over a number of years, over a number of sims
2. Get various kinds of historic data reading into c++ economic factors with GBM

while simulating, when accessing an economic factor you would do something like this:
stock_market.return(random_seed, month_index)
or at least that would be nice
