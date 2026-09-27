#include <iostream>
#include <string_view>
#include <cmath>

namespace {
    double round2(double x) { return std::round(x * 100.0) / 100.0; }   // file-private helper
}

namespace Units::Metric {
    double convert(double inches) { return round2(inches * 2.54); }
    std::string_view unitName() { return "cm"; }
}

namespace Units::Imperial {
    double convert(double centimetres) { return round2(centimetres / 2.54); }
    std::string_view unitName() { return "in"; }
}

int main()
{
    namespace UM = Units::Metric;
    namespace UI = Units::Imperial;

    std::cout << "10 in = " << UM::convert(10) << ' ' << UM::unitName() << '\n';
    std::cout << "30 cm = " << UI::convert(30) << ' ' << UI::unitName() << '\n';

    // With both using-directives active, convert(10) is AMBIGUOUS: the compiler sees two
    // equally good convert(double) functions and refuses to guess.
}
