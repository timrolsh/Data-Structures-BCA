#include "ModLab.hpp"
const int MOD1 = 17;
const long long MOD2 = __LONG_LONG_MAX__ - 24; // 9223372036854775783, I think largest prime you can fit in a signed long long

using namespace std;
long Mod::modulus = 17;

int main(){
    cout << "Small Mod Test\n";
    Mod::set_modulus(MOD1);
    Mod a(1), b(-10), c(-21), d(99);
    cout << "\tTest 1: " << (a.val() == 1 && b.val() == 7 && c.val() == 13 && d.val() == 14) << '\n';
    cout << "\tTest 2: " << (a.pwr(16) == 1 && b.pwr(16) == 1 && c.pwr(16) == 1 && d.pwr(16) == 1) << '\n';
    cout << "\tTest 3: " << (a.pwr(1234134) == 1 && b.pwr(3238475238923) == 14 && c.pwr(-1035) == 13 && d.pwr(9223372036854775807) == 11) << '\n';
    cout << "\tTest 4: " << ((-a).val() == 16 && (-b).val() == 10 && (-c).val() == 4 && (-d).val() == 3) << '\n';
    cout << "\tTest 5: " << (8 == a + b && 11 == b - c && a * d == 8 + b * c && 7 == c / d) << '\n';

    cout << "Big Mod Test\n";
    Mod::set_modulus(MOD2);
    Mod w(10), x(-2), y(-1000), z(102131248714);
    cout << "\tTest 1: " << (w.val() == 10 && x.val() == 9223372036854775781 && y.val() == 9223372036854774783 && z.val() == 102131248714) << '\n';
    cout << "\tTest 2: " << (w.pwr(9223372036854775782) == 1 && x.pwr(9223372036854775782) == 1 && y.pwr(9223372036854775782) == 1 && z.pwr(9223372036854775782) == 1) << '\n';
    cout << "\tTest 3: " << (w.pwr(9223372036854775781) == 2767011611056432735 && x.pwr(-13467274278643267) == 36926955412652977 && y.pwr(3238475238923) == 6282865623983465974  && z.pwr(9223372036854775807) == 6304613605540290559) << '\n';
    cout << "\tTest 4: " << ((-w).val() == 9223372036854775773 && (-x).val() == 2 && (-y).val() == 1000 && (-z).val() == 9223371934723527069) << '\n';
    cout << "\tTest 5: " << (12 == w - x && 998 == x - y && 2000 == x * y && 1844674417584080028 == z / w) << '\n';
}