// ⭐⭐ Exercise 01: LinkerDetective
// This folder has main.cpp, stats.h and stats.cpp. The build FAILS AT LINK TIME.
// Read the linker errors carefully and fix the design (not by merging everything into one file!).
// Goals:
//   - stats.h can be included by many .cpp files safely
//   - callCount is ONE shared counter for the whole program
//   - the helper square() stays private to stats.cpp
#include <iostream>
#include "stats.h"

int main()
{
    std::cout << average(2, 4) << '\n';
    std::cout << average(10, 20) << '\n';
    std::cout << "calls: " << callCount << '\n';
    std::cout << version() << '\n';
}
