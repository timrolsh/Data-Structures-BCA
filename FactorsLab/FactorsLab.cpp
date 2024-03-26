#include <vector>
#include "FactorsLab.hpp"

using std::vector;
using std::min;
using std::abs;

class Mod {
public:
    explicit Mod(unsigned long t) {
        x = t % Mod::get_modulus();
        if (x < 0) {
            x += Mod::get_modulus();
        }
    }

    Mod &operator+=(const Mod &m) {
        unsigned long modX = x % Mod::get_modulus();
        unsigned long modMX = m.val() % Mod::get_modulus();
        // positive overflow check
        if (x > 0 && m.val() > 0 && (x + m.val()) < 0) {
            x = ((modX - Mod::get_modulus()) + modMX) % Mod::get_modulus();
        }
            // negative overflow check
        else if (x < 0 && m.val() < 0 && (x + m.val()) > 0) {
            x = ((modX + Mod::get_modulus()) + modMX) % Mod::get_modulus();
        }
            // no overflow will happen, they can just be added normally
        else {
            x = (x + m.val()) % Mod::get_modulus();
        }
        return *this;
    }

    Mod &operator-=(const Mod &m) {
        // mod subtracting is the same thing as mod adding the negative of the
        // quantity
        return *this += -m;
    }

    Mod &operator*=(const Mod &m) {
        unsigned long tracker = m.val();
        Mod total(0);
        Mod n(x);
        while (tracker != 0) {
            // if the tracker is odd, modadd x to the total
            if (tracker % 2 == 1) {
                total += n;
            }
            tracker /= 2;
            n += n;
        }
        *this = total;
        return *this;
    }

    Mod &operator/=(const Mod &m) {
        // dividing is the same thing as multiplying by the power of -1
        Mod answer(x);
        answer *= m.pwr(-1);
        *this = answer;
        return *this;
    }

    Mod operator-() const {
        return Mod(-1 * x);
    }

    Mod operator*(const Mod &b) {
        Mod answer = *this;
        answer *= b;
        return answer;
    }

    Mod operator+(const Mod &b) {
        Mod answer = *this;
        answer += b;
        return answer;
    }

    Mod pwr(long e) const {
        // 0 to the power of e will always be 0
        if (x == 0) {
            return Mod(0);
        }
        // the modular negative power is the same as the modular positive power
        // of the modular inverse
        if (e < 0) {
            return inv(x).pwr(-1 * e);
        }
            // anything to the power of 0 is 1
        else if (e == 0) {
            return Mod(1);
        }
        if (x > 0) {
            Mod xMultiply(x);
            // use an even exponent, and go down to the nearest even exponent if
            // it is odd
            if (e % 2 == 0) {
                xMultiply *= xMultiply;
                return xMultiply.pwr(e / 2);
            } else {
                Mod factor = (xMultiply * xMultiply).pwr(e / 2);
                return factor * xMultiply;
            }
        } else {
            int multiply = -1;
            if (e % 2 == 0) {
            }
            return Mod(multiply * Mod(-x).pwr(e).val());
        }
    }

    unsigned long val() const {
        return x;
    }

    static void set_modulus(unsigned long m) {
        if (m < 2) {
            throw std::runtime_error(
                    "The Mod::get_modulus() cannot be less than 2.");
        }
        modulus = m;
    }

    static unsigned long get_modulus() {
        return modulus;
    }

private:
    unsigned long x;
    static unsigned long modulus;

    static Mod inv(unsigned long r0) {
        unsigned long m = Mod::get_modulus();
        // make sure r0 is within range: [0, m-1]
        r0 %= m;
        // check for positive overflow
        if (r0 > 0 && r0 + m < 0) {
            return inv(r0 - m);
        }
        r0 = (r0 + m) % m;
        // use x1 and x2 for extended gcd algorithm
        unsigned long originalMod = m, x1 = 1, x2 = 0;
        bool negative = false;
        // use extended gcd to find modular inverse
        while (m % r0 != 0) {
            unsigned long q = m / r0;
            unsigned long t = x1;
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
            throw std::runtime_error("The inverse does not exist.");
        }
        // adjust value to have proper sign if its negative
        if (negative) {
            return Mod((-x1 % originalMod + originalMod) % originalMod);
        }
        return Mod(x1);
    }
};

// Set default value to avoid compiler error
unsigned long Mod::modulus = 0;

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
        Mod::set_modulus(n);
        unsigned long x = Mod(a).pwr((long) d).val();
        for (int _ = 0; _ < s; ++_) {
            unsigned long y = Mod(x).pwr(2).val();
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
g(x) = x^2 + 1 % n
**/
unsigned long g(unsigned long x) {
    return (Mod(x).pwr(2) + Mod(1)).val();
}

/**
Use the Pollard Rho algorithm to find a prime factor of a number. An output of -1 indicates failure.
**/
long findPrime(unsigned long n) {
    Mod::set_modulus(n);
    unsigned long x = 2;
    unsigned long y = x;
    unsigned long d = 1;
    while (d == 1) {
        x = g(x);
        y = g(g(y));
        d = gcd(abs((long) (x - y)), n);
    }
    if (d == n) {
        return -1;
    }
    return (long) d;
}

vector<unsigned long> factor(unsigned long n) {
    vector<unsigned long> factors;
    if (n == 1) {
        factors.push_back(1);
        factors.push_back(1);
    }
    // Step 1: Check for divisibility by small primes.
    for (unsigned long smallPrime: smallPrimes) {
        if (n == 1) {
            break;
        }
        bool pushed = false;
        while (n % smallPrime == 0) {
            if (!pushed) {
                factors.push_back(smallPrime);
                factors.push_back(1);
                pushed = true;
            } else {
                factors[factors.size() - 1] += 1;
            }
            n /= smallPrime;
        }
    }
    // If n has been factored all the way down to 1 with small primes, return list as is
    if (n == 1) {
        return factors;
    }
    // After that, if the number is still large, use Miller-Rabin to check if it is prime.
    if (isPrime(n)) {
        factors.push_back(n);
        factors.push_back(1);
        return factors;
    }
    // If it is not, use Pollard-Rho to find a prime factor, and then factor the smaller remaining number.
    long primeFactor = findPrime(n);
    while (n != 1 && primeFactor != -1) {
        if (factors.size() >= 2 && factors[factors.size() - 2] == primeFactor) {
            factors[factors.size() - 1] += 1;
        } else {
            factors.push_back(primeFactor);
            factors.push_back(1);
        }
        n /= primeFactor;
        primeFactor = findPrime(n);
    }
    if (factors.size() >= 2 && factors[factors.size() - 2] == n) {
        factors[factors.size() - 1] += 1;
    } else {
        factors.push_back(n);
        factors.push_back(1);
    }
    return factors;
}