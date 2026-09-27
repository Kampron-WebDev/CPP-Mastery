#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>

class BankError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;   // inherit the (message) constructor
};

class InsufficientFunds : public BankError {
public:
    InsufficientFunds(long long requested, long long available)
        : BankError{"insufficient funds: requested " + std::to_string(requested) + ", available " +
                    std::to_string(available)},
          requested{requested}, available{available}
    {
    }
    long long requested;
    long long available;
};

class AccountLocked : public BankError {
public:
    explicit AccountLocked(const std::string& owner) : BankError{"account of " + owner + " is locked"} {}
};

class InvalidAmount : public BankError {
public:
    InvalidAmount() : BankError{"amount must be positive"} {}
};

class Account {
public:
    Account(std::string owner, long long balance) : owner{std::move(owner)}, balance{balance} {}

    void deposit(long long amount)
    {
        check(amount);
        balance += amount;
    }

    void withdraw(long long amount)
    {
        check(amount);
        if (amount > balance) throw InsufficientFunds{amount, balance};
        balance -= amount;
    }

    void lock() { locked = true; }
    long long getBalance() const { return balance; }
    const std::string& getOwner() const { return owner; }

private:
    void check(long long amount) const
    {
        if (locked) throw AccountLocked{owner};
        if (amount <= 0) throw InvalidAmount{};
    }

    std::string owner;
    long long balance;
    bool locked{false};
};

// Strong guarantee: if deposit fails after withdraw succeeded, undo the withdraw.
void transfer(Account& from, Account& to, long long amount)
{
    from.withdraw(amount);          // if this throws, nothing has changed yet
    try {
        to.deposit(amount);
    } catch (...) {
        from.deposit(amount);       // roll back (can't fail: from isn't locked and amount > 0)
        throw;                      // rethrow the ORIGINAL exception
    }
}

void attempt(const std::string& label, Account& a, Account& b, long long amount)
{
    try {
        transfer(a, b, amount);
        std::cout << label << ": ok\n";
    } catch (const InsufficientFunds& e) {
        std::cout << label << ": " << e.what() << " (short by " << e.requested - e.available << ")\n";
    } catch (const BankError& e) {
        std::cout << label << ": bank error: " << e.what() << '\n';
    } catch (const std::exception& e) {
        std::cout << label << ": unexpected: " << e.what() << '\n';
    }
    std::cout << "   balances: " << a.getOwner() << '=' << a.getBalance() << ", " << b.getOwner() << '='
              << b.getBalance() << '\n';
}

int main()
{
    Account ama{"Ama", 1000};
    Account kofi{"Kofi", 500};
    attempt("normal transfer", ama, kofi, 300);
    attempt("too much", ama, kofi, 5000);
    attempt("negative", ama, kofi, -5);
    kofi.lock();
    attempt("into locked account", ama, kofi, 100);   // balances must be unchanged
}
