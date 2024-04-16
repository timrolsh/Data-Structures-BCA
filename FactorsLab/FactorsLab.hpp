#ifndef FACTORSLAB_FACTORSLAB_H

#define FACTORSLAB_FACTORSLAB_H

#include <vector>
std::vector<unsigned long> factor(unsigned long n);
unsigned long modularPower(unsigned long base, unsigned long exponent, unsigned long modulus);
unsigned long modularMultiply(unsigned long a, unsigned long b, unsigned long m);
bool isPrime(unsigned long n);
#endif