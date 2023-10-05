/*
Tim Rolshud
Data Structures Period 1
October 6th, 2023
*/

#include <iostream>

#include "ModLab.hpp"
using namespace std;

long Mod::modulus = 17;
const int MOD1 = 17;
const long MOD2 = __LONG_LONG_MAX__ - 24;
// A large prime number for modulus
const long LARGE_PRIME = 999998727899999;

int main() {
    cout << "Small Mod Test\n";
    Mod::set_modulus(MOD1);
    Mod a(1), b(-10), c(-21), d(99);
    cout << "\tTest 1: "
         << (a.val() == 1 && b.val() == 7 && c.val() == 13 && d.val() == 14)
         << '\n';
    cout << "\tTest 2: "
         << (a.pwr(16) == 1 && b.pwr(16) == 1 && c.pwr(16) == 1 &&
             d.pwr(16) == 1)
         << '\n';
    cout << "\tTest 3: "
         << (a.pwr(1234134) == 1 && b.pwr(3238475238923) == 14 &&
             c.pwr(-1035) == 13 && d.pwr(9223372036854775807) == 11)
         << '\n';
    cout << "\tTest 4: "
         << ((-a).val() == 16 && (-b).val() == 10 && (-c).val() == 4 &&
             (-d).val() == 3)
         << '\n';
    cout << "\tTest 5: "
         << (8 == a + b && 11 == b - c && a * d == 8 + b * c && 7 == c / d)
         << '\n';

    cout << "Big Mod Test\n";
    Mod::set_modulus(MOD2);
    Mod w(10), x(-2), y(-1000), z(102131248714);
    cout << "\tTest 1: "
         << (w.val() == 10 && x.val() == 9223372036854775781 &&
             y.val() == 9223372036854774783 && z.val() == 102131248714)
         << '\n';
    cout << "\tTest 2: "
         << (w.pwr(9223372036854775782) == 1 &&
             x.pwr(9223372036854775782) == 1 &&
             y.pwr(9223372036854775782) == 1 && z.pwr(9223372036854775782) == 1)
         << '\n';
    cout << "\tTest 3: "
         << (w.pwr(9223372036854775781) == 2767011611056432735 &&
             x.pwr(-13467274278643267) == 36926955412652977 &&
             y.pwr(3238475238923) == 6282865623983465974 &&
             z.pwr(9223372036854775807) == 6304613605540290559)
         << '\n';
    cout << "\tTest 4: "
         << ((-w).val() == 9223372036854775773 && (-x).val() == 2 &&
             (-y).val() == 1000 && (-z).val() == 9223371934723527069)
         << '\n';
    cout << "\tTest 5: "
         << (12 == w - x && 998 == x - y && 2000 == x * y &&
             1844674417584080028 == z / w)
         << '\n';

    // Test 6: Modulus Setting and Getting with Large Numbers
    Mod::set_modulus(LARGE_PRIME);
    cout << "\tTest 6: " << (Mod::get_modulus() == LARGE_PRIME) << '\n';

    Mod h(__LONG_LONG_MAX__ - 5), i(__LONG_LONG_MAX__ - 25);
}