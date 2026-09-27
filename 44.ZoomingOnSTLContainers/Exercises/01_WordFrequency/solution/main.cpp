#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
    const std::string text =
        "The quick brown fox jumps over the lazy dog. The dog sleeps; the fox runs! "
        "A quick fox is a happy fox, and a lazy dog is a sleepy dog.";

    // Normalise: lowercase letters, everything else becomes a space
    std::string clean;
    for (char ch : text) {
        const auto c = static_cast<unsigned char>(ch);
        clean += std::isalpha(c) ? static_cast<char>(std::tolower(c)) : ' ';
    }

    std::unordered_map<std::string, int> counts;
    std::istringstream words{clean};
    for (std::string w; words >> w;) ++counts[w];   // [] inserts 0 the first time, which is exactly what we want here

    std::cout << "Different words: " << counts.size() << '\n';

    std::vector<std::pair<std::string, int>> sorted(counts.begin(), counts.end());
    std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;   // most frequent first
        return a.first < b.first;                               // tie: alphabetical
    });

    for (std::size_t i = 0; i < 5 && i < sorted.size(); ++i)
        std::cout << sorted[i].first << ": " << sorted[i].second << '\n';
}
