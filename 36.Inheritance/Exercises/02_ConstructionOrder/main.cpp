// ⭐ Exercise 02: ConstructionOrder
// PREDICT the output (write it below) BEFORE running.
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
    Engine engine;   // a member
    Car() { std::cout << "Car built\n"; }
    ~Car() { std::cout << "Car scrapped\n"; }
};

int main()
{
    Car c;
    std::cout << "--- driving ---\n";
}
// Your prediction:
//
