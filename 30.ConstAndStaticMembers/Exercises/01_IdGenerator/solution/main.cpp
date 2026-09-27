#include <iostream>
#include <string>
#include <utility>

class Employee {
public:
    struct Address {
        std::string city;
    };

    static constexpr std::size_t maxNameLength{20};

    Employee(const std::string& name, Address address)
        : id{nextId++}, name{name.substr(0, maxNameLength)}, address{std::move(address)}
    {
        ++alive;
    }
    Employee(const Employee& other) : id{nextId++}, name{other.name}, address{other.address}
    {
        ++alive;   // copies are new employees too (with a new id)
    }
    Employee& operator=(const Employee&) = delete;
    ~Employee() { --alive; }

    static int aliveCount() { return alive; }
    void print() const { std::cout << '#' << id << ' ' << name << " (" << address.city << ")\n"; }

private:
    inline static int nextId{1};
    inline static int alive{0};

    int id;
    std::string name;
    Address address;
};

int main()
{
    Employee a{"Ada", {"London"}};
    Employee b{"Grace Brewster Murray Hopper, Rear Admiral", {"New York"}};   // name gets cut
    Employee c{"Linus", {"Helsinki"}};
    a.print();
    b.print();
    c.print();
    std::cout << "alive: " << Employee::aliveCount() << '\n';   // 3
    {
        Employee temp{"Temp", {"Accra"}};
        temp.print();
        std::cout << "alive inside block: " << Employee::aliveCount() << '\n';   // 4
    }
    std::cout << "alive after block: " << Employee::aliveCount() << '\n';        // 3
}
