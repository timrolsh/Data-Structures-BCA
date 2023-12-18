/*
Tim Rolshud
Data Structures
December 18th, 2023
*/
#include "ProbabilityLab.hpp"
#include <random>

#define BINARY_ITERATIONS 30

using std::random_device;
using std::mt19937;
using std::bernoulli_distribution;


bool flip() {
    random_device randomDevice;
    mt19937 gen(randomDevice());
    bernoulli_distribution distribution(0.5);
    return distribution(gen) == 1;
}

// Function to simulate a/b probability using flip()
bool flip(unsigned long long a, unsigned long long b) {
    if (a == 0) {
        return false;
    }
    if (a == b) {
        return true;
    }

    int probability = 1; // Start with a probability of 1 (100%)

    // Use binary representation to get as close to a/b as possible
    for (int i = 0; i < BINARY_ITERATIONS; ++i) {
        if (probability * 2 <= b) {
            probability *= 2;
            if (flip()) {
                a *= 2;
            }
        } else {
            return a >= b;
        }
    }
    return a >= b;
}

