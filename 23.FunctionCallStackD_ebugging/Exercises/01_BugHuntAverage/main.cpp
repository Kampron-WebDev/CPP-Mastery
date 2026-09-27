// ⭐ Exercise 01: BugHuntAverage
// Expected: "Average: 30"   Actual: something else.
// Put a breakpoint inside the loop, press F5, press F10 repeatedly and watch i and sum.
// There are TWO bugs.
#include <iostream>

double average(const int values[], int count)
{
    int sum = 0;
    for (int i = 1; i <= count; ++i) {
        sum += values[i];
    }
    return sum / count;
}

int main()
{
    int values[]{10, 20, 30, 40, 50};
    std::cout << "Average: " << average(values, 5) << '\n';
}
