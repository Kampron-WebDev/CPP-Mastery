#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

// Rule of Zero: std::string and std::vector already copy, move and clean up correctly,
// so the compiler-generated special members are exactly right. ~40 risky lines deleted.
class Player {
public:
    Player(std::string n, int rounds) : name{std::move(n)}, scores(static_cast<std::size_t>(rounds), 0) {}

    void setScore(int round, int value) { scores.at(static_cast<std::size_t>(round)) = value;  }   // at(): bounds-checked
    int total() const { return std::accumulate(scores.begin(), scores.end(), 0); }
    const std::string& getName() const { return name; }

private:
    std::string name;
    std::vector<int> scores;
};

int main()
{
    Player a{"Ama", 3};
    a.setScore(0, 10);
    a.setScore(1, 20);
    Player b = a;
    b.setScore(2, 5);
    Player c = std::move(b);
    std::cout << a.getName() << ' ' << a.total() << '\n';
    std::cout << c.getName() << ' ' << c.total() << '\n';
}
