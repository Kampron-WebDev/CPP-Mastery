#include <iostream>

int moves{0};

void hanoi(int n, char from, char to, char via)
{
    if (n == 0) return;                   // base case: nothing to move
    hanoi(n - 1, from, via, to);          // 1) clear the way: n-1 disks onto the spare peg
    std::cout << "Move disk " << n << " from " << from << " to " << to << '\n';
    ++moves;                              // 2) move the biggest disk
    hanoi(n - 1, via, to, from);          // 3) put the n-1 disks back on top of it
}

int main()
{
    hanoi(3, 'A', 'C', 'B');
    std::cout << "Moves for 3 disks: " << moves << '\n';   // 7
    // Formula: 2^n - 1. For n = 10: 1023 moves. For 64 disks: longer than the age of the universe!
}
