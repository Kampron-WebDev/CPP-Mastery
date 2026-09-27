#include <stats/stats.h>

#include <iostream>
#include <vector>

int main()
{
    const std::vector<double> temperatures{21.5, 19.0, 25.3, 30.1, 17.8};
    std::cout << "mean " << stats::mean(temperatures).value_or(0) << '\n';
    std::cout << "min  " << stats::minimum(temperatures).value_or(0) << '\n';
    std::cout << "max  " << stats::maximum(temperatures).value_or(0) << '\n';
}
