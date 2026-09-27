#pragma once

// inline: ONE variable for the whole program, even though every .cpp sees this definition.
// (Alternative: `extern int callCount;` here + `int callCount{0};` in stats.cpp.)
inline int callCount{0};

double average(double a, double b);

// inline: allowed to be defined in a header that many .cpp files include.
inline const char* version() { return "stats 1.0"; }
