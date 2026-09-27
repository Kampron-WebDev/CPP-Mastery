// ⭐⭐⭐ Exercise 04: CoinChange
// A shop owes a customer some change, in cents (e.g. 289 = $2.89).
// Coins available: 100, 50, 25, 10, 5, 1 cents.
// Print how many of each coin to give so the TOTAL NUMBER of coins is as small as possible.
//   Input : 289
//   Output:
//     100c x 2
//     50c  x 1
//     25c  x 1
//     10c  x 1
//     5c   x 0
//     1c   x 4
// First solve 289 BY HAND and write down what you did. That IS the algorithm.
// Divide 289 / 100 -> 2
// Divide  (289 % 100) / 50 -> 1
// Divide  ((289 % 100) % 50 ) / 25 -> 1
// Divide  (((289 % 100) % 50) % 25 ) / 10 -> 1
// Divide  ((((289 % 100) % 50) % 25 ) % 10) / 5 -> 0
// Divide  ((((289 % 100) % 50) % 25 ) % 10) % 5 -> 4
#include <iostream> 
#include <iomanip>

int main()
{
    // TODO

    int change{};

    std::cout << "Enter the change: ";
    std::cin >> change;

    if (change < 0) {
        std::cout << "Change can't be negative.\n";
        return 1;
    }



int hundred = change / 100;
int fifty = (change % 100) / 50;
int twenty_five = ((change % 100) % 50 ) / 25;
int ten = (((change % 100) % 50) % 25 ) / 10;
int five = ((((change % 100) % 50) % 25 ) % 10) / 5;
int one = ((((change % 100) % 50) % 25 ) % 10) % 5;

std::cout << std::left;
std::cout << std::setw(5) << "100c" << " x " << hundred << std::endl;
std::cout << std::setw(5) << "50c" << " x " << fifty << std::endl;
std::cout << std::setw(5) << "25c" << " x " << twenty_five << std::endl;
std::cout << std::setw(5) << "10c" << " x " << ten << std::endl;
std::cout << std::setw(5) << "5c" << " x " << five << std::endl;
std::cout << std::setw(5) << "1c" << " x " << one << std::endl;




}
