# Investment Simulator

The goal of this project is a vastly comprehensive investment simulation tool, with the goal of answering retirement planning questions

-   It is based on monthly data, which tends to be how we think and plan regarding money
-   It runs monte carlo simulations

# PPF

The simulator should be able to do many things, but my goal is to minimize for PPF given a person's life inputs
PPF: Probabilty of Portfolio Failure $\hat{P} = \frac{\# \text{ of failed sims before death}}{\text{total number of sims}}$
I would say it is better to choose a path with far less money for any ammount lower PPF

# Output Aggregation

The dificulty with simulating something over a term as long as a person's life is the quantity of data you need to get a stable result. Given that the values I'm dealing with don't need to be particularly precise, I will use a approximations where appropriate. My DistributionLearner, inspired by [this python library](https://github.com/cxxr/LiveStats/blob/master/livestats/livestats.py), should give me the best balance of time and space complexity, with $O(1)$ updates and minimal storage needs. I've also implemented a Heuristic to check a metric for stability based on STATISTICAL PRINCIPAL, wherein I can take note of a percentage likliehood a chosen value is within n% of it's true value, or, or the ammount I am n% ceterian I am within of the true value (so unclear)

Each investment within each account would need to be tracked with one of these DistributionLearners, which could then be summarized and checked for stability incrementally. The statistics from these summaries could then be saved to a csv file that the frontend could periodically access. This means that it could automatically update independantley of the simulation, making the process easier to follow visually (you could see how close to stable each year's data is as it runs). if the stability check is met at summary time it could then cancel execution.

# Project Structure

blah blah blah factors etc
