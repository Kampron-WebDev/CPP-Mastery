// ⭐⭐ Exercise 02: PointerToReference
// Rewrite this program so it uses REFERENCES instead of pointers everywhere.
// Behaviour and output must stay the same. Which version is easier to read? Why?
#include <iostream>

void addBonus(int* score, int bonus)
{
    *score += bonus;
}

void clampTo100(int* score)
{
    if (*score > 100) *score = 100;
}

int main()
{
    int alice{85};
    int* ref = &alice;
    addBonus(ref, 20);
    clampTo100(&alice);
    std::cout << "Alice: " << *ref << '\n';   // 100
}
