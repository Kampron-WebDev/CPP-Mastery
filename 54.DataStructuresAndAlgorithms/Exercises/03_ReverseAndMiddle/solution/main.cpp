#include <iostream>
#include <vector>

struct Node {
    int value;
    Node* next;
};

// Builds a list inside `storage` (which owns the memory) and returns the head.
Node* build(std::vector<Node>& storage, int n)
{
    storage.assign(static_cast<std::size_t>(n), Node{0, nullptr});
    for (int i = 0; i < n; ++i) {
        storage[static_cast<std::size_t>(i)].value = i + 1;
        storage[static_cast<std::size_t>(i)].next = (i + 1 < n) ? &storage[static_cast<std::size_t>(i + 1)] : nullptr;
    }
    return n ? &storage[0] : nullptr;
}

Node* reverse(Node* head)   // O(n) time, O(1) memory
{
    Node* previous = nullptr;
    while (head) {
        Node* next = head->next;
        head->next = previous;
        previous = head;
        head = next;
    }
    return previous;
}

Node* middle(Node* head)   // fast moves 2 steps while slow moves 1: when fast ends, slow is in the middle
{
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

bool hasCycle(Node* head)  // in a cycle, the fast runner eventually laps the slow one
{
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

void print(const Node* n)
{
    for (; n; n = n->next) std::cout << n->value << (n->next ? "->" : "\n");
}

int main()
{
    std::vector<Node> a, b, c;
    Node* odd = build(a, 5);
    Node* even = build(b, 4);
    std::cout << "middle of 1..5: " << middle(odd)->value << ", middle of 1..4: " << middle(even)->value << '\n';
    odd = reverse(odd);
    print(odd);

    Node* loop = build(c, 6);
    std::cout << std::boolalpha << "cycle? " << hasCycle(loop);
    c.back().next = &c[2];   // 6 -> 3 creates a cycle
    std::cout << " / after linking 6->3: " << hasCycle(loop) << '\n';
}
