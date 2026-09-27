#include <iostream>

int main()
{
    double prices[]{1.5, 2.25, 10.0};
    for (double& p : prices) {      // & : p is the real element, not a copy
        p *= 2;
    }
    for (const double& p : prices) std::cout << p << ' ';   // read-only, no copy
    std::cout << '\n';
}
