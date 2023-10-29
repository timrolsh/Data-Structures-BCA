# Poker Sort
* in poker, you have a deck standard of 52 cards
* Ace is highest card, in some contexts it is the lowest card
* there are hearts, spades, diamonds, and clubs
* the task is to given some hands in poker, sort them
	* you want to have a hand class and a card class
	* in the constructor of Hand class, compute a quantity that represents the rank and then make the comparisons by ranks through operator overloading, encode it into an integer and then compare integers
	* no using library sort
	* largest input should have a million hands
## Poker Hands (highest to least)
* **Straight**: ace can be the lowest or the highest in this context
	* A, 2, 3, 4, 5
	* 2, 3, 4, 5 ,6
	* 10, J, Q, K, A
* **Flush**: all suits are the same, no particular order
	* why suits matter in poker
* **Straight Flush**: combination of both a straight and a flush (A, 2, 3, 4, 5) that are all the same suit
* **Full house**: 3 of a kind + pair
* **4 of a kind**
* **full house**
* **flash**
* **3 of a kind**
* **2 pairs**
* **pair**
* **high card**: you have no hands whatsoever, so you go by who has the highest card
	* in this case, sort lexicographically from highest lowest and rank them there
## Suits are ranked
Clubs 0
Diamonds 1
Hearts 2
Spades 3
Use threads to parallelize calculation of integers and merge sort potentially
## Encoding method (tell which card is which)
* Hands are given as an int formatted in this way
* 2 of clubs `$->$` 4* 0 + 0 = 0
* 7 of diamonds `$->$` 4 * 5 + 1 = 21
* Ace of spades `$->$` 4 * 12 + 3 = 51
* Hand = `$52c^0c_0 + 52c_1 + 52^2c_2 + 52^3c_3 + 52^4c^4$`
	* this fits into a 32 bit integer, your responsibility to decode it
	* look at the way it was done in cryptology where message bytes were encoded into numbers
## Hands
* a Vector of 5 integers