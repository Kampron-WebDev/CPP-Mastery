#include <iostream>
#include <string>

template <typename T>
T largest(const T arr[], int size)
{
    T best = arr[0];
    for (int i = 1; i < size; ++i)
        if (arr[i] > best) best = arr[i];
    return best;
}

template <typename T>
void swapValues(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
int countEqual(const T arr[], int size, const T& value)
{
    int count{0};
    for (int i = 0; i < size; ++i)
        if (arr[i] == value) ++count;
    return count;
}

template <typename T>
T clampValue(const T& v, const T& lo, const T& hi)
{
    if (v < lo) return lo;
    if (hi < v) return hi;
    return v;
}

template <int N>
int sumFixed(const int (&arr)[N])   // reference to an array of exactly N ints
{
    int total{0};
    for (int x : arr) total += x;
    return total;
}

int main()
{
    int ints[]{3, 9, 2, 9};
    double doubles[]{1.5, -2.0, 7.25};
    std::string words[]{"pear", "apple", "zebra", "apple"};

    std::cout << largest(ints, 4) << ' ' << largest(doubles, 3) << ' ' << largest(words, 4) << '\n';
    std::cout << countEqual(ints, 4, 9) << ' ' << countEqual(words, 4, std::string{"apple"}) << '\n';

    std::string a{"left"}, b{"right"};
    swapValues(a, b);
    std::cout << a << ' ' << b << '\n';

    std::cout << clampValue(15, 0, 10) << ' ' << clampValue(0.5, 1.0, 2.0) << ' '
              << clampValue(std::string{"m"}, std::string{"a"}, std::string{"k"}) << '\n';

    std::cout << "sumFixed: " << sumFixed(ints) << '\n';   // N = 4 deduced
}
