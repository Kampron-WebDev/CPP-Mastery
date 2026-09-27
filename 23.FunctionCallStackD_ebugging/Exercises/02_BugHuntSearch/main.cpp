// ⭐⭐ Exercise 02: BugHuntSearch
// findFirstNegative should return the index of the first negative number, or -1.
// Expected output: 3  -1  0
// Use WATCH on data[i] and the CALL STACK panel to see which call misbehaves.
#include <iostream>

int findFirstNegative(const int data[], int size)
{
    int result = -1;
    for (int i = 0; i < size; ++i) {
        if (data[i] < 0) {
            result = i;
        }
    }
    return result;
}

int main()
{
    int a[]{4, 8, 1, -5, 7, -2};
    int b[]{1, 2, 3};
    int c[]{-9, -8, -7};
    std::cout << findFirstNegative(a, 6) << "  " << findFirstNegative(b, 3) << "  "
              << findFirstNegative(c, 3) << '\n';
}
