# How will a strategy be implemented?

# in code thoughts:

- SPEND() -> take money from checking account to lower household's expenses
- DEPOSIT() -> move money into checking account
- WITHDRAWL() -> move money from any account/investment to checking account
- TRANSFER() -> move moeny from any account/investment to some other

# How to make it user changable?

> first option is to not, I could just make a set of in code strategies built in

- I like the above option, the simulate_month() function would just be custom to each strategy
- convert the above with some branching and variable structure in a json like object
