#include <iostream>
#include <iterator>

void swapValues(int* a, int* b)
{
    if (a == nullptr || b == nullptr) return;   // null safety
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minMax(const int* arr, int size, int* outMin, int* outMax)
{
    if (arr == nullptr || outMin == nullptr || outMax == nullptr || size <= 0) return;
    *outMin = *outMax = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < *outMin) *outMin = arr[i];
        if (arr[i] > *outMax) *outMax = arr[i];
    }
}

int main()
{
    int x{3}, y{8};
    swapValues(&x, &y);
    std::cout << x << ' ' << y << '\n';

    int data[]{7, -2, 15, 4, 0};
    int lo{}, hi{};
    minMax(data, static_cast<int>(std::size(data)), &lo, &hi);
    std::cout << "min " << lo << ", max " << hi << '\n';
}
