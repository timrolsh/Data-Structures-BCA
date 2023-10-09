#include <iostream>
#include <string>
#include <fstream>

#include "FlojoLab.hpp"

using std::cout;
using std::string;
using std::to_string;

string vectorToString(vector<int> &list) {
    string answer = "[";
    for (int index = 0; index < list.size() - 1; ++index) {
        answer += to_string(list[index]) + ", ";
    }
    answer += to_string(list[list.size() - 1]) + "]";
    return answer;
}

vector<int> vectorFromString(const string &numberString) {
    vector<int> result;
    for (int index = 0; index < numberString.size();) {
        int numberStart = index;
        while (index < numberString.size() - 1 && numberString[index] != ' ') {
            ++index;
        }
        result.push_back(std::stoi(numberString.substr(numberStart, index - numberStart + 1)));
        ++index;
    }
    return result;
}

bool testJosephus(int testNumber, int n, int k, vector<int> &expectedResult) {
    vector<int> result = josephus(n, k);
    if (result == expectedResult) {
        // cout << "Passed Test #" << testNumber << "\n";
        return true;
    } else {
        cout << "Failed test case on line " << testNumber << ": \n\tn: " << n << ", k: " << k << "\n\tExpected Order: "
             << vectorToString(expectedResult) << "\n\tYour Order: " << vectorToString(result) << "\n";
        return false;
    }
}

int main() {
    cout << "Josephus Tests: \n";
    std::ifstream file("JosephusTestCases.txt");
    if (!file.is_open()) {
        cout << "Unable to open file, stopping tester: \n";
        return 1;
    }
    string line;
    int counter = 0;
    int correct = 0;
    while (std::getline(file, line)) {
        ++counter;
        vector<int> tokens = vectorFromString(line);
        int n = tokens[0];
        int k = tokens[1];
        tokens.erase(tokens.begin(), tokens.begin() + 2);
        if (testJosephus(counter, n, k, tokens)) {
            ++correct;
        }
    }
    if (correct == counter) {
        cout << "All test cases for Josephus passed.";
    }
    return 0;
}