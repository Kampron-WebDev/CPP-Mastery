#pragma once
#include <functional>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "lexer.h"

// Recursive-descent evaluator. Keeps variables between calls.
class Calculator {
public:
    Calculator();

    // Returns the value; for "name = expr" also stores the variable. Throws ParseError on errors.
    double evaluate(std::string_view line, std::string* assignedName = nullptr);

private:
    // One function per grammar rule (see README.md).
    double expression();
    double term();
    double factor();
    double unary();
    double primary();

    const Token& peek() const { return tokens[pos]; }
    const Token& advance() { return tokens[pos++]; }
    bool match(TokenKind kind);
    [[noreturn]] void fail(const std::string& what) const;

    std::vector<Token> tokens;
    std::size_t pos{0};
    std::map<std::string, double> variables;
    std::map<std::string, std::function<double(double)>> functions;
};
