#include <vector>
#include <cmath>
#include "FactorsLab.hpp"

using std::vector;
using std::min;

/**
Given a number (base) raised to a power (exponent), efficiently compute the result modulo a number (modulus).
**/
unsigned long modularPower(unsigned long base, unsigned long exponent, unsigned long modulus) {
    if (modulus == 1) {
        return 0;
    }
    unsigned long c = 1;
    for (unsigned long _ = 0; _ < exponent; ++_) {
        c = c * base % modulus;
    }
    return c;
}

/**
Given a positive integer, return its prime factorization as a vector where each odd index is a prime factor and each
even index is the exponent of that factor
**/
unsigned long smallPrimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

/**
A deterministic version of the Miller-Rabin algorithm to check if a number is prime.
**/
bool isPrime(unsigned long n) {
    // 2 is the only even prime number
    if (n == 2) {
        return true;
    }
    if (n < 2 || n % 2 == 0) {
        return false;
    }
    // n - 1 = 2^s * d
    int s = 0;
    unsigned long d = n - 1;
    while (d % 2 == 0) {
        s++;
        d /= 2;
    }
    for (int a = 2; a < min(n - 2, (unsigned long) pow(2 * log(n), 2)); ++a) {
        unsigned long x = modularPower(a, d, n);
        for (int _ = 0; _ < s; ++_) {
            unsigned long y = modularPower(x, 2, n);
            if (y == 1 && x != 1 && x != n - 1) {
                return false;
            }
            x = y;
        }
        if (x != 1) {
            return false;
        }
    }
    return true;
}

vector<unsigned long> factor(unsigned long n) {
    vector<unsigned long> factors;
    // Step 1: Check for divisibility by small primes.
    for (unsigned long smallPrime: smallPrimes) {
        bool pushed = false;
        while (n % smallPrime == 0) {
            if (!pushed) {
                factors.push_back(smallPrime);
                factors.push_back(1);
                pushed = true;
            }
            factors[factors.size() - 1] += 1;
            n /= smallPrime;
        }
    }
    // After that, if the number is still large, use Miller-Rabin to check if it is prime. If it is not, use Pollard-Rho to find a prime factor, and then factor the smaller remaining number.
}