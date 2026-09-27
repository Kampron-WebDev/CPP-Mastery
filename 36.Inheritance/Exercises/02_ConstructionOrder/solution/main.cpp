#include <iostream>

struct Engine {
    Engine() { std::cout << "Engine built\n"; }
    ~Engine() { std::cout << "Engine scrapped\n"; }
};

struct Vehicle {
    Vehicle() { std::cout << "Vehicle built\n"; }
    ~Vehicle() { std::cout << "Vehicle scrapped\n"; }
};

struct Car : Vehicle {
    Engine engine;
    Car() { std::cout << "Car built\n"; }
    ~Car() { std::cout << "Car scrapped\n"; }
};

int main()
{
    Car c;
    std::cout << "--- driving ---\n";
}
// Output:
//   Vehicle built      <- 1. base class first
//   Engine built       <- 2. then members (in declaration order)
//   Car built          <- 3. then the constructor body
//   --- driving ---
//   Car scrapped       <- destruction is the exact reverse
//   Engine scrapped
//   Vehicle scrapped
