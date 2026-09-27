#include <iostream>

double average(const int values[], int count)
{
    int sum = 0;
    // Bug 1: loop started at 1 and went to count (skipped values[0], read past the end)
    for (int i = 0; i < count; ++i) {
        sum += values[i];
    }
    // Bug 2: integer division threw away the fraction (hidden here because 150/5 is exact;
    // try values that average 30.5 to see it)
    return static_cast<double>(sum) / count;
}

int main()
{
    int values[]{10, 20, 30, 40, 50};
    std::cout << "Average: " << average(values, 5) << '\n';
}
