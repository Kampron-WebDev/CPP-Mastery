// ⭐⭐⭐ Exercise 01: OptimizeThis
// This program finds the words that appear in BOTH texts and counts them. It's correct but SLOW.
// Use the "Build & Run this folder (Optimized -O2)" task.
// 1. Time it (it prints its own time).
// 2. Find at least FIVE performance problems (write them as comments).
// 3. Fix them one at a time, measuring after each. Output must stay the same.
// Target: at least 20x faster.
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> makeWords(int count, int seed)
{
    std::vector<std::string> words;
    unsigned x = static_cast<unsigned>(seed);
    for (int i = 0; i < count; ++i) {
        x = x * 1103515245u + 12345u;
        words.push_back("w" + std::to_string(x % 20000));
    }
    return words;
}

bool contains(std::vector<std::string> list, std::string word)
{
    for (auto item : list)
        if (item == word) return true;
    return false;
}

int main()
{
    const auto start = std::chrono::steady_clock::now();
    std::vector<std::string> a = makeWords(20000, 1);
    std::vector<std::string> b = makeWords(20000, 2);

    std::vector<std::string> common;
    for (auto word : a)
        if (contains(b, word) && !contains(common, word)) common.push_back(word);

    std::sort(common.begin(), common.end());
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
    std::cout << common.size() << " common words, first: " << (common.empty() ? "-" : common.front())
              << ", time " << ms.count() << " ms\n";
}
