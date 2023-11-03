#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::vector;


enum Suit {
    CLUBS = 0, DIAMONDS = 1, HEARTS = 2, SPADES = 3
};

enum Rank {
    TWO = 0,
    THREE = 1,
    FOUR = 2,
    FIVE = 3,
    SIX = 4,
    SEVEN = 5,
    EIGHT = 6,
    NINE = 7,
    TEN = 8,
    JACK = 9,
    QUEEN = 10,
    KING = 11,
    ACE = 12
};


class Card {
public:
    Suit suit;
    Rank rank;

    /*
    Each card will be encoded as an integer 0 ≤ c ≤ 51 as follows: The possible
    ranks of a card {2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace} will be
    mapped in order to {0, 1, ..., 12}. The possible suits
    {Clubs, Diamonds, Hearts, Spades} will be mapped to {0, 1, 2, 3}. Then, if the
    mapped rank and suit of a card are r and s, respectively, the encoded value
    will be c = 4 * r + s.
    */
    explicit Card(int encodedCard) {
        suit = static_cast<Suit>(encodedCard % 4);
        rank = static_cast<Rank>(encodedCard / 4);
    }

    /*
    no arg constructor for Card is called when a blank hand is created, put some
    dummy values for the suits and ranks for now
    */
    Card() {
        suit = CLUBS;
        rank = TWO;
    }
};

class Hand {
public:
    vector<Card> list;
    int encodedHand;

    // when you create hands it will by default create a hand of 5 empty cards
    Hand() {
        list = vector<Card>(5);
        encodedHand = 0;
    }
};

/*
Given the vector of integers of encoded hands, create a vector of Hands and
cards within those hands so that it is easier to work with anf ot sort
*/
vector<Hand> decodeHands(vector<int> &encodedHands) {
    vector<Hand> decodedHands(encodedHands.size());
    for (int handIndex = 0; handIndex < encodedHands.size(); ++handIndex) {
        int encodedHand = encodedHands[handIndex];
        Hand &hand = decodedHands[handIndex];
        for (int cardIndex = 0; cardIndex < 5; ++cardIndex) {
            Card &card = hand.list[cardIndex];
            int encodedCard = encodedHand % 52;
            card.suit = static_cast<Suit>(encodedCard % 4);
            card.rank = static_cast<Rank>(encodedCard / 4);
            encodedHand /= 52;
        }
        hand.encodedHand = encodedHand;
    }
    return decodedHands;
}


/*
You are given a list of hands, where each integer in the vector represents a
hand. The hand, which itself, is a list of cars is encoded into each integer.
*/
void poker_sort(vector<int> &a) {
    vector<Hand> hands = decodeHands(a);
    return;
}
