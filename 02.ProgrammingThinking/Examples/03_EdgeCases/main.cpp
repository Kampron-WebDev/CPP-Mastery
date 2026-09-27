// Splitting a bill: the "happy path" is easy. The edge cases are where the thinking is.
#include <iostream>

int main()
{
    double bill{};
    int friends{};

    std::cout << "Bill amount: ";
    std::cin >> bill;
    std::cout << "Number of friends: ";
    std::cin >> friends;

    // Edge case 1: the user typed letters, so cin failed
    if (!std::cin) {
        std::cout << "That was not a number.\n";
        return 1;
    }
    // Edge case 2: zero or negative friends. Dividing by 0 is a disaster.
    if (friends <= 0) {
        std::cout << "You need at least one friend to split a bill!\n";
        return 1;
    }
    // Edge case 3: negative bill
    if (bill < 0) {
        std::cout << "A bill can't be negative.\n";
        return 1;
    }

    std::cout << "Each person pays: " << bill / friends << '\n';
}
