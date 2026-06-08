## Objective 
this project teaches how to compile and link multiple cpp files into a single executable 
file without using build tools

## Status 
Completed

## Files 
- **tutorial2.md** : This contains a short tutorial on how to link multiple files
- **main.cpp** : Calls hello function from main function. Declares the prototype on top
- **hello.cpp** : Defines the hello function. 

## How to run
```bash
g++ -o app hello.cpp main.cpp
./app
```