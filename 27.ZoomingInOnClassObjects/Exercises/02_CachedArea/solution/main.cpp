#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x;
    double y;
};

class Polygon {
public:
    void addPoint(Point p)
    {
        points.push_back(p);
        cacheValid = false;   // shape changed, so the old answer is wrong
    }

    double area() const
    {
        if (!cacheValid) {
            ++computations;
            double sum{0};
            for (std::size_t i = 0; i < points.size(); ++i) {
                const Point& a = points[i];
                const Point& b = points[(i + 1) % points.size()];   // wrap around
                sum += a.x * b.y - b.x * a.y;
            }
            cachedArea = std::abs(sum) / 2.0;
            cacheValid = true;
        }
        return cachedArea;
    }

    int timesComputed() const { return computations; }
    const std::vector<Point>& getPoints() const { return points; }

private:
    std::vector<Point> points;
    mutable bool cacheValid{false};   // mutable: changes don't alter the polygon's observable shape
    mutable double cachedArea{0};
    mutable int computations{0};
};

int main()
{
    Polygon square;
    for (Point p : {Point{0, 0}, Point{4, 0}, Point{4, 4}, Point{0, 4}}) square.addPoint(p);

    const Polygon& view = square;   // const access still works thanks to const area()
    std::cout << view.area() << ' ' << view.area() << ' ' << view.area() << '\n';
    std::cout << "computed " << view.timesComputed() << " time(s)\n";   // 1

    for (const auto& [x, y] : view.getPoints()) std::cout << '(' << x << ", " << y << ") ";
    std::cout << '\n';
}
