// ⭐ Exercise 01: TraceMe
// DO NOT RUN THIS YET.
// 1. On paper, make a trace table with columns: a, b, c
// 2. Write down the final values of a, b and c.
// 3. Put your predictions in the variables below, THEN run.
#include <iostream>

int main()
{
    int a = 3;
    int b = 4;
    int c = a + b;   // ? 7
    a = c - 1;       // ? 6
    b = a * 2;       // ? 12
    c = c + a + b;   // ? 25

    int myA = 6, myB = 12, myC = 25;   // TODO: your predictions

    std::cout << "a: real " << a << " / you " << myA << '\n';
    std::cout << "b: real " << b << " / you " << myB << '\n';
    std::cout << "c: real " << c << " / you " << myC << '\n';
}
