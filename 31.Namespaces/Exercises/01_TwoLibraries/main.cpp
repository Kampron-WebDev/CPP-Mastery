// ⭐⭐ Exercise 01: TwoLibraries
// Imagine two libraries both define   double convert(double)  and  std::string_view unitName():
//   Metric:   convert inches -> centimetres (x 2.54), unitName "cm"
//   Imperial: convert centimetres -> inches (/ 2.54), unitName "in"
// 1. Put each in a nested namespace:  Units::Metric  and  Units::Imperial
// 2. Put a helper  double round2(double)  (round to 2 decimals) in an ANONYMOUS namespace
//    and use it in both.
// 3. In main create an alias  namespace UM = Units::Metric;  and call everything.
// 4. Explain in a comment why "using namespace Units::Metric; using namespace Units::Imperial;"
//    followed by convert(10) fails.
#include <iostream>
#include <string_view>

int main()
{
    // TODO
}
