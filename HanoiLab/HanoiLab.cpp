#include "HanoiLab.hpp"

using std::swap;

// define maxes for towers and disks as defined in lab instructions
const int MAX_TOWERS = 10;
const int MAX_DISKS = 10000;

// define the externals n_hanoi and k_hanoi here
vector<VL> n_hanoi;
vector<VI> k_hanoi;

void hanoi_init() {
    for (int tower = 0; tower <= MAX_TOWERS; ++tower) {
        n_hanoi.emplace_back(MAX_DISKS + 1);
        k_hanoi.emplace_back(MAX_DISKS + 1);
        for (int disk = 0; disk <= MAX_DISKS; ++disk) {
            // handle 3 or less tower problems
            if (tower < 2 || disk == 0) {
                n_hanoi[tower][disk] = 0;
                k_hanoi[tower][disk] = 0;
            } else if (tower == 2) {
                if (disk < 2) {
                    n_hanoi[tower][disk] = disk;
                } else {
                    n_hanoi[tower][disk] = -1;
                }
            } else if (disk > 1) {
                n_hanoi[tower][disk] = -1;
                for (int k = 1; k < disk; ++k) {
                    if (!(n_hanoi[tower - 1][disk - k] == -1 || n_hanoi[tower][k] == -1)) {
                        long p = 2 * n_hanoi[tower][k];
                        long x = p + n_hanoi[tower - 1][disk - k];
                        if (p >= 0 && x >= 0 && (n_hanoi[tower][disk] == -1 || n_hanoi[tower][disk] > x)) {
                            n_hanoi[tower][disk] = x;
                            k_hanoi[tower][disk] = k;
                        }
                    }
                }
            } else {
                n_hanoi[tower][disk] = disk;
                k_hanoi[tower][disk] = 0;
            }
        }
    }
}

void hanoi(vector<VI> &moves, int n_twrs, int n_dsks, VI &aux) {
    int k = k_hanoi[n_twrs][n_dsks];
    // base case for recursion
    if (n_dsks == 1) {
        moves.push_back({aux[0], aux[1]});
        return;
    }
    swap(aux[1], aux[n_twrs - 1]);
    hanoi(moves, n_twrs, k, aux);
    swap(aux[1], aux[n_twrs - 1]);
    hanoi(moves, n_twrs - 1, n_dsks - k, aux);
    swap(aux[0], aux[n_twrs - 1]);
    hanoi(moves, n_twrs, k, aux);
    swap(aux[0], aux[n_twrs - 1]);
}


