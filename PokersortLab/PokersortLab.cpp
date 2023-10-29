#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::vector;


enum Suit {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

enum Rank {
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};


class Card {
public:
    Suit suit;
    Rank rank;
    Card(Suit suit, Rank rank) {
        this->suit = suit;
        this->rank = rank;
    }
//    no arg constructor for Card is called when a blank hand is created, put some dummy values for the suits and ranks for now
    Card() {
        suit = CLUBS;
        rank = TWO;
    }
};

class Hand {
public:
    vector<Card> list;
    explicit Hand(vector<Card> &list) {
        this->list = list;
    }

//    when you create hands it will by default create a hand of 5 empty cards
    Hand() {
        this->list = vector<Card>(5);

    }
};

vector<Hand> decodeHands(vector<int> &encodedHands) {
    vector<Hand> decodedHands(encodedHands.size());
    for (int index = 0; index < encodedHands.size(); ++index) {
//        TODO continue from here
    }
    return decodedHands;
}

/*
You are given a list of hands, where each integer in the vector represents a hand. The hand, which itself, is a list of cars is encoded into each integer.
*/
void poker_sort(vector<int>& a);