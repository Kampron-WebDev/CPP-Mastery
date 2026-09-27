#include <iostream>
#include <vector>
#include <algorithm>

void print(const std::vector<int>& v)
{
    for (int x : v) std::cout << x << ' ';
    std::cout << '\n';
}

int main()
{
    const std::vector<int> original{1, 2, 4, 5, 6, 7, 8, 9};
    auto isEven = [](int x) { return x % 2 == 0; };

    // A) erase returns an iterator to the element AFTER the erased one
    std::vector<int> a = original;
    for (auto it = a.begin(); it != a.end();) {
        if (isEven(*it)) it = a.erase(it);
        else ++it;
    }
    print(a);

    // B) erase-remove: remove_if moves the keepers forward, erase cuts off the tail (one pass: O(n))
    std::vector<int> b = original;
    b.erase(std::remove_if(b.begin(), b.end(), isEven), b.end());
    print(b);

    // C) C++20: one call, impossible to get wrong
    std::vector<int> c = original;
    std::erase_if(c, isEven);
    print(c);
}
