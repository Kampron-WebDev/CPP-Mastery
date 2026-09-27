#include <iostream>

// A) global: works, but ANY function in the program could change visitsA by mistake.
int visitsA{0};
void visitA()
{
    ++visitsA;
    std::cout << "[A] Visit number " << visitsA << '\n';
}

// B) static local: survives between calls, but only visitB can see it.
void visitB()
{
    static int visits{0};   // initialized once, the first time
    ++visits;
    std::cout << "[B] Visit number " << visits << '\n';
}

int main()
{
    for (int i = 0; i < 3; ++i) visitA();
    for (int i = 0; i < 3; ++i) visitB();
}
// B is safer: the counter is hidden (smallest scope) yet keeps its value (static lifetime).
