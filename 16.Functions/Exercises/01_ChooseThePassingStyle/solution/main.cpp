#include <iostream>
#include <string>
#include <vector>

// Read-only big object -> const reference: no copy, can't modify by accident.
void printName(const std::string& name) { std::cout << name << '\n'; }
// Must change the caller's string -> reference.
void addExclamation(std::string& text) { text += '!'; }
// Small, read-only -> by value (copying an int is free).
int square(int n) { return n * n; }
// A vector can be huge -> const reference.
double total(const std::vector<double>& prices)
{
    double t{};
    for (double p : prices) t += p;
    return t;
}
// Must change the caller's int -> reference.
void resetScore(int& score) { score = 0; }

int main()
{
    std::string name{"Grace"};
    printName(name);
    addExclamation(name);
    printName(name);
    std::cout << square(7) << '\n';
    std::vector<double> cart{1.5, 2.0, 3.25};
    std::cout << total(cart) << '\n';
    int score{99};
    resetScore(score);
    std::cout << score << '\n';
}
