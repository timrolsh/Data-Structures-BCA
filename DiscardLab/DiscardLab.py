import random
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


class HandType(Enum):
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

    def __repr__(self):
        return f'{self.rank.name} of {self.suit.name}'


"""
Determine the type of hand you currently have given the 5 cards.
"""


def get_hand_type(cards: list[Card]) -> HandType:
    is_flush: bool = True
    is_straight: bool = True
    rank_counts: list[int] = [0 for _ in range(13)]

    first_suit: Suit = cards[0].suit
    prev_rank: Rank = cards[0].rank
    rank_counts[prev_rank.value] += 1

    for index in range(1, 5):
        # Check for flush
        is_flush &= (cards[index].suit == first_suit)

        # Check for straight, and check for special case for ace-low straight
        if ((cards[index].rank != prev_rank.value + 1) and (not (index == 4 and cards[index].rank == Rank.ACE and prev_rank == Rank.FIVE))):
            is_straight = False
        prev_rank = cards[index].rank

        # Count ranks for pairs, three of a kind, full house, and four of a kind
        rank_counts[prev_rank.value] += 1

    # Ace slow straight special case, ace is the smallest card in this hand
    if ((is_straight) and cards[0].rank == Rank.TWO and cards[4].rank == Rank.ACE):
        # Move the last card to the first element
        cards.insert(0, cards.pop())

    if (is_straight and is_flush):
        return HandType.STRAIGHT_FLUSH
    elif (is_flush):
        return HandType.FLUSH
    elif (is_straight):
        return HandType.STRAIGHT

    # Determine pairs, three of a kind, full house, and four of a kind
    pairs: int = 0
    three: bool = False

    for index in range(13):
        count: int = rank_counts[index]
        if (count == 4):
            return HandType.FOUR_OF_A_KIND
        elif (count == 3):
            three = True
        elif (count == 2):
            if (three):
                return HandType.FULL_HOUSE
            pairs += 1

    if (three and (pairs == 1)):
        return HandType.FULL_HOUSE
    elif (three):
        return HandType.THREE_OF_A_KIND
    elif (pairs == 2):
        return HandType.TWO_PAIR
    elif (pairs == 1):
        return HandType.ONE_PAIR
    else:
        return HandType.HIGH_CARD


def main() -> None:
    # Read all the cards from the 5 numbers on the the line given from stdin
    cards: list[Card] = [Card(int(encoded_card)) for encoded_card in input().split(" ")]
    type: HandType = get_hand_type(cards)


if __name__ == '__main__':
    main()
