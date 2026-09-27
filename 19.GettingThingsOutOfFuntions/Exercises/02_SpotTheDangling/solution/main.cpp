#include <iostream>
#include <string>

// A: DANGLING, since x is a local. Fix: return by value.
int getA() { int x{5}; return x; }
// B: SAFE, because it refers to the caller's variable, which outlives the call.
int& getB(int& x) { return x; }
// C: SAFE. String literals live for the whole program (static storage).
const char* getC() { return "hello"; }
// D: DANGLING, since s is a local. Fix: return std::string by value (RVO makes it cheap).
std::string getD() { std::string s{"hi"}; return s; }
// E: DANGLING, since arr is a local array. Fix: return a value type, e.g. the first element,
//    or better a std::array / std::vector by value.
int getE() { int arr[3]{1, 2, 3}; return arr[0]; }

int main()
{
    int value{10};
    std::cout << getA() << ' ' << getB(value) << ' ' << getC() << ' ' << getD() << ' ' << getE() << '\n';
}
