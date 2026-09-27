// ⭐⭐ Exercise 01: RemoveTheNews
// This code has a LEAK (find it!) and uses raw new/delete.
// Rewrite it with std::unique_ptr and std::make_unique so that:
//   - there is not a single `new` or `delete` left
//   - createMonster is a factory returning std::unique_ptr<Monster>
//   - fight() only USES a monster (what should its parameter type be?)
//   - adopt() takes OWNERSHIP of a monster
// Every "created" line must have a matching "destroyed" line in the output.
#include <iostream>
#include <string>

class Monster {
public:
    explicit Monster(std::string name) : name{name} { std::cout << name << " created\n"; }
    ~Monster() { std::cout << name << " destroyed\n"; }
    const std::string& getName() const { return name; }
private:
    std::string name;
};

Monster* createMonster(const std::string& name) { return new Monster{name}; }

void fight(Monster* m) { std::cout << "Fighting " << m->getName() << '\n'; }

void adopt(Monster* m)
{
    std::cout << "Adopted " << m->getName() << '\n';
    delete m;
}

int main()
{
    Monster* goblin = createMonster("Goblin");
    Monster* troll = createMonster("Troll");
    fight(goblin);
    adopt(troll);
    Monster* dragon = createMonster("Dragon");
    fight(dragon);
    delete goblin;
}
