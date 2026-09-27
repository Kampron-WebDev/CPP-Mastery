// ⭐⭐ Exercise 01: NoRawLoops
// Rewrite every numbered loop below using ONE standard algorithm each (no for/while allowed).
// The output must stay identical.
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v{7, -3, 12, 0, 5, 12, -8, 3};

    // 1. sum
    int sum = 0;
    for (int x : v) sum += x;
    std::cout << "sum " << sum << '\n';

    // 2. count of 12s
    int twelves = 0;
    for (int x : v) if (x == 12) ++twelves;
    std::cout << "twelves " << twelves << '\n';

    // 3. any negative?
    bool anyNeg = false;
    for (int x : v) if (x < 0) { anyNeg = true; break; }
    std::cout << "anyNeg " << anyNeg << '\n';

    // 4. largest
    int best = v[0];
    for (int x : v) if (x > best) best = x;
    std::cout << "max " << best << '\n';

    // 5. doubled copy
    std::vector<int> doubled;
    for (int x : v) doubled.push_back(x * 2);
    std::cout << "doubled[2] " << doubled[2] << '\n';

    // 6. sort descending
    for (std::size_t i = 0; i < v.size(); ++i)
        for (std::size_t j = i + 1; j < v.size(); ++j)
            if (v[j] > v[i]) { int t = v[i]; v[i] = v[j]; v[j] = t; }
    std::cout << "first " << v.front() << ", last " << v.back() << '\n';
}
