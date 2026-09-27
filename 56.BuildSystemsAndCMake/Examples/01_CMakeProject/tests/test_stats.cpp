#include <stats/stats.h>

#include <iostream>
#include <vector>

int failures = 0;
void check(bool ok, const char* what)
{
    if (!ok) {
        ++failures;
        std::cerr << "FAIL: " << what << '\n';
    }
}

int main()
{
    const std::vector<double> v{1, 2, 3, 4};
    check(stats::mean(v) == 2.5, "mean of 1..4 is 2.5");
    check(stats::minimum(v) == 1.0, "minimum");
    check(stats::maximum(v) == 4.0, "maximum");
    check(!stats::mean(std::vector<double>{}).has_value(), "mean of empty has no value");
    std::cout << (failures == 0 ? "all tests passed\n" : "tests failed\n");
    return failures;   // CTest: 0 = pass
}
