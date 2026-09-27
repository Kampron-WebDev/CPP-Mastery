// A tiny unit-test framework in ~40 lines, to understand what GoogleTest/Catch2 do for you.
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// ---------------- the "framework" ----------------
struct TestCase {
    std::string name;
    std::function<void()> body;
};
std::vector<TestCase>& registry()
{
    static std::vector<TestCase> tests;
    return tests;
}
int failures{0};

struct Registrar {
    Registrar(std::string name, std::function<void()> body) { registry().push_back({std::move(name), std::move(body)}); }
};

#define TEST(name)                                        \
    void name();                                          \
    static Registrar registrar_##name{#name, name};       \
    void name()

#define CHECK_EQ(actual, expected)                                                                          \
    do {                                                                                                    \
        const auto a_ = (actual);                                                                           \
        const auto e_ = (expected);                                                                         \
        if (!(a_ == e_)) {                                                                                  \
            ++failures;                                                                                     \
            std::cout << "    FAIL " << __FILE__ << ':' << __LINE__ << ": " #actual " returned " << a_           \
                      << ", expected " << e_ << '\n';                                                       \
        }                                                                                                   \
    } while (false)

int runAllTests()
{
    for (const auto& t : registry()) {
        const int before = failures;
        t.body();
        std::cout << (failures == before ? "[ PASS ] " : "[ FAIL ] ") << t.name << '\n';
    }
    std::cout << '\n' << registry().size() << " tests, " << failures << " failed checks\n";
    return failures == 0 ? 0 : 1;   // non-zero exit code = CI pipeline turns red
}

// ---------------- code under test ----------------
int clamp(int value, int lo, int hi) { return value < lo ? lo : (value > hi ? hi : value); }

std::string repeat(const std::string& s, int times)
{
    std::string out;
    for (int i = 0; i < times; ++i) out += s;
    return out;
}

// ---------------- tests: Arrange, Act, Assert ----------------
TEST(clamp_inside_range_returns_value) { CHECK_EQ(clamp(5, 0, 10), 5); }
TEST(clamp_below_returns_low) { CHECK_EQ(clamp(-3, 0, 10), 0); }
TEST(clamp_above_returns_high) { CHECK_EQ(clamp(42, 0, 10), 10); }
TEST(clamp_on_the_edges) {
    CHECK_EQ(clamp(0, 0, 10), 0);
    CHECK_EQ(clamp(10, 0, 10), 10);
}
TEST(repeat_basic) { CHECK_EQ(repeat("ab", 3), std::string{"ababab"}); }
TEST(repeat_zero_and_negative_give_empty) {
    CHECK_EQ(repeat("ab", 0), std::string{});
    CHECK_EQ(repeat("ab", -2), std::string{});
}
TEST(this_one_fails_on_purpose_to_show_the_output) { CHECK_EQ(clamp(7, 0, 5), 7); }

int main() { return runAllTests(); }
