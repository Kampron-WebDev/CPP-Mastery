#include <iostream>
#include <algorithm>
#include <cctype>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int score;
    int age;
};

int main()
{
    std::vector<Student> students{{"Ama", 88, 19}, {"Kofi", 45, 17}, {"Esi", 88, 20},
                                  {"Yaw", 67, 16}, {"Akua", 92, 18}, {"Kwame", 31, 22}};

    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        if (a.score != b.score) return a.score > b.score;
        return a.name < b.name;
    });
    int rank{1};
    for (const auto& s : students) std::cout << rank++ << ". " << s.name << " " << s.score << '\n';

    if (auto it = std::find_if(students.begin(), students.end(), [](const Student& s) { return s.age < 18; });
        it != students.end())
        std::cout << "First under 18 (in ranking order): " << it->name << '\n';

    std::vector<Student> passed;
    std::copy_if(students.begin(), students.end(), std::back_inserter(passed),
                 [](const Student& s) { return s.score >= 50; });
    std::cout << "Passed: " << passed.size() << '\n';

    const double average = std::accumulate(students.begin(), students.end(), 0.0,
                                           [](double total, const Student& s) { return total + s.score; }) /
                           static_cast<double>(students.size());
    std::cout << "Average: " << average << '\n';

    std::cout << std::boolalpha << "All at least 15? "
              << std::all_of(students.begin(), students.end(), [](const Student& s) { return s.age >= 15; }) << '\n';

    std::vector<std::string> upper;
    std::transform(students.begin(), students.end(), std::back_inserter(upper), [](const Student& s) {
        std::string n = s.name;
        std::transform(n.begin(), n.end(), n.begin(), [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
        return n;
    });
    for (const auto& n : upper) std::cout << n << ' ';
    std::cout << '\n';
}
