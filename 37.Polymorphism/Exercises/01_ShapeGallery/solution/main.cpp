#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <cmath>
#include <numbers>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;
};

class Circle : public Shape {
public:
    explicit Circle(double r) : r{r} {}
    double area() const override { return std::numbers::pi * r * r; }
    double perimeter() const override { return 2 * std::numbers::pi * r; }
    std::string name() const override { return "Circle"; }
private:
    double r;
};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : w{w}, h{h} {}
    double area() const override { return w * h; }
    double perimeter() const override { return 2 * (w + h); }
    std::string name() const override { return "Rectangle"; }
private:
    double w, h;
};

class Square final : public Rectangle {   // new shape: no printing code changed (Open/Closed)
public:
    explicit Square(double side) : Rectangle{side, side} {}
    std::string name() const override { return "Square"; }
};

class Triangle : public Shape {
public:
    Triangle(double a, double b, double c) : a{a}, b{b}, c{c} {}
    double area() const override
    {
        const double s = perimeter() / 2;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }
    double perimeter() const override { return a + b + c; }
    std::string name() const override { return "Triangle"; }
private:
    double a, b, c;
};

int main()
{
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(1.0));
    shapes.push_back(std::make_unique<Rectangle>(2.0, 5.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0));
    shapes.push_back(std::make_unique<Square>(4.0));

    double total{0};
    const Shape* biggest = nullptr;
    for (const auto& s : shapes) {
        std::cout << s->name() << ": area " << s->area() << ", perimeter " << s->perimeter() << '\n';
        total += s->area();
        if (!biggest || s->area() > biggest->area()) biggest = s.get();   // .get(): non-owning raw pointer
    }
    std::cout << "Total area: " << total << '\n';
    std::cout << "Biggest: " << biggest->name() << '\n';
}
