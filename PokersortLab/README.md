# Pokersort Lab

## Notes about my implementation

This is not the best implementation at all in terms of performance. It does not use quick_sort, and relies entirely on merge sort and multithreading to achieve reasonable performance sorting large amounts of hands. The main reason for this is that due to the way hands were compared in this implementation. The fastest way to do so is during the assignment of the types of the hands, what needs to be done is a number that represents its rank needs to be created. That way, hands can be compardd using these numbers very quickly. My mistake was using a comparison function using the operator<= overload function. As a result, comparisons between hands became highly expensive and were the main bottleneck in performance for this implementation. The setup in order for this comparison function to properly work (classifying the cards with their types, etc.) was also probably not necessary. General organization wise, its a decent way to get started and makes it a little easier to see what kind of hands you have in a debugger, but also probably not necessary.

## Building/Running

To build this project using Make, run:

```bash
mkdir build
cd build
cmake ..
make
./PokersortLab
```

To compile and run this project and tester using just gcc/clang, run:

```bash
g++ -std=c++17 PokersortLab.cpp PokersortLabTester.cpp
./a.out # or ./a.exe on Windows
```

For optimization and lower run times, run:

```bash
g++ -std=c++17 -O PokersortLab.cpp PokersortLabTester.cpp
./a.out # or ./a.exe on Windows
```

I would not rely on this though as John is most likely not going to use this to compile.
