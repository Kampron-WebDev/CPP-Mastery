#include <iostream>
#include <iterator>

// Old style: outputs hidden among the parameters
void stats(const int arr[], int size, int& min, int& max, double& avg)
{
    min = max = arr[0];
    long long sum{0};
    for (int i = 0; i < size; ++i) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
        sum += arr[i];
    }
    avg = static_cast<double>(sum) / size;
}

// Modern: one clear return value
struct Stats {
    int min;
    int max;
    double average;
};

Stats computeStats(const int arr[], int size)
{
    Stats s{};
    stats(arr, size, s.min, s.max, s.average);   // reuse the logic
    return s;
}

int main()
{
    int data[]{12, 5, 30, 7, 19};
    const int n = static_cast<int>(std::size(data));

    int lo1{}, hi1{};
    double avg1{};
    stats(data, n, lo1, hi1, avg1);
    std::cout << "v1: " << lo1 << ' ' << hi1 << ' ' << avg1 << '\n';

    auto [lo, hi, avg] = computeStats(data, n);   // structured binding: clear and compact
    std::cout << "v2: " << lo << ' ' << hi << ' ' << avg << '\n';
}
