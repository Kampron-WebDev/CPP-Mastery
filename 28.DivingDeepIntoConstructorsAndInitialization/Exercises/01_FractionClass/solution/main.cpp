#include <iostream>
#include <numeric>   // std::gcd

class Fraction {
public:
    Fraction() : Fraction(0, 1) {}
    explicit Fraction(int whole) : Fraction(whole, 1) {}
    Fraction(int numerator, int denominator) : num{numerator}, den{denominator}
    {
        if (den == 0) {
            std::cout << "warning: denominator 0 replaced by 1\n";
            den = 1;
        }
        if (den < 0) {   // keep the sign on the numerator
            num = -num;
            den = -den;
        }
        const int g = std::gcd(num, den);   // gcd is never 0 here because den >= 1
        num /= g;
        den /= g;
    }

    void print() const { std::cout << num << '/' << den << '\n'; }
    double toDouble() const { return static_cast<double>(num) / den; }

    Fraction plus(const Fraction& other) const
    {
        return Fraction{num * other.den + other.num * den, den * other.den};   // constructor reduces it
    }

private:
    int num;
    int den;
};

int main()
{
    Fraction{6, 8}.print();     // 3/4
    Fraction{3, -9}.print();    // -1/3
    Fraction{5, 0}.print();     // warning, 5/1
    Fraction{}.print();         // 0/1
    Fraction{7}.print();        // 7/1
    Fraction{1, 2}.plus(Fraction{1, 3}).print();   // 5/6
    std::cout << Fraction{1, 4}.toDouble() << '\n';
    // Fraction f = 7;          // error thanks to explicit: no sneaky int -> Fraction
}
