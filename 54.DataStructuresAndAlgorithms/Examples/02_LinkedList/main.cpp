// A singly linked list built with unique_ptr: no manual delete, no leaks.
#include <iostream>
#include <memory>
#include <utility>

class IntList {
    struct Node {
        int value;
        std::unique_ptr<Node> next;   // each node OWNS the next one
    };

public:
    void pushFront(int value)   // O(1)
    {
        head = std::make_unique<Node>(Node{value, std::move(head)});
        ++count;
    }

    bool remove(int value)      // O(n): must walk to find it
    {
        std::unique_ptr<Node>* link = &head;           // pointer to "the link that points at the current node"
        while (*link) {
            if ((*link)->value == value) {
                *link = std::move((*link)->next);      // unlink: the removed node is freed automatically
                --count;
                return true;
            }
            link = &(*link)->next;
        }
        return false;
    }

    void reverse()              // O(n), a classic interview question
    {
        std::unique_ptr<Node> previous;
        while (head) {
            auto next = std::move(head->next);
            head->next = std::move(previous);
            previous = std::move(head);
            head = std::move(next);
        }
        head = std::move(previous);
    }

    void print() const
    {
        for (const Node* n = head.get(); n; n = n->next.get()) std::cout << n->value << " -> ";
        std::cout << "null  (size " << count << ")\n";
    }

    ~IntList()   // destroy iteratively: the default recursive chain could overflow the stack for huge lists
    {
        while (head) head = std::move(head->next);
    }

private:
    std::unique_ptr<Node> head;
    std::size_t count{0};
};

int main()
{
    IntList list;
    for (int v : {5, 4, 3, 2, 1}) list.pushFront(v);
    list.print();
    list.remove(3);
    list.print();
    list.reverse();
    list.print();
}
