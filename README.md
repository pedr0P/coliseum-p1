# Description
  This is a little game made in C++ for my programming class.
It takes two warriors and pairs them up against each other, using some rules akin to Dungeons and Dragons,
where a random number between 1 and 20 will yield different results.
> 1                   → Always the worst result <br>
> Anything in between → Decent result <br>
> 20                  → Always the best result <br>

# How to Play:
  Input the values you would like for two warriors. It is recommended that health be out of 100, and that strength, defense
and healing be out of 5, but ultimately, the choice is yours!
(OBS: Max health needs to be more than health)
  
# Compilation and Execution
Using g++ (or clangd):
``` bash
    g++ -std=c++20 -o coliseum-p1 src/main.cp
```
# Output
  In the beginning, the user will fill some fields with data like maximum health, health, strength, etc...<br>
After these fields (for both warriors) have been filled up, the game will start, and, using the inputted values
and a random number generator, the warriors will fight each other to the death.


# Authors
Pedro Vinícius Barbosa Pereira
