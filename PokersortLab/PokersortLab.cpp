/*
Tim Rolshud
Data Structures Period 1
November 7th, 2023
*/

#include <iostream>
#include <vector>
#include <thread>
#include <future>

using std::cout;
using std::vector;
using std::string;
using std::thread;
using std::promise;
using std::mutex;


/*
Insertion sort for smaller sized elements. This is a stable sort.
*/
template<typename Type>
vector<Type> mergeSortedVectors(vector<Type> vectorOne, vector<Type> vectorTwo) {
    vector<Type> mergedVector(vectorOne.size() + vectorTwo.size());
    int mergedVectorIndex = 0;
    int vectorOneIndex = 0;
    int vectorTwoIndex = 0;
    while (vectorOneIndex < vectorOne.size() && vectorTwoIndex < vectorTwo.size()) {
        if (vectorOne[vectorOneIndex] <= vectorTwo[vectorTwoIndex]) {
            mergedVector[mergedVectorIndex++] = vectorOne[vectorOneIndex++];
        } else {
            mergedVector[mergedVectorIndex++] = vectorTwo[vectorTwoIndex++];
        }
    }
    while (vectorOneIndex < vectorOne.size()) {
        mergedVector[mergedVectorIndex++] = vectorOne[vectorOneIndex++];
    }
    while (vectorTwoIndex < vectorTwo.size()) {
        mergedVector[mergedVectorIndex++] = vectorTwo[vectorTwoIndex++];
    }
    return mergedVector;
}


template<typename Type>
void insertionSort(vector<Type> &list) {
    for (int outerIndex = 1; outerIndex < list.size(); ++outerIndex) {
        Type key = list[outerIndex];
        int innerIndex = outerIndex - 1;
        // done with not <= to work with operator overload compare function for hands and cards
        while (innerIndex >= 0 && list[innerIndex] > key) {
            list[innerIndex + 1] = list[innerIndex];
            innerIndex = innerIndex - 1;
        }
        list[innerIndex + 1] = key;
    }
}

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

enum Type {
    HIGH_CARD = 0,
    ONE_PAIR = 1,
    TWO_PAIR = 2,
    THREE_OF_A_KIND = 3,
    STRAIGHT = 4,
    FLUSH = 5,
    FULL_HOUSE = 6,
    FOUR_OF_A_KIND = 7,
    STRAIGHT_FLUSH = 8
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
        suit = (Suit) (encodedCard % 4);
        rank = (Rank) (encodedCard / 4);
    }

    /*
    no arg constructor for Card is called when a blank hand is created, put some
    dummy values for the suits and ranks for now
    */
    Card() {
        suit = CLUBS;
        rank = TWO;
    }

//    operator overload for comparisons made while sorting cards in a hand
    bool operator<=(const Card &other) const {
        return rank <= other.rank;
    }

    bool operator>(const Card &other) const {
        return rank > other.rank;
    }

    bool operator==(const Card &other) const {
        return rank == other.rank && suit == other.suit;
    }
};

class Hand {
public:
//    TODO if this is doing a heap allocation, switch it to run on the stack
    vector<Card> list = vector<Card>(5);
    int encodedHand = 0;
    Type type = HIGH_CARD;
    // ranks for the cards with four of them in a four of a kind type of hand
    Rank rankOne = (Rank) (0);
    // ranks for the fifth card in a four of a kind type of hand
    Rank rankTwo = (Rank) (0);
    string s;

    /*
    This should only be called after the Hand class is created, and the list of
    cards is filled. This will determine the type of hand that the cards are.
    This is not in the constructor because the creation of the hands happens at
    an earlier stage than their cards are decoded and set to the correct values.
     */
    void determineHandType() {
        bool isFlush = true;
        bool isStraight = true;
        vector<int> rankCounts(13);

        Suit firstSuit = list[0].suit;
        Rank prevRank = list[0].rank;
        rankCounts[prevRank]++;

        for (int index = 1; index < 5; ++index) {
            // Check for flush
            isFlush &= (list[index].suit == firstSuit);

            // Check for straight, and check for special case for ace-low straight
            if ((list[index].rank != prevRank + 1) && (!(index == 4 && list[index].rank == ACE && prevRank == FIVE))) {
                isStraight = false;
            }
            prevRank = list[index].rank;

            // count ranks for pairs, three of a kind, full house, and four of a kind
            rankCounts[prevRank]++;
        }

        // ace slow straight special case, ace is the smallest card in this hand
        if ((isStraight) && list[0].rank == TWO && list[4].rank == ACE) {
            Card ace = list.back();
            list.pop_back();
            list.insert(list.begin(), ace);
            s = toString();
        }
        if (isStraight && isFlush) {
            type = STRAIGHT_FLUSH;
            return;
        } else if (isFlush) {
            type = FLUSH;
            return;
        } else if (isStraight) {
            type = STRAIGHT;
            return;
        }

        // determine pairs, three of a kind, full house, and four of a kind
        int pairs = 0;
        bool three = false;

        for (int index = 0; index < 13; ++index) {
            int count = rankCounts[index];
            if (count == 4) {
                type = FOUR_OF_A_KIND;
                rankOne = (Rank) index;
                // case where its 1 and 4
                if (list[0].rank != rankOne) {
                    rankTwo = list[0].rank;
                }
                    // case where its 4 and 1
                else {
                    rankTwo = list[4].rank;
                }
                return;
            } else if (count == 3) {
                rankOne = (Rank) (index);
                three = true;
            } else if (count == 2) {
                if (three) {
                    type = FULL_HOUSE;
                    rankTwo = (Rank) (index);
                    return;
                }
                if (pairs == 0) {
                    rankTwo = (Rank) (index);
                } else {
                    rankOne = (Rank) (index);
                }
                ++pairs;
            }
        }

        if (three && (pairs == 1)) {
            type = FULL_HOUSE;
            return;
        } else if (three) {
            type = THREE_OF_A_KIND;
            return;
        } else if (pairs == 2) {
            type = TWO_PAIR;
            return;
        } else if (pairs == 1) {
            type = ONE_PAIR;
            return;
        }
    }

    /*
    main comparison function used to compare these cards, operator overload for comparisons made while sorting
    This is set to <= so that merge sort can be stable and does not have to do twice as many comparisons
    */
    bool operator<=(const Hand &other) const {
        // if their types are different, return the one with the lower type
        if (type != other.type) {
            return type < other.type;
        }
            // logic for managing different types
        else {
            // in a straight flush, hand with the highest ranked card wins
            if (type == STRAIGHT_FLUSH || (type == STRAIGHT)) {
                return list[4].rank <= other.list[4].rank;
            }
                // in four of a kind
            else if (type == FOUR_OF_A_KIND) {
                // four ranks are different, the one with the higher four rank wins
                if (rankOne != other.rankOne) {
                    return (rankOne < other.rankOne);
                }
                    // four ranks are the same, the one with the higher 5th card rank wins
                else {
                    return rankTwo <= other.rankTwo;
                }
            } else if (type == FULL_HOUSE) {
                // the three cards are not the same rank, one with the higher rank wins
                if (rankOne != other.rankOne) {
                    return rankOne < other.rankOne;
                }
                // the three cards are the same rank, the one with the higher pair wins
                return rankTwo <= other.rankTwo;
            } else if (type == FLUSH) {
                for (int index = 4; index >= 0; --index) {
                    if (list[index].rank != other.list[index].rank) {
                        return list[index].rank < other.list[index].rank;
                    }
                }
                // if you've gone through the entire loop without finding anything, they are equal
                return true;
            } else if (type == THREE_OF_A_KIND) {
                if (rankOne != other.rankOne) {
                    return rankOne < other.rankOne;
                }

                // compare remaining two cards by rank
                Rank highCard = TWO;
                Rank otherHighCard = TWO;
                Rank lowCard = TWO;
                Rank otherLowCard = TWO;
                for (int index = 4; index >= 0; --index) {
                    if (list[index].rank != rankOne) {
                        highCard = list[index].rank;
                        --index;
                        while (index >= 0 && list[index].rank == rankOne) {
                            --index;
                        }
                        lowCard = list[index].rank;
                        break;
                    }
                }
                for (int index = 4; index >= 0; --index) {
                    if (other.list[index].rank != other.rankOne) {
                        otherHighCard = other.list[index].rank;
                        --index;
                        while (index >= 0 && other.list[index].rank == other.rankOne) {
                            --index;
                        }
                        otherLowCard = other.list[index].rank;
                        break;
                    }
                }
                if (highCard != otherHighCard) {
                    return highCard < otherHighCard;
                } else {
                    return lowCard <= otherLowCard;
                }
            } else if (type == TWO_PAIR) {
                if (rankOne != other.rankOne) {
                    return rankOne < other.rankOne;
                } else if (rankTwo != other.rankTwo) {
                    return rankTwo < other.rankTwo;
                }
                Rank fifthCard;
                Rank otherFifthCard;
                for (int index = 0; index < 5; ++index) {
                    if (list[index].rank != rankOne && list[index].rank != rankTwo) {
                        fifthCard = list[index].rank;
                    }
                    if (other.list[index].rank != other.rankOne && other.list[index].rank != other.rankTwo) {
                        otherFifthCard = other.list[index].rank;
                    }
                }
                return fifthCard <= otherFifthCard;
            } else if (type == ONE_PAIR) {
                if (rankTwo != other.rankTwo) {
                    return rankTwo < other.rankTwo;
                }
                int index = 4;
                int otherIndex = 4;
                while (index >= 0 && otherIndex >= 0) {
                    // we can compare two cards that are not pairs for both hands
                    if (list[index].rank != rankTwo && other.list[otherIndex].rank != other.rankTwo) {
                        // if these cards aren't the same rank, we can compare them
                        if (list[index].rank != other.list[otherIndex].rank) {
                            return list[index].rank < other.list[otherIndex].rank;
                        }
                        // these cards are the same rank, keep looking if we can find another 2 cards to compare
                        --index;
                        --otherIndex;
                    }
                    if (list[index].rank == rankTwo) {
                        --index;
                    }
                    if (other.list[otherIndex].rank == other.rankTwo) {
                        --otherIndex;
                    }
                }
                return true;
            }
            // otherwise there is a high card, get the highest card
            for (int index = 4; index >= 0; --index) {
                if (list[index].rank != other.list[index].rank) {
                    return list[index].rank < other.list[index].rank;
                }
            }
        }
        return true;
    }

    bool operator>(const Hand &other) const {
        return !(*this <= other);
    }

    string toString() {
        string handString = "[";
        for (int index = 0; index < 5; ++index) {
            Card card = list[index];
            Rank rank = card.rank;
            Suit suit = card.suit;
            if (rank == TWO) {
                handString += "2";
            } else if (rank == THREE) {
                handString += "3";
            } else if (rank == FOUR) {
                handString += "4";
            } else if (rank == FIVE) {
                handString += "5";
            } else if (rank == SIX) {
                handString += "6";
            } else if (rank == SEVEN) {
                handString += "7";
            } else if (rank == EIGHT) {
                handString += "8";
            } else if (rank == NINE) {
                handString += "9";
            } else if (rank == TEN) {
                handString += "10";
            } else if (rank == JACK) {
                handString += "Jack";
            } else if (rank == QUEEN) {
                handString += "Queen";
            } else if (rank == KING) {
                handString += "King";
            } else if (rank == ACE) {
                handString += "Ace";
            }
            handString += " of ";
            if (suit == CLUBS) {
                handString += "Clubs";
            } else if (suit == DIAMONDS) {
                handString += "Diamonds";
            } else if (suit == HEARTS) {
                handString += "Hearts";
            } else if (suit == SPADES) {
                handString += "Spades";
            }
            if (index != 4) {
                handString += ", ";
            }
        }
        handString += "]";
        return handString;
    }
};


/*
Given the vector of integers of encoded hands, create a vector of Hands and
cards within those hands so that it is easier to work with anf ot sort
*/
void decodeHands(vector<int> &encodedHands, int start, int end, vector<Hand> &decodedHands) {
    for (int handIndex = start; handIndex < end; ++handIndex) {
        int encodedHand = encodedHands[handIndex];
        Hand &hand = decodedHands[handIndex];
        hand.encodedHand = encodedHand;
        for (int cardIndex = 0; cardIndex < 5; ++cardIndex) {
            Card &card = hand.list[cardIndex];
            int encodedCard = encodedHand % 52;
            card.suit = (Suit) (encodedCard % 4);
            card.rank = (Rank) (encodedCard / 4);
            encodedHand /= 52;
        }

        // sort the cards in a hand once they are created
        insertionSort(hand.list);
        // determine the hand's type once it has been established
        hand.determineHandType();
        // make toString for debugging purposes
        // hand.s = hand.toString();
    }
}

mutex mtxActiveThreads;

/*
This implementation is specifically ment for Hands, as it takes
the resulting hands and writes them to the answer poker_sort vector.
*/
vector<Hand> mergeSort(const vector<Hand> &hands, int &activeThreads, const int &maxThreads) {
    // base case, hands is of size one, back out
    if (hands.size() <= 1) {
        return hands;
    }
    int middleIndex = (int) hands.size() / 2;
    // left
    promise<vector<Hand>> leftPromise;
    thread *lt = nullptr;
    // if we can make some more threads, start other merge sorts in parallel
    mtxActiveThreads.lock();
    if (activeThreads < maxThreads) {
        ++activeThreads;
        thread *leftThread = new thread([&]() {
            leftPromise.set_value(
                    mergeSort(vector<Hand>(hands.begin(), hands.begin() + middleIndex), activeThreads, maxThreads));
        });
        lt = leftThread;
        mtxActiveThreads.unlock();
    }
        // otherwise there are no more threads, sort in this thread
    else {
        mtxActiveThreads.unlock();
        leftPromise.set_value(
                mergeSort(vector<Hand>(hands.begin(), hands.begin() + middleIndex), activeThreads, maxThreads));
    }
    // right
    promise<vector<Hand>> rightPromise;
    thread *rt = nullptr;
    // if we can make some more threads, start other merge sorts in parallel
    mtxActiveThreads.lock();
    if (activeThreads < maxThreads) {
        ++activeThreads;
        thread *rightThread = new thread([&]() {
            rightPromise.set_value(
                    mergeSort(vector<Hand>(hands.begin() + middleIndex, hands.end()), activeThreads, maxThreads));
        });
        rt = rightThread;
        mtxActiveThreads.unlock();
    }
        // otherwise there are no more threads, sort in this thread
    else {
        mtxActiveThreads.unlock();
        rightPromise.set_value(
                mergeSort(vector<Hand>(hands.begin() + middleIndex, hands.end()), activeThreads, maxThreads));
    }
    // if these were done by threads, wait for them to finish before merging them
    if (lt != nullptr) {
        lt->join();
        delete lt;
        mtxActiveThreads.lock();
        --activeThreads;
        mtxActiveThreads.unlock();
    }
    if (rt != nullptr) {
        rt->join();
        delete rt;
        mtxActiveThreads.lock();
        --activeThreads;
        mtxActiveThreads.unlock();
    }
    // merge the two sorted vectors
    vector<Hand> left = leftPromise.get_future().get();
    vector<Hand> right = rightPromise.get_future().get();
    return mergeSortedVectors(left, right);
}

/*
You are given a list of hands, where each integer in the vector represents a
hand. The hand, which itself, is a list of cars is encoded into each integer.
*/
void poker_sort(vector<int> &a) {
    // decide how many threads we are going to use for this algorithm based on the size of the list
    int threadCount = (int) a.size() / 20000;
    if (threadCount == 0) {
        threadCount = 1;
    }
    vector<thread> threads;
    // main list of hands to work with
    vector<Hand> hands(a.size());
    // decode the hands into the vector of hands in parallel
    int blockSize = (int) a.size() / threadCount;
    int start = 0;
    int end = blockSize;
    while (start < a.size()) {
        threads.emplace_back(decodeHands, ref(a), start, end, ref(hands));
        start += blockSize;
        end += blockSize;
    }

    // wait for threads to finish decoding hands
    for (thread &thr: threads) {
        thr.join();
    }
    threads.clear();

    // sort these hands
    int activeThreads = 0;
    --threadCount;
    vector<Hand> answer = mergeSort(hands, activeThreads, threadCount);
    // encode the hands back into the vector of integers
    for (int index = 0; index < a.size(); ++index) {
        a[index] = answer[index].encodedHand;
    }
}
