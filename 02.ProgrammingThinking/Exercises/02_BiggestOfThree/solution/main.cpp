#include <iostream>

// Pseudocode:
//   read a, b, c
//   biggest <- a
//   if b > biggest: biggest <- b
//   if c > biggest: biggest <- c
//   print biggest
// This "keep the best so far" pattern works for 3 numbers or 3 million.
int main()
{
    int a{}, b{}, c{};
    std::cout << "Enter three numbers: ";
    std::cin >> a >> b >> c;

    int biggest = a;
    if (b > biggest) biggest = b;
    if (c > biggest) biggest = c;

    std::cout << "Biggest: " << biggest << '\n';
}
