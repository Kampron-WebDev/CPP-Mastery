#include <iostream>
#include <string>
#include <utility>
#include <vector>

class Student {
public:
    // Take by value + std::move: one copy at most (the "sink parameter" idiom).
    Student(std::string name, std::vector<int> grades) : name{std::move(name)}, grades{std::move(grades)} {}

    const std::string& getName() const { return name; }   // const: only reads
    double average() const                                 // const: only reads
    {
        double sum{0};
        for (int g : grades) sum += g;
        return grades.empty() ? 0.0 : sum / static_cast<double>(grades.size());
    }
    void addGrade(int g) { grades.push_back(g); }          // NOT const: it modifies

private:
    std::string name;
    std::vector<int> grades;
};

void printReport(const Student& s)
{
    std::cout << s.getName() << ": " << s.average() << '\n';
}

int main()
{
    Student ada{"Ada", {90, 85, 100}};
    ada.addGrade(95);
    printReport(ada);
}
