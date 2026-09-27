#include <iostream>
#include <optional>
#include <string_view>
#include <limits>

std::optional<int> parseInt(std::string_view text)
{
    if (text.empty()) return std::nullopt;

    bool negative = false;
    std::size_t i = 0;
    if (text[0] == '-') {
        negative = true;
        i = 1;
        if (text.size() == 1) return std::nullopt;   // just "-"
    }

    long long value{0};   // bigger type so we can detect overflow
    for (; i < text.size(); ++i) {
        const char c = text[i];
        if (c < '0' || c > '9') return std::nullopt;
        value = value * 10 + (c - '0');
        if (value > static_cast<long long>(std::numeric_limits<int>::max()) + 1) return std::nullopt;
    }
    if (negative) value = -value;
    if (value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min())
        return std::nullopt;
    return static_cast<int>(value);
}

int main()
{
    for (std::string_view t : {"42", "-7", "0", "", "abc", "12x", "-", "3.5", "2147483647", "2147483648"}) {
        const auto result = parseInt(t);
        std::cout << '"' << t << "\" -> ";
        if (result) std::cout << *result << '\n';
        else        std::cout << "invalid\n";
    }
}
