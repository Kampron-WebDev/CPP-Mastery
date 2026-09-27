#include <iostream>
#include <iterator>

int main()
{
    int values[]{3, 1, 4, 1, 5, 9, 2, 6};
    int* begin = values;
    int* end = values + std::size(values);   // "one past the last": never dereferenced

    for (int* p = begin; p != end; ++p) std::cout << *p << ' ';
    std::cout << '\n';

    for (int* p = end; p != begin;) {
        --p;                                  // step back first, then read
        std::cout << *p << ' ';
    }
    std::cout << '\n';

    int sum{0};
    for (int* p = begin; p != end; ++p) sum += *p;
    std::cout << "Sum: " << sum << '\n';

    for (int* p = begin; p != end; ++p) {
        if (*p > 4) {
            std::cout << "First > 4 is " << *p << " at index " << (p - begin) << '\n';
            break;
        }
    }
    // This begin/end pattern is EXACTLY how STL iterators work (Lesson 43).
}
