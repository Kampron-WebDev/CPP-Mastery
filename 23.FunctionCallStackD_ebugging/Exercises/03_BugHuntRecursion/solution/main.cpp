#include <iostream>
#include <string_view>

// Bug: the base case `size() == 1` returned 0 WITHOUT checking the last character,
// and an empty string would recurse forever (s.substr(1) on "" throws / never shrinks).
// Fix: the base case is the EMPTY string.
int countOccurrences(std::string_view s, char c)
{
    if (s.empty()) return 0;
    const int here = (s[0] == c) ? 1 : 0;
    return here + countOccurrences(s.substr(1), c);
}

int main()
{
    std::cout << countOccurrences("banana", 'a') << '\n';   // 3
    std::cout << countOccurrences("", 'a') << '\n';         // 0
}
