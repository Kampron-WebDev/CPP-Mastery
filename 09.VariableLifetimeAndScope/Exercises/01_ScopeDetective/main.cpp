// ⭐ Exercise 01: ScopeDetective
// Predict EVERY printed value (write it in the comment), then run.
#include <iostream>

int value{100};

int main()
{
    std::cout << value << '\n';         // prediction:
    int value{5};
    std::cout << value << '\n';         // prediction:
    {
        int value{7};
        std::cout << value << '\n';     // prediction:
        std::cout << ::value << '\n';   // prediction:
        value += 1;
    }
    std::cout << value << '\n';         // prediction:
    for (int i = 0; i < 2; ++i) {
        int temp{i * 10};
        value += temp;
    }
    std::cout << value << '\n';         // prediction:
    // std::cout << temp;               // Why would this line fail? Answer:
}
