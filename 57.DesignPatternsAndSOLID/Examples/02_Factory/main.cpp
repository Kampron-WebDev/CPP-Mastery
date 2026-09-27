// Factory + registry: create objects by name. Adding a new type = registering it; no factory code changes.
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <numbers>
#include <string>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};
class Circle : public Shape {
public:
    double area() const override { return std::numbers::pi; }   // unit circle
};
class Square : public Shape {
public:
    double area() const override { return 1.0; }                // unit square
};

class ShapeFactory {
public:
    using Creator = std::function<std::unique_ptr<Shape>()>;

    void registerType(const std::string& name, Creator creator) { creators[name] = std::move(creator); }

    std::unique_ptr<Shape> create(const std::string& name) const
    {
        const auto it = creators.find(name);
        return it != creators.end() ? it->second() : nullptr;   // nullptr for unknown names
    }

private:
    std::map<std::string, Creator> creators;
};

int main()
{
    ShapeFactory factory;
    factory.registerType("circle", [] { return std::make_unique<Circle>(); });
    factory.registerType("square", [] { return std::make_unique<Square>(); });

    for (const std::string name : {"circle", "square", "hexagon"}) {
        if (auto shape = factory.create(name)) std::cout << name << " area " << shape->area() << '\n';
        else std::cout << name << ": unknown shape\n";
    }
}
