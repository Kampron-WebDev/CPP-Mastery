#pragma once

class Rectangle {
public:
    Rectangle(double width, double height);

    double area() const;
    double perimeter() const;
    bool isSquare() const;
    Rectangle& scale(double factor);   // returns *this so calls can be chained

private:
    double width;
    double height;
};
