#include "lexer.h"

#include <cctype>

std::vector<Token> tokenize(std::string_view input)
{
    std::vector<Token> tokens;
    std::size_t i = 0;
    while (i < input.size()) {
        const char c = input[i];
        const std::size_t column = i + 1;
        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
        } else if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            const std::size_t start = i;
            while (i < input.size() && (std::isdigit(static_cast<unsigned char>(input[i])) || input[i] == '.')) ++i;
            const std::string text{input.substr(start, i - start)};
            std::size_t used = 0;
            double value = 0;
            try {
                value = std::stod(text, &used);
            } catch (const std::exception&) {
                used = 0;
            }
            if (used != text.size()) throw ParseError{"bad number '" + text + "' at position " + std::to_string(column)};
            tokens.push_back({TokenKind::Number, text, value, column});
        } else if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
            const std::size_t start = i;
            while (i < input.size() && (std::isalnum(static_cast<unsigned char>(input[i])) || input[i] == '_')) ++i;
            tokens.push_back({TokenKind::Name, std::string{input.substr(start, i - start)}, 0, column});
        } else {
            TokenKind kind{};
            switch (c) {
                case '+': kind = TokenKind::Plus; break;
                case '-': kind = TokenKind::Minus; break;
                case '*': kind = TokenKind::Star; break;
                case '/': kind = TokenKind::Slash; break;
                case '%': kind = TokenKind::Percent; break;
                case '^': kind = TokenKind::Caret; break;
                case '(': kind = TokenKind::LParen; break;
                case ')': kind = TokenKind::RParen; break;
                case '=': kind = TokenKind::Assign; break;
                default: throw ParseError{std::string{"unknown character '"} + c + "' at position " + std::to_string(column)};
            }
            tokens.push_back({kind, std::string(1, c), 0, column});
            ++i;
        }
    }
    tokens.push_back({TokenKind::End, "end of input", 0, input.size() + 1});
    return tokens;
}
