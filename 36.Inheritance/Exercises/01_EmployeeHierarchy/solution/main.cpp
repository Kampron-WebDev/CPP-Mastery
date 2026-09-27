#include <iostream>
#include <string>
#include <utility>

class Person {
public:
    Person(std::string name, int age) : name{std::move(name)}, age{age} {}
    void introduce() const { std::cout << "I'm " << name << ", " << age << '\n'; }

protected:
    std::string name;
    int age;
};

class Employee : public Person {
public:
    Employee(std::string name, int age, std::string company, double salary)
        : Person{std::move(name), age}, company{std::move(company)}, salary{salary < 0 ? 0 : salary}
    {
    }

    void raise(double percent)
    {
        if (percent > 0) salary *= 1.0 + percent / 100.0;
    }

    void describe() const
    {
        introduce();
        std::cout << "  works at " << company << " earning " << salary << '\n';
    }

private:
    std::string company;
    double salary;
};

class Manager : public Employee {
public:
    Manager(std::string name, int age, std::string company, double salary, int teamSize)
        : Employee{std::move(name), age, std::move(company), salary}, teamSize{teamSize < 0 ? 0 : teamSize}
    {
    }

    void describe() const   // hides Employee::describe, then reuses it explicitly
    {
        Employee::describe();
        std::cout << "  manages " << teamSize << " people\n";
    }

private:
    int teamSize;
};

int main()
{
    Employee dev{"Kwame", 28, "Acme", 5000};
    dev.raise(10);
    dev.describe();

    Manager boss{"Ama", 41, "Acme", 9000, 7};
    boss.describe();
}
