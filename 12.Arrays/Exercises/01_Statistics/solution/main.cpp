#include <iostream>
#include <iterator>

int main()
{
    double temps[]{21.5, 19.0, 25.3, 30.1, 17.8, 22.4, 28.9};
    const auto count = std::size(temps);

    double minT = temps[0], maxT = temps[0], sum = 0.0;
    for (double t : temps) {
        if (t < minT) minT = t;
        if (t > maxT) maxT = t;
        sum += t;
    }
    const double average = sum / count;

    int aboveAverage{0};
    for (double t : temps)
        if (t > average) ++aboveAverage;

    std::cout << "Count: " << count << "\nMin: " << minT << "\nMax: " << maxT
              << "\nAverage: " << average << "\nDays above average: " << aboveAverage << '\n';
}
