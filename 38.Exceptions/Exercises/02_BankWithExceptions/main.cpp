// ⭐⭐⭐ Exercise 02: BankWithExceptions
// Create an exception hierarchy:
//   class BankError : public std::runtime_error          (base for all bank problems)
//   class InsufficientFunds : public BankError           (stores requested and available amounts)
//   class AccountLocked : public BankError
//   class InvalidAmount : public BankError
// class Account with deposit/withdraw/lock that THROW these.
// transfer(from, to, amount) must give the STRONG guarantee: if the withdraw or the deposit
// fails, both balances are exactly as before.
// In main, trigger each error, catch specific ones first, then BankError, then std::exception.
#include <iostream>
#include <stdexcept>
#include <string>

int main()
{
    // TODO
}
