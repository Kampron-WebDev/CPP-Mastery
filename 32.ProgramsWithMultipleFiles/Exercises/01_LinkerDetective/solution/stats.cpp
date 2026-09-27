#include "stats.h"

namespace {
    // Anonymous namespace: internal linkage, invisible to other .cpp files.
    [[maybe_unused]] double square(double x) { return x * x; }
}

double average(double a, double b)
{
    ++callCount;
    return (a + b) / 2;
}
