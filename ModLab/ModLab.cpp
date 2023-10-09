/*
Tim Rolshud
Data Structures Period 1
October 6th, 2023
*/
#include "ModLab.hpp"

#include <iostream>
using namespace std;

Mod::Mod(long t) {
    x = t % Mod::get_modulus();
    if (x < 0) {
        x += Mod::get_modulus();
    }
}

Mod::Mod(const Mod &m) {
    x = m.val();
}
Mod &Mod::operator=(const Mod &m) {
    x = m.val();
    return *this;
}

Mod &Mod::operator+=(const Mod &m) {
    long modX = x % Mod::get_modulus();
    long modMX = m.val() % Mod::get_modulus();
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

Mod &Mod::operator-=(const Mod &m) {
    // mod subtracting is the same thing as mod adding the negative of the
    // quantity
    return *this += -m;
}

Mod &Mod::operator*=(const Mod &m) {
    long tracker = m.val();
    Mod total(0);
    Mod n(x);
    while (tracker != 0) {
        // if the tracker is odd, modadd x to the total
        if (tracker % 2 == 1) {
            total += n;
        };
        tracker /= 2;
        n += n;
    }
    *this = total;
    return *this;
}

Mod &Mod::operator/=(const Mod &m) {
    // dividing is the same thing as multiplying by the power of -1
    Mod answer(x);
    answer *= m.pwr(-1);
    *this = answer;
    return *this;
}

Mod Mod::operator-() const {
    return Mod(-1 * x);
}

Mod Mod::pwr(long e) const {
    // 0 to the power of e will always be 0
    if (x == 0) {
        return Mod(0);
    };
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

long Mod::val() const {
    return x;
}

void Mod::set_modulus(long m) {
    if (m < 2) {
        throw std::runtime_error(
            "The Mod::get_modulus() cannot be less than 2.");
        exit(1);
    }
    modulus = m;
}

Mod Mod::inv(long r0) {
    long m = Mod::get_modulus();
    // make sure r0 is within range: [0, m-1]
    r0 %= m;
    // check for positive overflow
    if (r0 > 0 && r0 + m < 0) {
        return inv(r0 - m);
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
        throw std::runtime_error("The inverse does not exist.");
        exit(1);
    }
    // adjust value to have proper sign if its negative
    if (negative) {
        return (-x1 % originalMod + originalMod) % originalMod;
    }
    return Mod(x1);
}

Mod operator+(const Mod &a, const Mod &b) {
    Mod answer = a;
    answer += b;
    return answer;
}

Mod operator+(long t, const Mod &m) {
    return m + Mod(t);
}

Mod operator-(const Mod &a, const Mod &b) {
    Mod answer = a;
    answer -= b;
    return answer;
}

Mod operator-(long t, const Mod &m) {
    return m - Mod(t);
}

Mod operator*(const Mod &a, const Mod &b) {
    Mod answer = a;
    answer *= b;
    return answer;
}

Mod operator*(long t, const Mod &m) {
    return m * Mod(t);
}

Mod operator/(const Mod &a, const Mod &b) {
    Mod answer = a;
    answer /= b;
    return answer;
}

Mod operator/(long t, const Mod &m) {
    return m / Mod(t);
}

bool operator==(const Mod &a, const Mod &b) {
    return ((a.val() % Mod::get_modulus()) == (b.val() % Mod::get_modulus()));
}

bool operator==(long t, const Mod &m) {
    return ((m.val() % Mod::get_modulus()) == (t % Mod::get_modulus()));
}

bool operator!=(const Mod &a, const Mod &b) {
    return !(a == b);
}

bool operator!=(long t, const Mod &m) {
    return !(t == m);
}

istream &operator>>(istream &is, Mod &m) {
    long x;
    is >> x;
    m = Mod(x);
    return is;
}

ostream &operator<<(ostream &os, const Mod &m) {
    return os << m.val() << "\n";
}
