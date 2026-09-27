// ⭐ Exercise 02: BiggestOfThree
// Read three whole numbers and print the biggest one.
//   Input : 4 19 7
//   Output: Biggest: 19
// Think: what if two numbers are equal? What if all are negative?
//
// Step 1: write your pseudocode here as comments.
// Ask for 3 whole numbers
// Compare and find the biggest
// Print out the biggest
// Step 2: write the code.
#include <iostream>

int main()
{
    // TODO

    int num1{}, num2{}, num3{};
    int biggest{};

    std::cout << "Enter 3 whole numbers, separate them with a space: ";
    std::cin >> num1 >> num2 >> num3;

   
    biggest = num1;

    if(num2 > num1) biggest = num2;
    if(num3 > num2) biggest = num3;

    std::cout << "The biggest number is " << biggest << '\n';


    return 0;
}
