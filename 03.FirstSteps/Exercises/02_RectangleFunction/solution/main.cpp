#include <iostream>

int area(int width, int height)
{
    return width * height;
}

int perimeter(int width, int height)
{
    return 2 * (width + height);
}

int main()
{
    int width{}, height{};
    std::cout << "Width and height: ";
    std::cin >> width >> height;

    std::cout << "Area: " << area(width, height)
              << ", Perimeter: " << perimeter(width, height) << '\n';
}
