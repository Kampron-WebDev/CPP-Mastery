// assert (run time, debug builds) and static_assert (compile time).
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

static_assert(sizeof(std::int32_t) == 4, "int32_t must be 4 bytes");   // checked by the compiler

double average(const std::vector<int>& values)
{
    // Precondition: callers must never pass an empty vector. If they do, it's a BUG in the caller.
    assert(!values.empty() && "average() needs at least one value");
    long long sum{0};
    for (int v : values) sum += v;
    return static_cast<double>(sum) / static_cast<double>(values.size());
}

int main()
{
    std::cout << average({1, 2, 3, 4}) << '\n';
    std::cout << "Now calling average({}), which should stop with an assertion failure:\n";
    std::cout.flush();
    std::cout << average({}) << '\n';   // assertion fails here and prints file + line
    // Rebuild with -DNDEBUG (release) and the assert disappears: never rely on it for real input checks!
}
