#include <iostream>
#include <vector>
#include <algorithm>
#include <compare>

struct Version {
    int major;
    int minor;
    int patch;

    auto operator<=>(const Version&) const = default;   // compares major, then minor, then patch
    bool operator==(const Version&) const = default;

    friend std::ostream& operator<<(std::ostream& os, const Version& v)
    {
        return os << v.major << '.' << v.minor << '.' << v.patch;
    }
};

int main()
{
    std::vector<Version> versions{{1, 10, 0}, {1, 2, 3}, {2, 0, 0}, {1, 2, 10}, {0, 9, 9}};
    std::sort(versions.begin(), versions.end());   // uses the generated <
    for (const auto& v : versions) std::cout << v << ' ';
    std::cout << '\n';

    std::cout << std::boolalpha << (Version{1, 2, 3} >= Version{1, 2, 3}) << '\n';
}
