#include <iostream>
#include <memory>
#include <vector>

class Animal {
public:
    virtual void speak() const { std::cout << "...\n"; }
    virtual ~Animal() { std::cout << "Animal gone\n"; }   // BUG 1: destructor must be virtual
};

class Cat : public Animal {
public:
    void speak() const override { std::cout << "Meow\n"; }   // BUG 2: missing const, so it didn't override
    ~Cat() override { std::cout << "Cat gone\n"; }
};

class Dog : public Animal {
public:
    void speak() const override { std::cout << "Woof\n"; }
    ~Dog() override { std::cout << "Dog gone\n"; }
};

void makeItSpeak(const Animal& a) { a.speak(); }   // BUG 3: by value SLICED the object

int main()
{
    std::vector<std::unique_ptr<Animal>> zoo;
    zoo.push_back(std::make_unique<Cat>());
    zoo.push_back(std::make_unique<Dog>());
    for (const auto& a : zoo) makeItSpeak(*a);
}
