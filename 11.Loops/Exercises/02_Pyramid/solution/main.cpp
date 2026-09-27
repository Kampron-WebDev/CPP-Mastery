#include <iostream>
#include <iomanip>

int main()
{
    int n{};
    std::cout << "Height: ";
    std::cin >> n;

    for (int row = 1; row <= n; ++row) {
        for (int s = 0; s < n - row; ++s) std::cout << ' ';
        for (int s = 0; s < 2 * row - 1; ++s) std::cout << '*';
        std::cout << '\n';
    }

    std::cout << '\n';
    for (int row = 1; row <= n; ++row) {
        for (int col = 1; col <= n; ++col)
            std::cout << std::setw(3) << row * col;
        std::cout << '\n';
    }
}
