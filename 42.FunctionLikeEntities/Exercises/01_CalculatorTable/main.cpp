// ⭐⭐ Exercise 01: CalculatorTable
// Replace a big switch statement with a TABLE of operations:
//   std::map<char, std::function<double(double, double)>> ops;   (map: Lesson 44, it's a lookup table)
//   ops['+'] = a normal function;  ops['-'] = a lambda;  ops['*'] = std::multiplies<>{};
//   ops['^'] = a lambda using std::pow;  ops['/'] = a lambda that throws on division by zero
// Read "a op b" lines until the user types q, look the operator up and call it.
// Adding a new operator should be ONE line of code.
#include <iostream>
#include <functional>
#include <map>

int main()
{
    // TODO
}
