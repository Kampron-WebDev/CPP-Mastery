#include <iostream>
#include <memory>

struct Child;

struct Parent {
    std::shared_ptr<Child> child;   // the parent OWNS the child
    ~Parent() { std::cout << "Parent destroyed\n"; }
};

struct Child {
    std::weak_ptr<Parent> parent;   // the child only OBSERVES the parent: no ownership, no cycle
    void greetParent() const
    {
        if (auto p = parent.lock())   // shared_ptr if the parent still exists, else empty
            std::cout << "Hi parent! (parent alive, use_count " << p.use_count() << ")\n";
        else
            std::cout << "Parent is gone\n";
    }
    ~Child() { std::cout << "Child destroyed\n"; }
};

// Why the original leaked: at the end of main, the local p and c are released, but the Parent
// is still owned by c->parent and the Child by p->child. Each count stays at 1 forever.
int main()
{
    auto p = std::make_shared<Parent>();
    auto c = std::make_shared<Child>();
    p->child = c;
    c->parent = p;
    c->greetParent();
}   // both destructors now run
