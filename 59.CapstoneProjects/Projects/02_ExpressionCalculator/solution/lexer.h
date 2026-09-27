#pragma once
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

enum class TokenKind { Number, Name, Plus, Minus, Star, Slash, Percent, Caret, LParen, RParen, Assign, End };

struct Token {
    TokenKind kind;
    std::string text;      // for names and error messages
    double value{0};       // for numbers
    std::size_t position;  // 1-based column, for error messages
};

class ParseError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

std::vector<Token> tokenize(std::string_view input);
