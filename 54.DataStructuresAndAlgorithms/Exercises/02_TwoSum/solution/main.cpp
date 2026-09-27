#include <iostream>
#include <optional>
#include <unordered_map>
#include <utility>
#include <vector>

using Result = std::optional<std::pair<int, int>>;

// O(n²) time, O(1) extra memory
Result twoSumBrute(const std::vector<int>& v, int target)
{
    for (int i = 0; i < static_cast<int>(v.size()); ++i)
        for (int j = i + 1; j < static_cast<int>(v.size()); ++j)
            if (v[static_cast<std::size_t>(i)] + v[static_cast<std::size_t>(j)] == target) return std::pair{i, j};
    return std::nullopt;
}

// O(n) time, O(n) memory: trade memory for speed
Result twoSumFast(const std::vector<int>& v, int target)
{
    std::unordered_map<int, int> seenAt;   // value -> index
    for (int i = 0; i < static_cast<int>(v.size()); ++i) {
        const int x = v[static_cast<std::size_t>(i)];
        if (auto it = seenAt.find(target - x); it != seenAt.end()) return std::pair{it->second, i};
        seenAt[x] = i;                     // insert AFTER checking, so x can't pair with itself
    }
    return std::nullopt;
}

void show(const char* label, const Result& r)
{
    std::cout << label;
    if (r) std::cout << '{' << r->first << ", " << r->second << "}\n";
    else std::cout << "none\n";
}

int main()
{
    show("brute {2,7,11,15} 9: ", twoSumBrute({2, 7, 11, 15}, 9));
    show("fast  {2,7,11,15} 9: ", twoSumFast({2, 7, 11, 15}, 9));
    show("fast  {3,2,4} 6:     ", twoSumFast({3, 2, 4}, 6));
    show("fast  {1,2} 7:       ", twoSumFast({1, 2}, 7));
}
