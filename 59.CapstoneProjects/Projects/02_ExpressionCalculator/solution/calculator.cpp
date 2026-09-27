#include "calculator.h"

#include <cmath>
#include <numbers>

Calculator::Calculator()
{
    variables["pi"] = std::numbers::pi;
    variables["e"] = std::numbers::e;
    functions["sqrt"] = [](double x) { return std::sqrt(x); };
    functions["abs"] = [](double x) { return std::abs(x); };
    functions["sin"] = [](double x) { return std::sin(x); };
    functions["cos"] = [](double x) { return std::cos(x); };
    functions["ln"] = [](double x) { return std::log(x); };
}

double Calculator::evaluate(std::string_view line, std::string* assignedName)
{
    tokens = tokenize(line);
    pos = 0;

    // statement := NAME '=' expression | expression
    std::string target;
    if (tokens.size() >= 3 && tokens[0].kind == TokenKind::Name && tokens[1].kind == TokenKind::Assign) {
        target = tokens[0].text;
        pos = 2;
    }
    const double value = expression();
    if (peek().kind != TokenKind::End) fail("unexpected '" + peek().text + "'");
    if (!target.empty()) {
        if (functions.contains(target)) throw ParseError{"'" + target + "' is a function name"};
        variables[target] = value;
        if (assignedName) *assignedName = target;
    }
    variables["ans"] = value;
    return value;
}

bool Calculator::match(TokenKind kind)
{
    if (peek().kind != kind) return false;
    ++pos;
    return true;
}

void Calculator::fail(const std::string& what) const
{
    throw ParseError{what + " at position " + std::to_string(peek().position)};
}

// expression := term (('+' | '-') term)*     (a loop makes it LEFT-associative: 10-4-3 = 3)
double Calculator::expression()
{
    double value = term();
    while (true) {
        if (match(TokenKind::Plus)) value += term();
        else if (match(TokenKind::Minus)) value -= term();
        else return value;
    }
}

// term := factor (('*' | '/' | '%') factor)*
double Calculator::term()
{
    double value = factor();
    while (true) {
        if (match(TokenKind::Star)) {
            value *= factor();
        } else if (match(TokenKind::Slash) || match(TokenKind::Percent)) {
            const bool isModulo = tokens[pos - 1].kind == TokenKind::Percent;
            const double rhs = factor();
            if (rhs == 0) throw ParseError{isModulo ? "modulo by zero" : "division by zero"};
            value = isModulo ? std::fmod(value, rhs) : value / rhs;
        } else {
            return value;
        }
    }
}

// factor := unary ('^' factor)?     (recursion on the right makes it RIGHT-associative: 2^3^2 = 512)
double Calculator::factor()
{
    const double base = unary();
    if (match(TokenKind::Caret)) return std::pow(base, factor());
    return base;
}

// unary := '-' unary | primary
double Calculator::unary()
{
    if (match(TokenKind::Minus)) return -unary();
    if (match(TokenKind::Plus)) return unary();
    return primary();
}

// primary := NUMBER | NAME | NAME '(' expression ')' | '(' expression ')'
double Calculator::primary()
{
    const Token& token = peek();
    if (match(TokenKind::Number)) return token.value;
    if (match(TokenKind::LParen)) {
        const double value = expression();
        if (!match(TokenKind::RParen)) fail("expected ')'");
        return value;
    }
    if (token.kind == TokenKind::Name) {
        const std::string name = advance().text;
        if (match(TokenKind::LParen)) {   // function call
            const auto fn = functions.find(name);
            if (fn == functions.end()) throw ParseError{"unknown function '" + name + "'"};
            const double arg = expression();
            if (!match(TokenKind::RParen)) fail("expected ')' after function argument");
            return fn->second(arg);
        }
        const auto var = variables.find(name);
        if (var == variables.end()) throw ParseError{"unknown variable '" + name + "'"};
        return var->second;
    }
    fail("unexpected '" + token.text + "'");
}
