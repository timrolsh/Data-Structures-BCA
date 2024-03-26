#ifndef FACTORSLAB_FACTORSLAB_H

#define FACTORSLAB_FACTORSLAB_H

#include <vector>
unsigned long modularPower(unsigned long base, unsigned long exponent, unsigned long modulus);
bool isPrime(unsigned long n);
long findPrime(unsigned long n);
std::vector<unsigned long> factor(unsigned long n);

#endif