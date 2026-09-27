#include <cctype>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int failures{0};
#define CHECK_EQ(actual, expected)                                                                   \
    do {                                                                                             \
        if (!((actual) == (expected))) {                                                             \
            ++failures;                                                                              \
            std::cout << "FAIL line " << __LINE__ << ": " #actual << '\n';                           \
        }                                                                                            \
    } while (false)

std::string toUpper(std::string_view s)
{
    std::string out;
    out.reserve(s.size());
    for (char c : s) out += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return out;
}

bool startsWith(std::string_view s, std::string_view prefix)
{
    return prefix.size() <= s.size() && s.substr(0, prefix.size()) == prefix;
}

std::vector<std::string> split(std::string_view s, char sep)
{
    std::vector<std::string> parts;
    std::size_t start = 0;
    while (true) {
        const auto pos = s.find(sep, start);
        parts.emplace_back(s.substr(start, pos - start));   // pos == npos takes the rest
        if (pos == std::string_view::npos) break;
        start = pos + 1;
    }
    return parts;
}

std::string join(const std::vector<std::string>& parts, std::string_view sep)
{
    std::string out;
    for (std::size_t i = 0; i < parts.size(); ++i) {
        if (i > 0) out += sep;
        out += parts[i];
    }
    return out;
}

int countVowels(std::string_view s)
{
    int count{0};
    for (char c : s) {
        switch (std::tolower(static_cast<unsigned char>(c))) {
            case 'a': case 'e': case 'i': case 'o': case 'u': ++count; break;
            default: break;
        }
    }
    return count;
}

int main()
{
    CHECK_EQ(toUpper("hello"), "HELLO");
    CHECK_EQ(toUpper(""), "");
    CHECK_EQ(toUpper("MiXeD 123!"), "MIXED 123!");

    CHECK_EQ(startsWith("hello", "he"), true);
    CHECK_EQ(startsWith("hello", "hello"), true);
    CHECK_EQ(startsWith("he", "hello"), false);
    CHECK_EQ(startsWith("hello", ""), true);

    CHECK_EQ(split("a,b,c", ','), (std::vector<std::string>{"a", "b", "c"}));
    CHECK_EQ(split("a,,c", ','), (std::vector<std::string>{"a", "", "c"}));
    CHECK_EQ(split("", ','), (std::vector<std::string>{""}));
    CHECK_EQ(split("abc", ','), (std::vector<std::string>{"abc"}));

    CHECK_EQ(join({"a", "b", "c"}, ", "), "a, b, c");
    CHECK_EQ(join({}, ", "), "");
    CHECK_EQ(join({"solo"}, "-"), "solo");
    CHECK_EQ(join(split("x;y;z", ';'), "+"), "x+y+z");

    CHECK_EQ(countVowels("Programming"), 3);
    CHECK_EQ(countVowels("AEIOU aeiou"), 10);
    CHECK_EQ(countVowels("rhythm"), 0);

    std::cout << (failures == 0 ? "ALL TESTS PASS (green)\n" : "some tests fail (red): keep going!\n");
    return failures == 0 ? 0 : 1;
}
