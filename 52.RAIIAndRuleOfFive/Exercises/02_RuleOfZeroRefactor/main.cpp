// ⭐⭐ Exercise 02: RuleOfZeroRefactor
// This class works, but it manages memory by hand with a full Rule of Five (lots of code, lots of risk).
// Refactor it to the RULE OF ZERO:
//   - replace char* name with std::string
//   - replace int* scores + count with std::vector<int>
//   - DELETE the destructor, copy/move constructors and assignments completely
// main() must still work and print the same results.
#include <cstring>
#include <iostream>
#include <utility>

class Player {
public:
    Player(const char* n, int count) : name{new char[std::strlen(n) + 1]}, scores{new int[count]{}}, count{count}
    {
        std::strcpy(name, n);
    }
    ~Player() { delete[] name; delete[] scores; }
    Player(const Player& o) : name{new char[std::strlen(o.name) + 1]}, scores{new int[o.count]}, count{o.count}
    {
        std::strcpy(name, o.name);
        for (int i = 0; i < count; ++i) scores[i] = o.scores[i];
    }
    Player(Player&& o) noexcept
        : name{std::exchange(o.name, nullptr)}, scores{std::exchange(o.scores, nullptr)}, count{std::exchange(o.count, 0)} {}
    Player& operator=(Player o) noexcept
    {
        std::swap(name, o.name);
        std::swap(scores, o.scores);
        std::swap(count, o.count);
        return *this;
    }

    void setScore(int round, int value) { scores[round] = value; }
    int total() const { int t = 0; for (int i = 0; i < count; ++i) t += scores[i]; return t; }
    const char* getName() const { return name; }

private:
    char* name;
    int* scores;
    int count;
};

int main()
{
    Player a{"Ama", 3};
    a.setScore(0, 10);
    a.setScore(1, 20);
    Player b = a;           // copy
    b.setScore(2, 5);
    Player c = std::move(b);
    std::cout << a.getName() << ' ' << a.total() << '\n';   // Ama 30
    std::cout << c.getName() << ' ' << c.total() << '\n';   // Ama 35
}
