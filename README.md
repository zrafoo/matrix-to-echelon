# matrix-to-echelon
Matrix reduction to echelon form.


## generate.cpp
Used for generate matrix in .bin file.

### Usage:

Linux:
g++ -O2 generate.cpp -o generate
./generate
The program will create a .bin file containing the specified number of matrices of the specified size.

## main.cpp
Matrix reduction to echelon form.

### Usage:

Linux:
g++ -O3 -ffast-math -march=native -fno-exceptions main.cpp -o main
./main

If necessary, add code on your own to save the result of program work to a file.
