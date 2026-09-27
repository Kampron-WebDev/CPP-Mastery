#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Monster {
public:
    explicit Monster(std::string name) : name{std::move(name)} { std::cout << this->name << " created\n"; }
    ~Monster() { std::cout << name << " destroyed\n"; }
    const std::string& getName() const { return name; }
private:
    std::string name;
};

// Factory: creates and hands ownership to the caller.
std::unique_ptr<Monster> createMonster(const std::string& name) { return std::make_unique<Monster>(name); }

// Only uses the monster: a plain reference. No ownership involved.
void fight(const Monster& m) { std::cout << "Fighting " << m.getName() << '\n'; }

// Takes ownership: the monster dies when this function ends.
void adopt(std::unique_ptr<Monster> m) { std::cout << "Adopted " << m->getName() << '\n'; }

int main()
{
    auto goblin = createMonster("Goblin");
    auto troll = createMonster("Troll");
    fight(*goblin);
    adopt(std::move(troll));          // troll is now empty; the Troll is destroyed inside adopt
    auto dragon = createMonster("Dragon");
    fight(*dragon);
}   // Dragon and Goblin destroyed automatically (the original code leaked the Dragon!)
