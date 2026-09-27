// ⭐ Exercise 01: ChooseThePassingStyle
// Each function below has "???" instead of a parameter type. Choose the BEST of:
//   by value, by reference, by const reference
// and write a comment explaining why. Then uncomment and make it compile and run.
#include <iostream>
#include <string>
#include <vector>

// void printName(??? name)            { std::cout << name << '\n'; }
// void addExclamation(??? text)       { text += '!'; }
// int  square(??? n)                  { return n * n; }
// double total(??? prices)            { double t{}; for (double p : prices) t += p; return t; }
// void resetScore(??? score)          { score = 0; }

int main()
{
    // std::string name{"Grace"};
    // printName(name);
    // addExclamation(name);  printName(name);          // Grace!
    // std::cout << square(7) << '\n';                    // 49
    // std::vector<double> cart{1.5, 2.0, 3.25};
    // std::cout << total(cart) << '\n';                  // 6.75
    // int score{99}; resetScore(score); std::cout << score << '\n';   // 0
}
