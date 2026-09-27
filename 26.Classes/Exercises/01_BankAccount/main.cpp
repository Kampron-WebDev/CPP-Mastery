// ⭐⭐ Exercise 01: BankAccount
// Design a class BankAccount with:
//   private: owner (std::string), balanceCents (long long)   <- money in whole cents!
//   public:
//     BankAccount(std::string owner, long long initialCents)   (negative initial -> 0)
//     bool deposit(long long cents)     // false if cents <= 0
//     bool withdraw(long long cents)    // false if cents <= 0 or more than the balance
//     long long balance() const
//     const std::string& owner() const   (name the member ownerName to avoid a clash)
//     void print() const                 // "Ada: $12.05"
// INVARIANT: the balance can never go below zero. No function may break that.
// Test: deposit, over-withdraw (must fail), withdraw, print.
#include <iostream>
#include <string>

int main()
{
    // TODO
}
