#include "stats.h"

double square(double x) { return x * x; }       // should be private to this file

double average(double a, double b)
{
    ++callCount;
    return (a + b) / 2;
}
