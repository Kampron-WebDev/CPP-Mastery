// ⭐⭐ Exercise 02: InvalidationTrap
// Task: remove every EVEN number from the vector.
// The loop below is BROKEN: erase() invalidates `it`, then ++it uses a dead iterator (UB).
// Fix it THREE ways:
//   A) use the iterator returned by erase()
//   B) the erase-remove idiom: v.erase(std::remove_if(...), v.end());
//   C) C++20: std::erase_if(v, predicate);
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v{1, 2, 4, 5, 6, 7, 8, 9};
    // for (auto it = v.begin(); it != v.end(); ++it)
    //     if (*it % 2 == 0) v.erase(it);          // BUG
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';
}
