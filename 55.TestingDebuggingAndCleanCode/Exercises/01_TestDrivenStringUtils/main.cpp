// ⭐⭐ Exercise 01: TestDrivenStringUtils
// The TESTS are already written (bottom of the file). The functions are stubs, so tests FAIL (red).
// Implement the functions ONE AT A TIME until every test passes (green). Then tidy up (refactor).
// Don't change the tests! (In real TDD you'd write them first yourself.)
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

// ---- implement these ----
std::string toUpper(std::string_view s) { return std::string{s}; }                     // TODO
bool startsWith(std::string_view s, std::string_view prefix) { (void)s; (void)prefix; return false; }   // TODO (don't use starts_with!)
std::vector<std::string> split(std::string_view s, char sep) { (void)s; (void)sep; return {}; }   // TODO
std::string join(const std::vector<std::string>& parts, std::string_view sep) { (void)parts; (void)sep; return ""; }   // TODO
int countVowels(std::string_view s) { (void)s; return -1; }                            // TODO

// ---- the tests ----
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
