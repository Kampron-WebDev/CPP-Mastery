// ⭐⭐ Exercise 03: ReverseAndMiddle
// Using this minimal node:   struct Node { int value; Node* next; };
// (raw pointers on purpose: interviews use them; nodes live in a std::vector here so there are no leaks)
// Write:
//   Node* reverse(Node* head)          -> returns the new head, O(n) time, O(1) memory
//   Node* middle(Node* head)           -> the middle node in ONE pass (hint: slow & fast pointers)
//   bool hasCycle(Node* head)          -> Floyd's tortoise and hare
// Test with 1->2->3->4->5 (middle 3), 1->2->3->4 (middle 3, the second middle), and a list with a cycle.
#include <iostream>
#include <vector>

struct Node {
    int value;
    Node* next;
};

int main()
{
    // TODO
}
