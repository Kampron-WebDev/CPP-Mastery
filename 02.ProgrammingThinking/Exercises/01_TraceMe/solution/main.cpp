#include <iostream>

// Trace table:
//        a   b   c
// start  3   4   -
// c=a+b  3   4   7
// a=c-1  6   4   7
// b=a*2  6  12   7
// c=...  6  12  25   (7 + 6 + 12)
int main()
{
    int a = 3;
    int b = 4;
    int c = a + b;
    a = c - 1;
    b = a * 2;
    c = c + a + b;

    int myA = 6, myB = 12, myC = 25;

    std::cout << "a: real " << a << " / you " << myA << '\n';
    std::cout << "b: real " << b << " / you " << myB << '\n';
    std::cout << "c: real " << c << " / you " << myC << '\n';
}
