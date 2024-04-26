#ifndef QUADMODLAB_QUADMODLAB_H

#define QUADMODLAB_QUADMODLAB_H

#include <vector>
#include <iostream>
#include <unordered_map>
using std::ostream;
using std::vector;
using std::unordered_map;

std::vector<long> quad_solve(long n, long a, long b, long c);

inline ostream &operator<<(ostream &os, const vector< long> &v) {
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

inline ostream &operator<<(ostream &os, const unordered_map<long, vector<long>> &solutions) {
    os << "{\n";
    for (auto const &pair: solutions) {
        os << pair.first << ": " << pair.second << "\n";
    }
    os << "}\n";
    return os;
}

#endif