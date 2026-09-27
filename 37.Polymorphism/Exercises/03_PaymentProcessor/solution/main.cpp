#include <iostream>
#include <memory>
#include <string>
#include <vector>

class PaymentMethod {
public:
    virtual ~PaymentMethod() = default;
    virtual bool pay(long long cents) = 0;
    virtual std::string name() const = 0;
};

class CreditCard : public PaymentMethod {
public:
    explicit CreditCard(long long limitCents) : remaining{limitCents} {}
    bool pay(long long cents) override
    {
        if (cents > remaining) return false;
        remaining -= cents;
        return true;
    }
    std::string name() const override { return "Credit card"; }
private:
    long long remaining;
};

class MobileMoney : public PaymentMethod {
public:
    explicit MobileMoney(long long balanceCents) : balance{balanceCents} {}
    bool pay(long long cents) override
    {
        const long long withFee = cents + cents / 100;   // 1% fee
        if (withFee > balance) return false;
        balance -= withFee;
        return true;
    }
    std::string name() const override { return "Mobile money"; }
private:
    long long balance;
};

class GiftCard : public PaymentMethod {
public:
    explicit GiftCard(long long valueCents) : value{valueCents} {}
    bool pay(long long cents) override
    {
        if (used || cents > value) return false;
        used = true;
        return true;
    }
    std::string name() const override { return "Gift card"; }
private:
    long long value;
    bool used{false};
};

// Checkout depends only on the interface: new payment types need ZERO changes here.
class Checkout {
public:
    void process(PaymentMethod& method, long long cents)
    {
        const bool ok = method.pay(cents);
        std::cout << (ok ? "PAID    " : "DECLINED") << "  " << cents / 100 << '.'
                  << (cents % 100 < 10 ? "0" : "") << cents % 100 << " via " << method.name() << '\n';
    }
};

int main()
{
    CreditCard card{50'000};
    MobileMoney momo{10'000};
    GiftCard gift{2'500};

    Checkout checkout;
    checkout.process(card, 45'000);
    checkout.process(card, 10'000);   // over the limit
    checkout.process(momo, 9'900);    // 99.00 + 0.99 fee = 99.99 <= 100.00
    checkout.process(momo, 100);      // not enough left
    checkout.process(gift, 1'999);
    checkout.process(gift, 1);        // single use
}
