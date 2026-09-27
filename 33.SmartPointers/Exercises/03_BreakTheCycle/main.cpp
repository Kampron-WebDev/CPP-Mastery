// ⭐⭐⭐ Exercise 03: BreakTheCycle
// Parent holds shared_ptr<Child>; Child holds shared_ptr<Parent>.
// Run it: NEITHER destructor message prints. That's a memory leak caused by a cycle.
// 1. Explain (in a comment) why the counts never reach zero.
// 2. Fix it by changing ONE member to std::weak_ptr.
// 3. In Child::greetParent(), use lock() to safely reach the parent.
#include <iostream>
#include <memory>
#include <string>

struct Child;

struct Parent {
    std::shared_ptr<Child> child;
    ~Parent() { std::cout << "Parent destroyed\n"; }
};

struct Child {
    std::shared_ptr<Parent> parent;
    void greetParent() const { std::cout << "Hi parent!\n"; }
    ~Child() { std::cout << "Child destroyed\n"; }
};

int main()
{
    auto p = std::make_shared<Parent>();
    auto c = std::make_shared<Child>();
    p->child = c;
    c->parent = p;
    c->greetParent();
}
