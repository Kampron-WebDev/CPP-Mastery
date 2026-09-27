#include <iostream>

class Temperature {
public:
    static constexpr double absoluteZero{0.0};

    static Temperature fromKelvin(double k) { return Temperature{k}; }
    static Temperature fromCelsius(double c) { return Temperature{c + 273.15}; }
    static Temperature fromFahrenheit(double f) { return Temperature{(f - 32.0) * 5.0 / 9.0 + 273.15}; }

    double kelvin() const { return k; }
    double celsius() const { return k - 273.15; }
    double fahrenheit() const { return celsius() * 9.0 / 5.0 + 32.0; }

private:
    explicit Temperature(double kelvin) : k{kelvin < absoluteZero ? absoluteZero : kelvin} {}
    double k;
};

int main()
{
    const auto body = Temperature::fromCelsius(37);
    const auto oven = Temperature::fromFahrenheit(350);
    const auto impossible = Temperature::fromKelvin(-50);   // clamped to absolute zero

    std::cout << "body: " << body.celsius() << " C = " << body.fahrenheit() << " F\n";
    std::cout << "oven: " << oven.celsius() << " C\n";
    std::cout << "impossible: " << impossible.kelvin() << " K\n";
    // Temperature t{30};   // error: the constructor is private, which forces clear intent
}
