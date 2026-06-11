## Goal 
This projects shows signal handling in C++.
It contains a single program that doesnt terminate if we press Ctrl + C in the terminal. Rather
it prints a message on how to terminate.

## Status
Completed

## Files
- **src/main_v1.cpp** : Contains the basic version of the signal handler. it mistakenly uses std::cout inside the handler function
- **src/main_v2.cpp** : Contains the bug free  version of the signal handler. it uses async  write operation inside the handler function
- **Tutorial/** : contains notes on some theoretical knowledge

