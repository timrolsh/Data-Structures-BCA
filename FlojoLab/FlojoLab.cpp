#include "FlojoLab.hpp"

#include <iostream>
#include <string>

using std::cout;
using std::string;

vector<int> loopTail(Link<int> *head) {
    int loopLength = 0;
    int tailLength = 0;
    // edge case where a nullptr linked list is passed
    if (head != nullptr) {
        Link<int> *slow = head;
        Link<int> *fast = head;
        // first stage, determine whether the linked list is circular or not
        slow = slow->next;
        // prevent dereferencing nullptr and causing segfault
        if (fast->next == nullptr) {
            fast = nullptr;
        } else {
            fast = fast->next->next;
        }
        while (fast != nullptr && fast != slow) {
            slow = slow->next;
            // prevent dereferencing nullptr and causing segfault
            if (fast->next == nullptr) {
                fast = nullptr;
            } else {
                fast = fast->next->next;
            }
        }
        // second stage: get the length of the loop, will be skipped if the linked list is not circular and the fast pointer reached the end and is null
        if (fast != nullptr) {
            ++loopLength;
            fast = fast->next;
            while (slow != fast) {
                fast = fast->next;
                ++loopLength;
            }
        }
        // third stage, get the tail length of the linked list
        slow = head;
        fast = head;
        for (int _ = 0; _ < loopLength; ++_) {
            fast = fast->next;
        }
        while (fast != nullptr) {
            // if the list is circular and it comes back on itself, break the loop as we now have the tail length
            if (slow == fast && loopLength > 0) {
                break;
            }
            slow = slow->next;
            fast = fast->next;
            ++tailLength;
        }
    }
    vector<int> answer(2);
    answer[0] = loopLength;
    answer[1] = tailLength;
    return answer;
}

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
        // edge case: k = 1
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
    // at this point head will be a linked list of itself, set the next element to null so that the destructor doesn't fail
    head->next = nullptr;
    delete head;
    return removeList;
}
