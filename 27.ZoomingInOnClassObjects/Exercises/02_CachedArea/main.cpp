// ⭐⭐⭐ Exercise 02: CachedArea
// Class Polygon stores points (struct Point { double x, y; }) in a std::vector.
//   void addPoint(Point p)
//   double area() const   <- expensive, so CACHE the result:
//        mutable bool cacheValid{false}; mutable double cachedArea{0};
//        addPoint must invalidate the cache.
//   Area formula (shoelace): 0.5 * |sum over i of (x_i * y_{i+1} - x_{i+1} * y_i)|  (wrap around at the end)
// Count how many times the area is actually computed (another mutable counter).
// Then loop over the points with   for (const auto& [x, y] : points)   to print them.
#include <iostream>
#include <vector>

int main()
{
    // TODO: square (0,0) (4,0) (4,4) (0,4) -> area 16; call area() 3 times -> computed once
}
