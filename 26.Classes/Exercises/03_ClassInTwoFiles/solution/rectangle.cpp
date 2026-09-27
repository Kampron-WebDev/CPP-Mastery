#include "rectangle.h"

Rectangle::Rectangle(double width, double height)
    : width{width > 0 ? width : 1.0}, height{height > 0 ? height : 1.0}
{
}

double Rectangle::area() const { return width * height; }
double Rectangle::perimeter() const { return 2 * (width + height); }
bool Rectangle::isSquare() const { return width == height; }

Rectangle& Rectangle::scale(double factor)
{
    if (factor > 0) {
        width *= factor;
        height *= factor;
    }
    return *this;
}
