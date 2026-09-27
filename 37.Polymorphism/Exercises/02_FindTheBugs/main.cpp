// ⭐⭐ Exercise 02: FindTheBugs
// Expected output:
//   Meow
//   Woof
//   Cat gone
//   Animal gone
//   Dog gone
//   Animal gone
// There are THREE classic polymorphism bugs below. Find and fix them.
#include <iostream>
#include <memory>
#include <vector>

class Animal {
public:
    virtual void speak() const { std::cout << "...\n"; }
    ~Animal() { std::cout << "Animal gone\n"; }
};

class Cat : public Animal {
public:
    void speak() { std::cout << "Meow\n"; }
    ~Cat() { std::cout << "Cat gone\n"; }
};

class Dog : public Animal {
public:
    void speak() const override { std::cout << "Woof\n"; }
    ~Dog() { std::cout << "Dog gone\n"; }
};

void makeItSpeak(Animal a) { a.speak(); }

int main()
{
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Cat>());
    zoo.push_back(std::make_unique<Dog>());
    for (const auto& a : zoo) makeItSpeak(*a);
}
