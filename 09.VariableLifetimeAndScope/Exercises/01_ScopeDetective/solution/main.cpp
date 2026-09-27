#include <iostream>

int value{100};

int main()
{
    std::cout << value << '\n';         // 100 (only the global exists yet)
    int value{5};
    std::cout << value << '\n';         // 5   (local shadows global)
    {
        int value{7};
        std::cout << value << '\n';     // 7   (innermost wins)
        std::cout << ::value << '\n';   // 100 (:: = global)
        value += 1;                     // changes the inner one only
    }
    std::cout << value << '\n';         // 5   (inner one is gone)
    for (int i = 0; i < 2; ++i) {
        int temp{i * 10};
        value += temp;                  // +0, then +10
    }
    std::cout << value << '\n';         // 15
    // std::cout << temp;               // temp only exists inside the for loop's body
}
