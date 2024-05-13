from enum import Enum

class Suit(Enum):
    CLUBS = 0
    DIAMONDS = 1
    HEARTS = 2
    SPADES = 3

class Rank(Enum):
    TWO = 0
    THREE = 1
    FOUR = 2
    FIVE = 3
    SIX = 4
    SEVEN = 5
    EIGHT = 6
    NINE = 7
    TEN = 8
    JACK = 9
    QUEEN = 10
    KING = 11
    ACE = 12

class Type(Enum):
    HIGH_CARD = 0
    ONE_PAIR = 1
    TWO_PAIR = 2
    THREE_OF_A_KIND = 3
    STRAIGHT = 4
    FLUSH = 5
    FULL_HOUSE = 6
    FOUR_OF_A_KIND = 7
    STRAIGHT_FLUSH = 8

class Card:
    def __init__(self, encoded_card: int):
        self.rank = Rank(encoded_card // 4)
        self.suit = Suit(encoded_card % 4)

    def __str__(self):
        return f'{self.rank.name} of {self.suit.name}'
    

def main() -> None:
    # Read all the cards from the 5 numbers on the the line given from stdin
    cards: list[Card] = [Card(int(encoded_card)) for encoded_card in input().split(" ")]




if __name__ == '__main__':
    main()
