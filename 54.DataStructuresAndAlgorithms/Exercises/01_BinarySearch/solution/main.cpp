#include <algorithm>
#include <iostream>
#include <vector>

// O(log n)
int binarySearch(const std::vector<int>& a, int target)
{
    int lo = 0, hi = static_cast<int>(a.size()) - 1;
    while (lo <= hi) {
        const int mid = lo + (hi - lo) / 2;
        const int value = a[static_cast<std::size_t>(mid)];
        if (value == target) return mid;
        if (value < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// O(log n). Invariant: everything before lo is < target; everything from hi on is >= target.
std::size_t firstAtLeast(const std::vector<int>& a, int target)
{
    std::size_t lo = 0, hi = a.size();   // half-open range [lo, hi)
    while (lo < hi) {
        const std::size_t mid = lo + (hi - lo) / 2;
        if (a[mid] < target) lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int main()
{
    const std::vector<std::vector<int>> tests{{}, {5}, {1, 3, 5, 7, 9}, {2, 2, 2, 4, 4, 8}};
    int mismatches{0};
    for (const auto& v : tests) {
        for (int target = -1; target <= 10; ++target) {
            const auto expected = static_cast<std::size_t>(std::lower_bound(v.begin(), v.end(), target) - v.begin());
            if (firstAtLeast(v, target) != expected) ++mismatches;
            const int idx = binarySearch(v, target);
            const bool present = std::binary_search(v.begin(), v.end(), target);
            if ((idx != -1) != present || (idx != -1 && v[static_cast<std::size_t>(idx)] != target)) ++mismatches;
        }
    }
    std::cout << "binarySearch({1,3,5,7,9}, 7) = " << binarySearch(tests[2], 7) << '\n';
    std::cout << "firstAtLeast({2,2,2,4,4,8}, 3) = " << firstAtLeast(tests[3], 3) << '\n';
    std::cout << (mismatches == 0 ? "All edge-case checks passed" : "MISMATCHES FOUND") << '\n';
}
