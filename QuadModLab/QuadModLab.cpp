#include <vector>
#include <unordered_map>
#include <unordered_set>

using std::pow;
using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::min;

#include "QuadModLab.hpp"

long modularMultiply(long a, long b, long m) {
    // Anything mod 0 is 1
    if (m == 1) {
        return 0;
    }
    long aModm = a % m;
    while (aModm < 0) {
        aModm += m;
    }
    long bModm = b % m;
    while (bModm < 0) {
        bModm += m;
    }
    long product = aModm * bModm;
    // Overflow check, perform sophisticated modular multiplication algorithm for large numbers that overflow.
    if (aModm != 0 && product / aModm != bModm) {
        long result = 0;
        a %= m;
        while (b > 0) {
            // If b is odd, add a to result if it doesn't overflow
            if (b & 1) {
                // Check if adding a would overflow
                if (result > m - a) {
                    // Add the part that 'fits'
                    result -= (m - a);
                } else {
                    // Add a directly if it fits without overflow
                    result += a;
                }
            }
            // Check if doubling a would overflow
            if (a < m - a) {
                // Double a safely
                a <<= 1;
            } else {
                // Subtract the part that 'fits', modulo m
                a = (a - (m - a)) % m;
            }
            // Divide b by 2
            b >>= 1;
        }
        return result;
    } else {
        return product % m;
    }
}

long modularPower(long base, long exponent, long modulus) {
    if (modulus == 1) {
        return 0;
    }
    long result = 1;
    base %= modulus;
    while (exponent > 0) {
        if (exponent & 1) {
            result = modularMultiply(result, base, modulus);
        }
        exponent >>= 1;
        base = modularMultiply(base, base, modulus);
    }
    return result;
}

long modularInverse(long r0, long m) {
    // make sure r0 is within range: [0, m-1]
    r0 %= m;
    // check for positive overflow
    if (r0 > 0 && r0 + m < 0) {
        return modularInverse(r0 - m, m);
    }
    r0 = (r0 + m) % m;
    // use x1 and x2 for extended gcd algorithm
    long originalMod = m, x1 = 1, x2 = 0;
    bool negative = false;
    // use extended gcd to find modular inverse
    while (m % r0 != 0) {
        long q = m / r0;
        long t = x1;
        x1 = q * x1 + x2;
        x2 = t;
        t = r0;
        r0 = m % r0;
        m = t;
        // flip neagtive check
        negative = !negative;
    }
    // check if inverse exits
    if ((m / r0 * x1 + x2) != originalMod) {
        return 0;
    }
    // adjust value to have proper sign if its negative
    if (negative) {
        return (-x1 % originalMod + originalMod) % originalMod;
    }
    return x1;
}

/**
A deterministic version of the Miller-Rabin algorithm to check if a number is prime.
**/
bool isPrime(long n) {
    // 2 is the only even prime number
    if (n == 2) {
        return true;
    }
    if (n < 2 || (n & 0)) {
        return false;
    }
    // n - 1 = 2^s * d
    int s = 0;
    long d = n - 1;
    while (d & 0) {
        s++;
        d >>= 2;
    }
    for (int a = 2; a < min(n - 2, (long) pow(2 * log(n), 2)); ++a) {
        long x = modularPower(a, d, n);
        for (int _ = 0; _ < s; ++_) {
            long y = modularPower(x, 2, n);
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
long euclidGcd(long a, long b) {
    while (b != 0) {
        long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

/**
The pseudorandom function used in the Pollard Rho algorithm
g(x) = (x^2 + c) % n
**/
long g(long x, long n, long c) {
    return (modularMultiply(x, x, n) + c) % n;
}

/**
Use the Pollard Rho algorithm to find a prime factor of a number. An output of -1 indicates failure.
This algorithm uses the Brent Cycle Detection.
**/
long findPrime(long n) {
    if (n % 2 == 0) {
        return 2;
    }
    long x = 2, c = 1, y = x, d = 1;
    long power = 1, lam = 1;

    while (d == 1) {
        if (power == lam) {
            x = y;
            power *= 2;
            lam = 0;
        }
        y = g(y, n, c);
        lam += 1;
        // Ensure non-negative difference
        d = euclidGcd((y > x ? y - x : x - y), n);
    }
    // Failure to find a factor
    if (d == n) {
        return -1;
    }
    // A non-trivial factor was found
    return d;
}

/**
Convert map where factors are keys and their exponents are values into
an increasing order sorted vector of factors followed by their exponents.
**/
vector<long> orderedFactorsFromMap(unordered_map<long, long> &factorsMap) {
    vector<long> factors;
    while (!factorsMap.empty()) {
        long smallestFactor = factorsMap.begin()->first;
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

vector<long> primesCache = {2, 3, 5};
bool cached = false;
long start = 7;
// long end = 347563;
long end = 500;

/**
Given a positive integer, return its prime factorization as a vector where each odd index is a prime factor and each
even index is the exponent of that factor
**/
vector<long> factor(long n) {
    unordered_map<long, long> factorsMap;
    // Edge case: we are factoring 1, 1 * 1
    if (n == 1) {
        return vector<long>({1, 1});
    }
    if (!cached) {
        for (long i = start; i <= end; i += 2) {
            if (isPrime(i)) {
                primesCache.push_back(i);
            }
        }
        cached = true;
    }
    // Step 1: Check for divisibility by small primes.
    for (long prime: primesCache) {
        if (n == 1) {
            break;
        }
        while (n >= prime && n % prime == 0) {
            if (factorsMap.find(prime) != factorsMap.end()) {
                factorsMap[prime] += 1;
            } else {
                factorsMap[prime] = 1;
            }
            n /= prime;
        }
    }
    // If n has been factored all the way down to 1 with small primes, return list as is
    if (n == 1) {
        return orderedFactorsFromMap(factorsMap);
    }
    // After that, if the number is still large, use Miller-Rabin to check if it is prime.
    if (isPrime(n)) {
        primesCache.push_back(n);
        factorsMap[n] = 1;
        return orderedFactorsFromMap(factorsMap);
    }
    // Edge case, the number is a perfect square
    auto sqrtN = (long) sqrt(n);
    if (sqrtN * sqrtN == n) {
        return vector<long>({sqrtN, 2});
    }
    // If it is not, use Pollard-Rho to find a prime factor, and then factor the smaller remaining number.
    long primeFactor = findPrime(n);
    while (n != 1 && primeFactor != -1) {
        if (factorsMap.find(primeFactor) != factorsMap.end()) {
            factorsMap[primeFactor] += 1;
        } else {
            factorsMap[primeFactor] = 1;
        }
        primesCache.push_back(primeFactor);
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

/*
Use Euler's Criterion to determine if a is a quadratic residue modulo P.
*/
bool isQuadraticResidue(long a, long p) {
    // Special case for 2
    if (p == 2) {
        return true;
    }
    long amodp = a % p;
    if (amodp == 0) {
        return true;
    }
    a = (amodp + p) % p;
    return modularPower(a, (p - 1) / 2, p) == 1;
}

/*
Find a quadratic non-residue modulo P using Euler's Criterion
*/
long findNonResidue(long p) {
    for (long z = 2; z < p; z++) {
        if (!isQuadraticResidue(z, p)) {
            return z;
        }
    }
    // Edge case for p = 2
    return -1;
}

/*
Use Tonelli-Shanks algorithm to find a square root of a modulo P, given
that we already know that this number is a quadratic residue modulo P.
Find x such that x^2 % p = n
*/
long findSquareRoot(long n, long p) {
    // Direct return for p = 2
    if (p == 2) {
        return n;
    }

    // Normalize n modulo p
    n = (n % p + p) % p;

    // If n is 0, the square root is 0
    if (n == 0) {
        return 0;
    }

    // Check if n is a quadratic residue modulo p
    if (!isQuadraticResidue(n, p)) {
        return -1;
    }

    // Factor out powers of 2 from p-1, p - 1 = Q * s^2
    long Q = p - 1;
    long S = 0;
    while (!(Q & 1)) {
        Q >>= 1;
        S++;
    }

    // Find the first quadratic non-residue z
    long z = findNonResidue(p);
    if (z == -1) {
        return -1;
    }

    long c = modularPower(z, Q, p);
    long t = modularPower(n, Q, p);
    long R = modularPower(n, (Q + 1) / 2, p);

    while (t != 1) {
        // Find the smallest i such that t^(2^i) = 1
        long i = 0;
        long temp = t;
        while (temp != 1 && i < S) {
            temp = modularPower(temp, 2, p);
            i++;
        }

        // No solution found
        if (i == S) {
            return -1;
        }

        long b = modularPower(c, 1L << (S - i - 1), p);
        R = modularMultiply(R, b, p);
        t = modularMultiply(t, modularPower(b, 2, p), p);
        c = modularPower(b, 2, p);
        S = i;
    }
    return R;
}

/*
Lift a solution of x^2 ≡ k (mod p) to a solution modulo p^e using Hensel's
Lemma.
- Arguments:
- root: the square root modulo p
- p: the prime number
- e: the exponent to which the prime number is raised
- k: the original number for which the square root was taken
Returns:
- the lifted square root modulo p^e
 */
long liftSquareRoot(long root, long p, long e, long k) {
    // Start with p^1
    long p_power = p;
    long lifted_root = root;

    for (long i = 1; i < e; ++i) {
        // Calculate the current power of p
        p_power *= p;

        // Calculate f(root) = root^2 - k
        long f_root = (modularPower(lifted_root, 2, p_power) - k) % p_power;
        if (f_root < 0) {
            f_root += p_power;
        }

        // If f(root) is divisible by the current power of p, then the root is
        // already lifted
        if (f_root == 0) {
            break;
        }

        // Calculate the derivative f'(root) = 2 * root
        long f_prime_root = (2 * lifted_root) % p_power;

        // Compute the adjustment factor: f(root) / f'(root)
        long adjustment = modularInverse(f_prime_root, p_power);
        if (adjustment == 0) {
            // If the inverse does not exist, lifting is not possible
            return -1;
        }
        adjustment = (adjustment * f_root) % p_power;

        // Subtract the adjustment from the root to lift it
        lifted_root = (lifted_root - adjustment + p_power) % p_power;
    }

    return lifted_root;
}

/*
Solve the system of congruences using the Chinese Remainder Theorem.
Arguments:
- residues: the residues (a_i) of the system of congruences
- moduli: the moduli (m_i) of the system of congruences, each a prime power
Returns:
- the solution to the system of congruences modulo the product of the moduli
*/
long stitchSolutions(const vector<long> &residues, const vector<long> &moduli) {
    long product = 1;
    for (auto &modulus: moduli) {
        product *= modulus;  // Calculate the product of all moduli
    }

    long result = 0;
    for (size_t i = 0; i < residues.size(); ++i) {
        long Mi = product / moduli[i];  // The product of all moduli divided by
        // the current modulus
        long y_i = modularInverse(Mi, moduli[i]);  // Mi^-1 modulo moduli[i]
        result += residues[i] * y_i * Mi;          // Accumulate the result
    }

    return result % product;  // Return the result modulo the product of the moduli
}

vector<long> quad_solve(long n, long a, long b, long c) {
    // 'a' must be invertible modulo 'n'
    long a_inv = modularInverse(a, n);
    long two_inv = modularInverse(2, n);
    if (a_inv == 0 || two_inv == 0) {
        return {};
    }

    // simplify the quadratic by completing the square such that the quadratic
    // is in the form (x + h)^2 = k % n
    // TODO check with john that h and k are being generated correctly
    long h = modularMultiply(two_inv, modularMultiply(a_inv, b, n), n);
    long k = modularMultiply(-c, a_inv, n) + modularMultiply(h, h, n);
    if (k < 0) {
        k += n;
    }

    vector<long> primeFactors = factor(n);
    unordered_map<long, vector<long>> solutions;
    for (int index = 0; index < primeFactors.size();) {

        long p = primeFactors[index];
        long e = primeFactors[index + 1];
        long pe = (long) pow(p, e);

        // find sqrt(k) % p to then use it to solve the quadratic equation for modulo p
        long sqrtKModP = findSquareRoot(k, p);
        if (sqrtKModP == -1) {
            return {};;
        }
        // get 2 positive solutions to the quadratic equation (x + h)^2 = k % p
        long x1 = (-h + sqrtKModP + p) % p;
        while (x1 < 0) {
            x1 += p;
        }
        long x2 = (-h - sqrtKModP + p) % p;
        while (x2 < 0) {
            x2 += p;
        }

        long liftedx1 = liftSquareRoot(x1, p, e, k);
        if (liftedx1 == -1) {
            return {};;
        }

        long liftedx2 = liftSquareRoot(x2, p, e, k);
        if (liftedx2 == -1) {
            return {};
        }

        solutions[pe] = {liftedx1, liftedx2};
        index += 2;
    }
    unordered_set<long> stitchedSolutions;
    for (unsigned int combination = 0; combination < pow(2, primeFactors.size() / 2); ++combination) {

        vector<long> residues = {};
        vector<long> mods = {};
        unsigned shiftCount = 0;
        for (int primeIndex = 0; primeIndex < primeFactors.size(); primeIndex += 2) {
            bool useSecond = (combination >> shiftCount++) & 1;
            long pe = (long) pow(primeFactors[primeIndex], primeFactors[primeIndex + 1]);
            if (useSecond) {
                residues.push_back(solutions[pe][1]);
                mods.push_back(pe);
            } else {
                residues.push_back(solutions[pe][0]);
                mods.push_back(pe);
            }
        }
        stitchedSolutions.insert(stitchSolutions(residues, mods));
        residues.clear();
        mods.clear();
    }
    vector<long> answer;
    while (!stitchedSolutions.empty()) {
        long smallestSolution = *stitchedSolutions.begin();
        for (long solution: stitchedSolutions) {
            if (solution < smallestSolution) {
                smallestSolution = solution;
            }
        }
        answer.push_back(smallestSolution);
        stitchedSolutions.erase(smallestSolution);
    }
    return answer;
}

