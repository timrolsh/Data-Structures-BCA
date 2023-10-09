#include "FlojoLab.hpp"

#include <iostream>
#include <string>

using std::cout;
using std::string;

template <class T> vector<int> loopTail(Link<T> *head) {
    int loopLength = 0;
    int tailLength = 0;
//    edge case: the circular linked list is just one node pointing to itself

    if (head != nullptr) {
        Link<T> *slow = head;
        Link <T> *fast = head;
        while (!(slow == nullptr || fast == nullptr || slow == fast)) {
            slow = slow->next;
            fast = fast->next;
            if (fast != nullptr) {
                fast = fast->next;
            }
        }
//        now we know its circular, find the length of the list
        if (slow == fast) {
            fast = fast->next;
            ++loopLength;
            while (slow != fast) {
                fast = fast->next;
                ++loopLength;
            }
        }



    }
    vector<int> answer(2);
    answer[0] = loopLength;
    answer[1] = tailLength;
}


//string circularListToString(Link<int> *list) {
//    Link<int> *head = list;
//    string answer = "[";
//    int timesSame = 0;
//    while (timesSame < 2) {
//        if (head == list) {
//            ++timesSame;
//        }
//        answer += ""
//    }
//
//
//}

/*
Given a number n, create a circular linked list that starts with the number 1
and goes all the way to n inclusive. The Node that contains the number n will
point back to the note that contains the number 1. Return a two element vector where the node with the number 1 is the first element and the node with the number n is the second element
*/
vector<Link<int> *> createCircularLinkedList(int n) {
    Link<int> *head = new Link<int>(1);
    Link<int> *tail = head;
    for (int number = 2; number <= n; ++number) {
        Link<int> *temp = new Link<int>(number);
        tail->next = temp;
        tail = temp;
    }
    tail->next = head;
    vector<Link<int> *> answer;
    answer.push_back(head);
    answer.push_back(tail);
    return answer;
}

vector<int> josephus(int n, int k) {
    vector<Link<int> *> temp = createCircularLinkedList(n);
    Link<int> *head = temp[0], *tail = temp[1];
    vector<int> removeList(n);
    int vectorIndex = 0;
    while (n > 1) {
        Link<int> *first, *remove, *second;
//        edge case: k = 1
        if (k == 1) {
            first = tail;
        } else {
            first = head;
            for (int a = 1; a <= k - 2; ++a) {
                first = first->next;
            }
        }
        remove = first->next;
        second = remove->next;
        // add the element we are removing to the list
        removeList[vectorIndex++] = remove->info;
        // make first point to second (drop the removed node from the list)
        first->next = second;
        // set the removed node's next to nullptr so that its destructor won't
        // remove the rest of the list
        remove->next = nullptr;
        // delete the removed node from memory
        delete remove;
        // set the new head of the list to be second
        head = second;
        // decrement n by 1 as we just removed an element from the linked list
        --n;
    }
    // after the loop finishes, there will only be one element left in the
    // linked list, and it will be head. Remove it, delete the final node, and
    // return the final vector
    removeList[vectorIndex] = head->info;
//    at this point head will be a linked list of itself, set the next element to null so that the destructor doesn't fail
    head->next = nullptr;
    delete head;
    return removeList;
}
