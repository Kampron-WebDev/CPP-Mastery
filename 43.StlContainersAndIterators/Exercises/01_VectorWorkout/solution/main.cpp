#include <iostream>
#include <vector>
#include <array>

int main()
{
    std::vector<int> v;
    std::cout << "Numbers (0 to stop): ";
    for (int x; std::cin >> x && x != 0;) {
        v.push_back(x);
        std::cout << "  size " << v.size() << ", capacity " << v.capacity() << '\n';   // GCC: 1 2 4 8 16 ... (doubling)
    }
    if (v.empty()) return 0;

    for (auto it = v.begin(); it != v.end(); ++it) std::cout << *it << ' ';
    std::cout << '\n';
    for (auto it = v.rbegin(); it != v.rend(); ++it) std::cout << *it << ' ';
    std::cout << '\n';

    if (v.size() > 2) {
        for (auto it = v.begin() + 1; it != v.end() - 1; ++it) std::cout << *it << ' ';
        std::cout << '\n';
    }

    std::array<int, 3> firstThree{};
    for (std::size_t i = 0; i < firstThree.size() && i < v.size(); ++i) firstThree[i] = v[i];
    for (int x : firstThree) std::cout << x << ' ';
    std::cout << '\n';
}
