#include <iostream>
#include <string>
#include <utility>

class Tracker {
public:
    explicit Tracker(std::string name) : name{std::move(name)} { std::cout << "+ " << this->name << " born\n"; }
    ~Tracker() { std::cout << "- " << name << " dies\n"; }

private:
    std::string name;
};

int main()
{
    Tracker a{"a"};           // + a
    {
        Tracker b{"b"};       // + b
        Tracker c{"c"};       // + c
    }                         // - c, - b   (reverse order!)
    Tracker* d = new Tracker{"d"};   // + d
    Tracker e{"e"};           // + e
    delete d;                 // - d   (heap objects die when YOU delete them)
}                             // - e, - a
// Without "delete d": "- d dies" never prints. The object leaks.
