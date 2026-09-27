// A binary search tree: left < node < right. In-order traversal visits values in SORTED order.
#include <algorithm>
#include <iostream>
#include <memory>

class BST {
    struct Node {
        int value;
        std::unique_ptr<Node> left, right;
    };

public:
    void insert(int v) { insert(root, v); }
    bool contains(int v) const
    {
        const Node* n = root.get();
        while (n) {                       // O(height): O(log n) if balanced, O(n) if it degenerates into a line
            if (v == n->value) return true;
            n = (v < n->value) ? n->left.get() : n->right.get();
        }
        return false;
    }
    void printInOrder() const { inOrder(root.get()); std::cout << '\n'; }
    int height() const { return height(root.get()); }

private:
    static void insert(std::unique_ptr<Node>& n, int v)
    {
        if (!n) { n = std::make_unique<Node>(Node{v, nullptr, nullptr}); return; }
        if (v < n->value) insert(n->left, v);
        else if (v > n->value) insert(n->right, v);   // duplicates ignored
    }
    static void inOrder(const Node* n)
    {
        if (!n) return;
        inOrder(n->left.get());
        std::cout << n->value << ' ';
        inOrder(n->right.get());
    }
    static int height(const Node* n) { return n ? 1 + std::max(height(n->left.get()), height(n->right.get())) : 0; }

    std::unique_ptr<Node> root;
};

int main()
{
    BST tree;
    for (int v : {50, 30, 70, 20, 40, 60, 80, 35}) tree.insert(v);
    /*
                50
              /    \
            30      70
           /  \    /  \
         20   40  60   80
             /
           35
    */
    tree.printInOrder();   // 20 30 35 40 50 60 70 80 (sorted!)
    std::cout << std::boolalpha << "contains 60? " << tree.contains(60) << ", contains 65? " << tree.contains(65) << '\n';
    std::cout << "height: " << tree.height() << '\n';

    BST line;
    for (int v = 1; v <= 8; ++v) line.insert(v);   // sorted input → a "stick", not a bushy tree
    std::cout << "height after inserting 1..8 in order: " << line.height() << " (why std::map self-balances!)\n";
}
