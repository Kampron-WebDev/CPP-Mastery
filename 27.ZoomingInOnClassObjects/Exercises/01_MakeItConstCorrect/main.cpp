// ⭐⭐ Exercise 01: MakeItConstCorrect
// This code does not compile, because printReport takes a const reference but Student's
// functions are not const. Fix it by adding const in ALL the right places (and only there).
// Also: which parameters should be const references instead of copies?
#include <iostream>
#include <string>
#include <vector>

class Student {
public:
    Student(std::string name, std::vector<int> grades) : name{name}, grades{grades} {}

    std::string getName() { return name; }
    double average()
    {
        double sum{0};
        for (int g : grades) sum += g;
        return grades.empty() ? 0.0 : sum / grades.size();
    }
    void addGrade(int g) { grades.push_back(g); }

private:
    std::string name;
    std::vector<int> grades;
};

void printReport(const Student& s)
{
    // std::cout << s.getName() << ": " << s.average() << '\n';   // uncomment: fails until fixed
    (void)s;
}

int main()
{
    Student ada{"Ada", {90, 85, 100}};
    ada.addGrade(95);
    printReport(ada);
}
