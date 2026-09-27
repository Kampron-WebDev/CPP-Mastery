#include <iostream>

// No * or & at the call site, no null checks needed: a reference always refers to something.
void addBonus(int& score, int bonus)
{
    score += bonus;
}

void clampTo100(int& score)
{
    if (score > 100) score = 100;
}

int main()
{
    int alice{85};
    int& ref = alice;
    addBonus(ref, 20);
    clampTo100(alice);
    std::cout << "Alice: " << ref << '\n';   // 100
}
