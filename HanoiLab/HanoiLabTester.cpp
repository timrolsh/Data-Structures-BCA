#define CATCH_CONFIG_RUNNER

#include "HanoiLabTesterHelper.hpp"
#include <iostream>
#include <algorithm>
#include "HanoiLab.hpp"

using std::cout;
using std::swap;

inline void hanoiTest(int towers, int disks, vector<VI> expected) {
    vector<VI> moves;
    VI aux;
    for (int i = 0; i < towers; ++i)
        aux.push_back(i);
    hanoi(moves, towers, disks, aux);
    REQUIRE(moves == expected);
}

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    hanoi_init();
    Catch::Session().run(argc, argv);
    auto end = std::chrono::high_resolution_clock::now();// Calculate the duration in seconds
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
    std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
    return 0;
}

TEST_CASE("hanoi_init[3] - the first 6")
{
    REQUIRE(n_hanoi[3][1] == 0b1);
    REQUIRE(n_hanoi[3][2] == 0b11);
    REQUIRE(n_hanoi[3][3] == 0b111);
    REQUIRE(n_hanoi[3][4] == 0b1111);
    REQUIRE(n_hanoi[3][5] == 0b11111);
    REQUIRE(n_hanoi[3][6] == 0b111111);
}

TEST_CASE("hanoi_init[3] - everything")
{
    for (unsigned int d = 1; d < 64; ++d) {
        REQUIRE(n_hanoi[3][d] == (1LL << d) - 1LL);
    }
}

TEST_CASE("hanoi_init[3] - the last")
{
    REQUIRE(n_hanoi[3][63] == 0b111111111111111111111111111111111111111111111111111111111111111);
}

TEST_CASE("hanoi_init[4] - the first 3")
{
    REQUIRE(n_hanoi[4][1] == 1);
    REQUIRE(n_hanoi[4][2] == 3);
    REQUIRE(n_hanoi[4][3] == 5);
}

TEST_CASE("hanoi_init - OEIS A007664")
{
    VI a = {1, 3, 5, 9, 13, 17, 25, 33, 41, 49, 65, 81, 97, 113, 129, 161,
            193, 225, 257, 289, 321, 385, 449, 513, 577, 641, 705, 769,
            897, 1025, 1153, 1281, 1409, 1537, 1665, 1793, 2049, 2305,
            2561, 2817, 3073, 3329, 3585, 3841, 4097, 4609, 5121, 5633};
    for (int i = 0; i < a.size(); ++i) {
        REQUIRE(n_hanoi[4][i + 1] == a[i]);
    }
}

TEST_CASE("hanoi_init - OEIS A137695")
{
    VI a = {1, 3, 3, 7, 5, 5, 15, 9, 7, 7, 31, 13, 11, 9, 9, 63, 17, 15, 13, 11,
            11, 127, 25, 19, 17, 15, 13, 13, 255, 33, 23, 21, 19, 17, 15, 15,
            511, 41, 27, 25, 23, 21, 19, 17, 17, 1023, 49, 31, 29, 27, 25,
            23, 21, 19, 19, 2047, 65, 39, 33, 31, 29, 27, 25, 23, 21, 21,
            4095, 81, 47, 37, 35};
    int row = 1;
    int col = 0;
    for (int x: a) {
        if (col + 3 <= 10) {
            REQUIRE(n_hanoi[col + 3][row] == x);
        }
        ++col;
        if (col == row) {
            ++row;
            col = 0;
        }
    }
}

TEST_CASE("hanoi_init[4] - everything")
{
    unsigned long long diff = 2ULL;
    int x = 1;
    int j = 0;
    for (int i = 1; i < 1660; ++i) {
        REQUIRE(n_hanoi[4][i + 1] - n_hanoi[4][i] == diff);
        ++j;
        if (j == x + 1) {
            diff = diff << 1ULL;
            ++x;
            j = 0;
        }
    }
}

TEST_CASE("hanoi_init[5] - everything")
{
    unsigned long long diff = 2LL;
    int x = 1;
    int j = 0;
    for (int i = 1; i < n_hanoi[5].size() - 1; ++i) {
        REQUIRE(n_hanoi[5][i + 1] - n_hanoi[5][i] == diff);
        ++j;
        if (j == x * (x + 3) / 2 + 1) {
            diff = diff << 1LL;
            ++x;
            j = 0;
        }
    }
}

TEST_CASE("hanoix(1)")
{
    for (int i = 3; i <= 10; ++i) {
        vector<VI> moves;
        VI aux;
        for (int j = 0; j < i; ++j) {
            aux.push_back(j);
        }
        hanoi(moves, i, 1, aux);

        vector<VI> expected = {{0, 1}};
        REQUIRE(moves == expected);
    }
}

TEST_CASE("hanoi3(2)")
{
    hanoiTest(3, 2, {{0, 2},
                     {0, 1},
                     {2, 1}});
}

TEST_CASE("hanoi4(2)")
{
    hanoiTest(4, 2, {{0, 3},
                     {0, 1},
                     {3, 1}});
}

TEST_CASE("hanoi3(3)")
{
    hanoiTest(3, 3, {{0, 1},
                     {0, 2},
                     {1, 2},
                     {0, 1},
                     {2, 0},
                     {2, 1},
                     {0, 1}});
}

TEST_CASE("hanoi4(3)")
{
    hanoiTest(4, 3, {{0, 3},
                     {0, 2},
                     {0, 1},
                     {2, 1},
                     {3, 1}});
}

TEST_CASE("hanoi5(3)")
{
    hanoiTest(5, 3, {{0, 4},
                     {0, 3},
                     {0, 1},
                     {3, 1},
                     {4, 1}});
}

void hanoiTestAuto(int i, int j) {
    vector<VI> moves;
    VI aux;
    vector<VI> towers;
    for (int k = 0; k < i; ++k) {
        towers.emplace_back();
        aux.push_back(k);
    }
    hanoi(moves, i, j, aux);

    // Basic size check
    REQUIRE(moves.size() == n_hanoi[i][j]);

    // Simulation
    for (int k = 0; k < j; ++k) { // Set-up
        towers[0].push_back(k);
    }
    VI expected = towers[0];
    for (VI move: moves) {
        REQUIRE(!towers[move[0]].empty());
        int disk = towers[move[0]].back();
        towers[move[0]].pop_back();
        if (!towers[move[1]].empty())
            REQUIRE(disk > towers[move[1]].back());
        towers[move[1]].push_back(disk);
    }
    REQUIRE(towers[1] == expected); // Final checks
    for (int k = 0; k < i; ++k) {
        if (k != 1)
            REQUIRE(towers[k].empty());
    }
    towers[1].clear(); // Reset
}

TEST_CASE("hanoi - up to 1000")
{
    VI aux = {0, 1, 2};
    vector<VI> towers{{},
                      {},
                      {},
                      {},
                      {},
                      {},
                      {},
                      {},
                      {},
                      {}};
    for (int i = 3; i <= 10; ++i) {
        for (int j = 1; j < n_hanoi[i].size() && n_hanoi[i][j] <= 1000; ++j) { // arbitrary cutoff
            hanoiTestAuto(i, j);
        }
        aux.push_back(i);
    }
}

TEST_CASE("hanoi7(8110)")
{
    hanoiTestAuto(7, 8110);
}