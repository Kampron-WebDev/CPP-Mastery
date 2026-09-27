// ⭐⭐ Exercise 02: SpotTheDangling
// Three of these five functions are BROKEN (they return something that dies).
// For each one write SAFE or DANGLING and why. Then fix the broken ones
// (usually: just return by value). Only then uncomment the calls in main.
#include <iostream>
#include <string>

// A
int& getA() { int x{5}; return x; }
// B
int& getB(int& x) { return x; }
// C
const char* getC() { return "hello"; }
// D
std::string& getD() { std::string s{"hi"}; return s; }
// E
int* getE() { int arr[3]{1, 2, 3}; return arr; }

int main()
{
    // std::cout << getA() << getB(...) << getC() << getD() << *getE();
}
