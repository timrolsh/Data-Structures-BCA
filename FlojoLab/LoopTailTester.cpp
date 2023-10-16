#include <iostream>

#include "FlojoLab.hpp"

using std::cout;

int main() {
    cout
            << "Josephus Tests involve reading from a file, and do not work with Make. Run those with the following command instead: \n\t g++ FlojoLab.cpp JosephusTester.cpp; ./a.out\n";
    cout << "loopTail Tests: \n";
    Link<int> *l1 = nullptr;
    vector<int> t1 = loopTail(l1);
    cout << "\tTest 1: " << (t1 == vector<int>{0, 0}) << '\n';

    // Test 2: List without loop
    Link<int> *l2 = new Link<int>(1);
    l2->next = new Link<int>(2);
    vector<int> t2 = loopTail(l2);
    cout << "\tTest 2: " << (t2 == vector<int>{0, 2}) << '\n';

    // Test 3: List with loop, no tail
    Link<int> *l3 = new Link<int>(1);
    l3->next = new Link<int>(2);
    l3->next->next = new Link<int>(3);
    l3->next->next->next = l3;
    vector<int> t3 = loopTail(l3);
    cout << "\tTest 3: " << (t3 == vector<int>{3, 0}) << '\n';

    // Test 4: List with loop and tail
    Link<int> *l4 = new Link<int>(1);
    l4->next = new Link<int>(2);
    l4->next->next = new Link<int>(3);
    l4->next->next->next = new Link<int>(4);
    l4->next->next->next->next = l4->next;
    vector<int> t4 = loopTail(l4);
    cout << "\tTest 4: " << (t4 == vector<int>{3, 1}) << '\n';

    Link<int> *l5 = new Link<int>(1);
    vector<int> t5 = loopTail(l5);
    cout << "\tTest 5: " << (t5 == vector<int>{0, 1}) << '\n';

    // Test 6: Single node, self-loop
    Link<int> *l6 = new Link<int>(1);
    l6->next = l6;
    vector<int> t6 = loopTail(l6);
    cout << "\tTest 6: " << (t6 == vector<int>{1, 0}) << '\n';
    Link<int> *l7 = new Link<int>(1);
    l7->next = new Link<int>(2);
    l7->next->next = l7->next;
    vector<int> t7 = loopTail(l7);
    cout << "\tTest 7: " << (t7 == vector<int>{1, 1}) << '\n';
    Link<int> *l8 = new Link<int>(1);
    l8->next = new Link<int>(2);
    l8->next->next = new Link<int>(3);
    l8->next->next->next = new Link<int>(4);
    l8->next->next->next->next = new Link<int>(5);
    l8->next->next->next->next->next = l8->next->next;
    vector<int> t8 = loopTail(l8);
    cout << "\tTest 8: " << (t8 == vector<int>{3, 2});

}