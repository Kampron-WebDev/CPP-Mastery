import <iostream>;
import geometry;

int main()
{
    std::cout << "circle r=2 : " << area(Circle{2.0}) << '\n';
    std::cout << "rect 3x4   : " << area(Rect{3.0, 4.0}) << '\n';
    // std::cout << square(2.0);   // error: 'square' was not declared (it isn't exported)
}
