#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <vector>

int main()
{
    std::vector<int> v{7, -3, 12, 0, 5, 12, -8, 3};

    std::cout << "sum " << std::accumulate(v.begin(), v.end(), 0) << '\n';
    std::cout << "twelves " << std::count(v.begin(), v.end(), 12) << '\n';
    std::cout << "anyNeg " << std::any_of(v.begin(), v.end(), [](int x) { return x < 0; }) << '\n';
    std::cout << "max " << *std::max_element(v.begin(), v.end()) << '\n';

    std::vector<int> doubled;
    std::transform(v.begin(), v.end(), std::back_inserter(doubled), [](int x) { return x * 2; });
    std::cout << "doubled[2] " << doubled[2] << '\n';

    std::sort(v.begin(), v.end(), std::greater<>{});
    std::cout << "first " << v.front() << ", last " << v.back() << '\n';
}
