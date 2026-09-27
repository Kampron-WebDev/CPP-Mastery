#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void print(const std::vector<std::string>& words)
{
    for (const auto& w : words) std::cout << w << ' ';
    std::cout << '\n';
}

int main()
{
    std::vector<std::string> words{"pear", "fig", "banana", "kiwi", "apple", "date", "cherry"};

    std::sort(words.begin(), words.end());
    print(words);

    std::sort(words.begin(), words.end(),
              [](const std::string& a, const std::string& b) { return a.size() < b.size(); });
    print(words);

    std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b;   // tie-breaker
    });
    print(words);

    std::sort(words.begin(), words.end(),
              [](const std::string& a, const std::string& b) { return a.back() < b.back(); });
    print(words);

    std::size_t minLength{};
    std::cout << "Count words longer than: ";
    std::cin >> minLength;
    const auto count = std::count_if(words.begin(), words.end(),
                                     [minLength](const std::string& w) { return w.size() > minLength; });
    std::cout << count << " words\n";
}
