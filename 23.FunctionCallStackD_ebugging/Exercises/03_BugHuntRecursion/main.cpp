// ⭐⭐ Exercise 03: BugHuntRecursion
// countOccurrences("banana", 'a') should return 3. It returns something else.
// Set a breakpoint on the first line of the function. Each time it stops, look at the
// CALL STACK panel: one frame per call. Click the frames and compare their `s` values.
#include <iostream>
#include <string_view>

int countOccurrences(std::string_view s, char c)
{
    if (s.size() == 1) return 0;
    int here = (s[0] == c) ? 1 : 0;
    return here + countOccurrences(s.substr(1), c);
}

int main()
{
    std::cout << countOccurrences("banana", 'a') << '\n';   // expected 3
    // std::cout << countOccurrences("", 'a') << '\n';      // expected 0: what happens now?
}
