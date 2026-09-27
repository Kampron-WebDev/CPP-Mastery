#include <iostream>
#include <compare>
#include <string>

class Money {
public:
    explicit Money(long long cents = 0) : cents{cents} {}
    static Money fromDollars(long long dollars, int cents = 0) { return Money{dollars * 100 + cents}; }

    long long inCents() const { return cents; }

    Money& operator+=(const Money& o) { cents += o.cents; return *this; }
    Money& operator-=(const Money& o) { cents -= o.cents; return *this; }
    friend Money operator+(Money a, const Money& b) { return a += b; }
    friend Money operator-(Money a, const Money& b) { return a -= b; }
    friend Money operator*(const Money& m, long long k) { return Money{m.cents * k}; }
    friend Money operator*(long long k, const Money& m) { return m * k; }
    friend Money operator/(const Money& m, long long k) { return Money{m.cents / k}; }
    // No operator*(Money, Money): "dollars squared" makes no sense, so it won't compile.

    friend bool operator==(const Money&, const Money&) = default;
    friend auto operator<=>(const Money&, const Money&) = default;   // gives < <= > >=

    friend std::ostream& operator<<(std::ostream& os, const Money& m)
    {
        long long c = m.cents;
        if (c < 0) {
            os << '-';
            c = -c;
        }
        std::string dollars = std::to_string(c / 100);
        for (int i = static_cast<int>(dollars.size()) - 3; i > 0; i -= 3) dollars.insert(i, ",");
        const long long rest = c % 100;
        return os << '$' << dollars << '.' << (rest < 10 ? "0" : "") << rest;
    }

private:
    long long cents;
};

int main()
{
    const Money price = Money::fromDollars(19, 99);
    Money bill = price * 3;
    std::cout << "3 items:       " << bill << '\n';          // $59.97
    bill -= Money::fromDollars(10);
    std::cout << "after discount: " << bill << '\n';         // $49.97
    std::cout << "each of 3 pays: " << bill / 3 << '\n';     // $16.65
    std::cout << "big:           " << Money::fromDollars(1234567, 5) << '\n';   // $1,234,567.05
    std::cout << "negative:      " << Money{-350} << '\n';   // -$3.50
    std::cout << std::boolalpha << "price < bill? " << (price < bill) << '\n';
    // auto nonsense = price * price;   // error: no match for operator*
}
