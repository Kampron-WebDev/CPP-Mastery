// ⭐⭐⭐ Exercise 02: RefactorTheSmells
// This program is CORRECT but smelly. The tests at the bottom pass. Refactor the code above them so that:
//   - names explain themselves (no x, t, d, f2, tmp)
//   - no magic numbers (named constexpr constants / an enum class for the membership level)
//   - calc() is split into small functions that each do ONE thing
//   - no duplicated code
//   - parameters are passed efficiently and const-correctly
//   - no boolean-flag parameter
// The tests must STILL PASS after every small step. (Adjust only the function names/signatures they call.)
#include <iostream>
#include <string>
#include <vector>

double calc(std::vector<double> d, int t, bool f2)
{
    double x = 0;
    for (int i = 0; i < (int)d.size(); i++) x += d[i];
    if (t == 1) x = x - x * 0.05;
    if (t == 2) x = x - x * 0.10;
    if (t == 3) x = x - x * 0.20;
    if (f2) {
        if (x < 50) x = x + 4.99;
    } else {
        if (x < 50) x = x + 9.99;
    }
    return x;
}

int failures{0};
void check(bool ok, const char* what)
{
    if (!ok) { ++failures; std::cout << "FAIL: " << what << '\n'; }
}
bool near(double a, double b) { return a - b < 1e-9 && b - a < 1e-9; }

int main()
{
    check(near(calc({10, 20}, 0, false), 39.99), "no membership, standard shipping");
    check(near(calc({10, 20}, 0, true), 34.99), "no membership, express flag");
    check(near(calc({100}, 1, false), 95.0), "silver, free shipping over 50");
    check(near(calc({30, 30}, 2, false), 54.0), "gold 10%");
    check(near(calc({50}, 3, true), 44.99), "platinum 20% drops below 50 -> shipping added");
    check(near(calc({}, 0, false), 9.99), "empty cart still pays shipping");
    std::cout << (failures == 0 ? "all tests pass\n" : "tests FAILED\n");
    return failures;
}
