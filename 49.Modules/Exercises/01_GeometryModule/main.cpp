// ⭐⭐ Exercise 01: GeometryModule
// Turn a small geometry library into a MODULE named  geometry  in this folder:
//   geometry-shapes.ixx : export module geometry:shapes;   (partition)
//                         export struct Circle { double r; };  export struct Rect { double w, h; };
//   geometry.ixx        : export module geometry;
//                         export import :shapes;             (re-export the partition)
//                         export double area(const Circle&); export double area(const Rect&);
//                         a NON-exported helper  double square(double)  used by area(Circle)
// Then here in main.cpp:  import geometry;  and print the areas.
// Prove the helper is hidden: calling square(2.0) from main must NOT compile.
// For now this file prints a reminder so the folder builds before you start.
#include <iostream>

int main()
{
    std::cout << "Create geometry.ixx and geometry-shapes.ixx, then replace this with import geometry;\n";
}
