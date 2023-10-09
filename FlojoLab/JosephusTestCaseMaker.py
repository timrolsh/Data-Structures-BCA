"""
The JosephusTextCases.txt file was generated using this program. The three variables can
be modified to generate different tests. This program uses an algorithm faster than the
circular linked lists method to generate the correct output order.
"""
import random

N_RANGE: int = 5000
K_RANGE: int = 6000
NUM_TEST_CASES: int = 100


def josephus_order(n: int, k: int) -> list[int]:
    # List to hold the order of eliminated persons
    order_of_elimination: list[int] = []

    # List to hold the persons in the game, initially [1, 2, ..., n]
    people: list[int] = list(range(1, n + 1))

    # Index of person to be eliminated
    index: int = 0

    # Continue until all persons are eliminated
    while len(people) > 0:
        # Count k-1 persons
        index = (index + k - 1) % len(people)
        # Add the eliminated person to the order list
        order_of_elimination.append(people.pop(index))

    return order_of_elimination


def main():
    with open("JosephusTestCases.txt", "w") as file:
        final_string: str = ""
    x: int = 1
    while x <= NUM_TEST_CASES:
        n: int = random.randrange(1, N_RANGE)
        k: int = random.randrange(1, K_RANGE)
        answer: list[int] = josephus_order(n, k)
        final_string += f"{n} {k} {' '.join([str(a) for a in answer])}\n"
        x += 1
    file.write(final_string)
    print("Done!")


print(josephus_order(1, 2))
print(josephus_order(1, 1))
