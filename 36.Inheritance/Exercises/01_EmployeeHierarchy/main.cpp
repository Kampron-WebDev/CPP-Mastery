// ⭐⭐ Exercise 01: EmployeeHierarchy
// class Person   { protected: std::string name; int age; public: Person(name, age); void introduce() const; }
// class Employee : public Person { std::string company; double salary; ... raise(double percent) }
// class Manager  : public Employee { int teamSize; ... }
// - Each constructor passes the right values to its base's constructor.
// - introduce() in Person prints "I'm <name>, <age>".
// - Employee and Manager each have describe() that calls the base part too
//   (e.g. Manager::describe() calls Employee::describe() then adds "manages N people").
// - Validation: salary can't be negative, teamSize can't be negative.
#include <iostream>
#include <string>

int main()
{
    // TODO
}
