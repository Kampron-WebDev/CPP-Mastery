#include "geometry.h"
#include <numbers>   // C++20: std::numbers::pi

double circleArea(double radius) { return std::numbers::pi * radius * radius; }
double rectangleArea(double width, double height) { return width * height; }
double triangleArea(double base, double height) { return 0.5 * base * height; }
