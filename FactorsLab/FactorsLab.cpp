/**
Tim Rolshud
Data Structures
March 26 2024
**/
#include <vector>
#include <map>
#include "FactorsLab.hpp"

using std::vector;
using std::map;
using std::tuple;
using std::min;
using std::abs;
using std::sqrt;

unsigned long modularPower(unsigned long base, unsigned long exponent, unsigned long modulus) {
    if (modulus == 1) {
        return 0;
    }
    unsigned long result = 1;
    base %= modulus;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % modulus;
        }
        exponent >>= 1;
        base = (base * base) % modulus;
    }
    return result;
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
    if (n < 2 || (n & 0)) {
        return false;
    }
    // n - 1 = 2^s * d
    int s = 0;
    unsigned long d = n - 1;
    while (d & 0) {
        s++;
        d >>= 2;
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

/**
Euclid's algorithm for finding the greatest common divisor of two numbers.
**/
unsigned long gcd(unsigned long a, unsigned long b) {
    while (b != 0) {
        unsigned long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

/**
The pseudorandom function used in the Pollard Rho algorithm
g(x) = (x^2 + 1) % n
**/
unsigned long g(unsigned long x, unsigned long n) {
    return (modularPower(x, 2, n) + 1) % n;
}

/**
Use the Pollard Rho algorithm to find a prime factor of a number. An output of -1 indicates failure.
**/
long findPrime(unsigned long n) {
    unsigned long x = 2;
    unsigned long y = x;
    unsigned long d = 1;
    while (d == 1) {
        x = g(x, n);
        y = g(g(y, n), n);
        d = gcd(abs((long) (x - y)), n);
    }
    if (d == n) {
        return -1;
    }
    return (long) d;
}

/**
Convert map where factors are keys and their exponents are values into
an increasing order sorted vector of factors followed by their exponents.
**/
vector<unsigned long> orderedFactorsFromMap(map<unsigned long, unsigned long> &factorsMap) {
    vector<unsigned long> factors;
    while (!factorsMap.empty()) {
        unsigned long smallestFactor = factorsMap.begin()->first;
        for (auto const &pair: factorsMap) {
            if (pair.first < smallestFactor) {
                smallestFactor = pair.first;
            }
        }
        factors.push_back(smallestFactor);
        factors.push_back(factorsMap[smallestFactor]);
        factorsMap.erase(smallestFactor);
    }
    return factors;
}

vector<unsigned long> factor(unsigned long n) {
    map<unsigned long, unsigned long> factorsMap;
    // Edge case: we are factoring 1, 1 * 1
    if (n == 1) {
        return vector<unsigned long>({1, 1});
    }
    // Step 1: Check for divisibility by small primes.
    for (unsigned long smallPrime: smallPrimes) {
        if (n == 1) {
            break;
        }
        while (n % smallPrime == 0) {
            if (factorsMap.find(smallPrime) != factorsMap.end()) {
                factorsMap[smallPrime] += 1;
            } else {
                factorsMap[smallPrime] = 1;
            }
            n /= smallPrime;
        }
    }
    // If n has been factored all the way down to 1 with small primes, return list as is
    if (n == 1) {
        return orderedFactorsFromMap(factorsMap);
    }
    // After that, if the number is still large, use Miller-Rabin to check if it is prime.
    if (isPrime(n)) {
        factorsMap[n] = 1;
        return orderedFactorsFromMap(factorsMap);
    }
    // Edge case, the number is a perfect square
    auto sqrtN = (unsigned long) sqrt(n);
    if (sqrtN * sqrtN == n) {
        return vector<unsigned long>({sqrtN, 2});
    }
    // If it is not, use Pollard-Rho to find a prime factor, and then factor the smaller remaining number.
    long primeFactor = findPrime(n);
    while (n != 1 && primeFactor != -1) {
        if (factorsMap.find(primeFactor) != factorsMap.end()) {
            factorsMap[primeFactor] += 1;
        } else {
            factorsMap[primeFactor] = 1;
        }
        n /= primeFactor;
        primeFactor = findPrime(n);
    }
    if (factorsMap.find(n) != factorsMap.end()) {
        factorsMap[n] += 1;
    } else {
        factorsMap[n] = 1;
    }
    return orderedFactorsFromMap(factorsMap);
}
