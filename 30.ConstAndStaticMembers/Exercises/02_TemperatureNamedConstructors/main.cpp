// ⭐⭐ Exercise 02: TemperatureNamedConstructors
// "Temperature t{30};" is ambiguous: Celsius? Fahrenheit? Kelvin?
// Design class Temperature that stores KELVIN internally, with:
//   - a PRIVATE constructor Temperature(double kelvin)
//   - public static "named constructors":
//       static Temperature fromCelsius(double c);
//       static Temperature fromFahrenheit(double f);
//       static Temperature fromKelvin(double k);
//   - static constexpr double absoluteZero{0.0};   values below it are clamped to it
//   - getters celsius(), fahrenheit(), kelvin()
// Now  Temperature::fromCelsius(30)  is impossible to misread.
#include <iostream>

int main()
{
    // TODO
}
