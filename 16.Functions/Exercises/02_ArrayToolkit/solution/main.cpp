#include <iostream>
#include <iterator>

int sum(const int arr[], int size)
{
    int total{0};
    for (int i = 0; i < size; ++i) total += arr[i];
    return total;
}

int indexOfMax(const int arr[], int size)
{
    if (size <= 0) return -1;
    int best{0};
    for (int i = 1; i < size; ++i)
        if (arr[i] > arr[best]) best = i;
    return best;
}

bool contains(const int arr[], int size, int value)
{
    for (int i = 0; i < size; ++i)
        if (arr[i] == value) return true;
    return false;
}

// Not const: fill's whole job is to modify the array.
void fill(int arr[], int size, int value = 0)
{
    for (int i = 0; i < size; ++i) arr[i] = value;
}

void print(const int arr[], int size)
{
    std::cout << '[';
    for (int i = 0; i < size; ++i) std::cout << (i ? ", " : "") << arr[i];
    std::cout << "]\n";
}

int main()
{
    int data[]{4, 8, 15, 16, 23, 42};
    const int n = static_cast<int>(std::size(data));

    print(data, n);
    std::cout << "sum = " << sum(data, n) << '\n';
    std::cout << "max at index " << indexOfMax(data, n) << '\n';
    std::cout << std::boolalpha << "contains 15? " << contains(data, n, 15)
              << ", contains 7? " << contains(data, n, 7) << '\n';
    fill(data, n, 9);
    print(data, n);
    fill(data, n);   // default value 0
    print(data, n);
}
