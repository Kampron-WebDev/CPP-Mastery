#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

// Problems found:
//  1. contains() took the vector BY VALUE: a full copy of 20 000 strings on EVERY call.
//  2. contains() took the word by value (another copy).
//  3. `for (auto item : list)` copied every string again while searching.
//  4. Linear search inside a loop = O(n*m): 20 000 x 20 000 = 400 million comparisons.
//  5. `!contains(common, word)`: another linear search, growing as `common` grows.
//  6. `for (auto word : a)` copied each word; makeWords didn't reserve.
// Fix: hash sets (O(1) lookup) + no copies. O(n + m) overall.

std::vector<std::string> makeWords(int count, int seed)
{
    std::vector<std::string> words;
    words.reserve(static_cast<std::size_t>(count));
    unsigned x = static_cast<unsigned>(seed);
    for (int i = 0; i < count; ++i) {
        x = x * 1103515245u + 12345u;
        words.push_back("w" + std::to_string(x % 20000));
    }
    return words;
}

int main()
{
    const auto start = std::chrono::steady_clock::now();
    const std::vector<std::string> a = makeWords(20000, 1);
    const std::vector<std::string> b = makeWords(20000, 2);

    const std::unordered_set<std::string> inB(b.begin(), b.end());   // O(1) average lookups
    std::unordered_set<std::string> seen;
    std::vector<std::string> common;
    for (const auto& word : a)
        if (inB.contains(word) && seen.insert(word).second) common.push_back(word);   // insert().second == "was new"

    std::sort(common.begin(), common.end());
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start);
    std::cout << common.size() << " common words, first: " << (common.empty() ? "-" : common.front())
              << ", time " << ms.count() << " ms\n";
}
