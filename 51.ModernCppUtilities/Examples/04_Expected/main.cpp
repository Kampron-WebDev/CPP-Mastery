// std::expected<T, E> (C++23): either a value, or an error explaining why not.
// BUILD WITH: Ctrl+Shift+P -> "Tasks: Run Task" -> "C++: Build & Run this folder (C++23)"
#include <charconv>
#include <expected>
#include <iostream>
#include <string>
#include <string_view>

enum class ParseError { Empty, NotANumber, OutOfRange };

std::string_view describe(ParseError e)
{
    switch (e) {
        case ParseError::Empty: return "empty input";
        case ParseError::NotANumber: return "not a number";
        case ParseError::OutOfRange: return "age must be 0-130";
    }
    return "?";
}

std::expected<int, ParseError> parseAge(std::string_view text)
{
    if (text.empty()) return std::unexpected{ParseError::Empty};
    int value{};
    const auto [end, ec] = std::from_chars(text.data(), text.data() + text.size(), value);   // fast, no exceptions
    if (ec != std::errc{} || end != text.data() + text.size()) return std::unexpected{ParseError::NotANumber};
    if (value < 0 || value > 130) return std::unexpected{ParseError::OutOfRange};
    return value;
}

int main()
{
    for (std::string_view input : {"42", "", "abc", "200", "7x"}) {
        const auto result = parseAge(input);
        if (result) std::cout << '"' << input << "\" -> age " << *result << '\n';
        else        std::cout << '"' << input << "\" -> error: " << describe(result.error()) << '\n';
    }
    // value_or: a default when there's an error
    std::cout << "with default: " << parseAge("oops").value_or(-1) << '\n';
}
