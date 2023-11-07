#include <iostream>
#include <string>
#include <cmath>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

#include "PokersortLab.hpp"

vector<int> encodeHands(const string &handString) {
    vector<int> encodedHands;
    for (int index = 0; index < handString.size();) {
        int encodedHand = 0;
        for (int exponent = 0; exponent <= 4; ++exponent) {
            int encodedCard = 0;
            char rankChar = handString[index++];
            char suitChar = handString[index++];
            // handle ranks
            if (rankChar == 'T') {
                encodedCard += 4 * 8;
            } else if (rankChar == 'J') {
                encodedCard += 4 * 9;
            } else if (rankChar == 'Q') {
                encodedCard += 4 * 10;
            } else if (rankChar == 'K') {
                encodedCard += 4 * 11;
            } else if (rankChar == 'A') {
                encodedCard += 4 * 12;
            }
                // we have a rank that is a number from 2 to 9
            else {
                encodedCard += 4 * (rankChar - 50);
            }
            // handle suits
            if (suitChar == 'C') {
                encodedCard += 0;
            } else if (suitChar == 'D') {
                encodedCard += 1;
            } else if (suitChar == 'H') {
                encodedCard += 2;
            } else if (suitChar == 'S') {
                encodedCard += 3;
            }

            encodedHand += encodedCard * (int) pow(52, exponent);
            ++index;
        }
        encodedHands.push_back(encodedHand);
    }
    return encodedHands;
}


void fileTester(const string &filename) {
    string inFileName = filename + (string) "In.txt";
    string outFileName = filename + (string) "Out.txt";
    ifstream inFile(inFileName);
    if (!inFile.is_open()) {
        cout << "Could not open inFile " << inFileName << '\n';
        return;
    }
    string line;
    getline(inFile, line);
    int handsCount = stoi(line);
    vector<int> encodedHands(handsCount);
    for (int index = 0; index < handsCount; ++index) {
        inFile >> encodedHands[index];
    }

    auto start = high_resolution_clock::now();
    poker_sort(encodedHands);
    auto end = high_resolution_clock::now();
    ifstream outFile(outFileName);
    int wrongCount = 0;
    for (int index = 0; index < handsCount; index++) {
        int currentHand;
        outFile >> currentHand;
        wrongCount += (currentHand != encodedHands[index]);
        if (currentHand != encodedHands[index]) {
            cout << index << ' ' << encodedHands[index] << '\n';
        }
    }

    auto duration = duration_cast<milliseconds>(end - start);
    if (wrongCount == 0) {
        cout << "Your code was correct. It sorted in " << duration.count() << " milliseconds.\n";
    } else {
        cout << "There were " << wrongCount << " hands out of place, and your sort took " << duration.count()
             << " milliseconds.\n";
    }
}

int main() {
    cout << "Pokersort Lab Tester: \n\n#1: ShortOne: \n";
    fileTester((string) "TestCases/ShortOne");
    cout << "\n#2: ShortTwo: \n";
    fileTester((string ) "TestCases/ShortTwo");
    cout << "\n#3: LongOne: \n";
    fileTester((string ) "TestCases/LongOne");
    cout << "\n#4: LongTwo: \n";
    fileTester((string) "TestCases/LongTwo");
}