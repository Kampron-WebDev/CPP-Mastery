#include <iostream>
#include <string>
#include <sstream>

int main()
{
    const std::string text{"the cat sat on the mat with the hat"};

    // istringstream splits on whitespace: the simplest robust word splitter.
    std::istringstream stream{text};
    std::string word, longest, replaced;
    int words{0}, theCount{0};
    while (stream >> word) {
        ++words;
        if (word == "the") ++theCount;          // whole-word match, so "there" doesn't count
        if (word.size() > longest.size()) longest = word;
        if (!replaced.empty()) replaced += ' ';
        replaced += (word == "the") ? "a" : word;
    }

    std::cout << "Words: " << words << "\n\"the\" appears: " << theCount
              << "\nLongest: " << longest << "\nReplaced: " << replaced << '\n';

    // The find() way, for comparison: counts substrings (would also match inside "there")
    int raw{0};
    for (auto pos = text.find("the"); pos != std::string::npos; pos = text.find("the", pos + 1)) ++raw;
    std::cout << "(substring count via find: " << raw << ")\n";
}
