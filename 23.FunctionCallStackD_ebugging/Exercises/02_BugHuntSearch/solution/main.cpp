#include <iostream>

// Bug: the loop kept going after finding a negative, so it returned the LAST one.
// Fix: return immediately on the first match.
int findFirstNegative(const int data[], int size)
{
    for (int i = 0; i < size; ++i) {
        if (data[i] < 0) return i;
    }
    return -1;
}

int main()
{
    int a[]{4, 8, 1, -5, 7, -2};
    int b[]{1, 2, 3};
    int c[]{-9, -8, -7};
    std::cout << findFirstNegative(a, 6) << "  " << findFirstNegative(b, 3) << "  "
              << findFirstNegative(c, 3) << '\n';
}
