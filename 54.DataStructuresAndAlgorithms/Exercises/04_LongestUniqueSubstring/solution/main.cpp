#include <array>
#include <iostream>
#include <string>
#include <string_view>

// Sliding window, O(n) time, O(1) memory (256 possible chars).
std::string_view longestUnique(std::string_view s)
{
    std::array<int, 256> lastSeen;
    lastSeen.fill(-1);
    std::size_t bestStart = 0, bestLength = 0, left = 0;
    for (std::size_t right = 0; right < s.size(); ++right) {
        const auto c = static_cast<unsigned char>(s[right]);
        // If c repeats INSIDE the current window, jump left past its previous position.
        // (The >= check matters: in "abba" the old 'a' is already outside the window.)
        if (lastSeen[c] >= static_cast<int>(left)) left = static_cast<std::size_t>(lastSeen[c]) + 1;
        lastSeen[c] = static_cast<int>(right);
        if (right - left + 1 > bestLength) {
            bestLength = right - left + 1;
            bestStart = left;
        }
    }
    return s.substr(bestStart, bestLength);
}

int main()
{
    for (std::string_view t : {"abcabcbb", "bbbbb", "pwwkew", "", "dvdf", "abba"}) {
        const auto best = longestUnique(t);
        std::cout << '"' << t << "\" -> " << best.size() << " (\"" << best << "\")\n";
    }
    // Brute force: all O(n²) substrings, each checked in O(n) → O(n³). The window is O(n).
}
