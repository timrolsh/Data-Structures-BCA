#ifndef HANOILAB_HANOILAB_H
#define HANOILAB_HANOILAB_H

#include <vector>

using std::vector;

// Class Header as copied from the lab instructions
typedef vector<int> VI;
typedef vector<long> VL;
// these are set to externals to avoid duplicate definitions and linker errorrs, will be defined in HanoiLab.cpp
extern vector<VL> n_hanoi;
extern vector<VI> k_hanoi;

// Initialize n_hanoi and k_hanoi
void hanoi_init();

// Fill moves so that each element is a two-integer VI describing the move
// You may assume that, initially, aux[] = {0, 1, 2, ..., n_twrs - 1}
void hanoi(vector<VI> &moves, int n_twrs, int n_dsks, VI &aux);

#endif