# Project 02: Expression Calculator ⭐⭐⭐

Build a calculator that understands **real expressions** with operator precedence, brackets and variables,
the same technique compilers use. It's one of the most educational projects in computer science.

```
> 2 + 3 * 4
14
> (2 + 3) * 4
20
> x = 5
x = 5
> y = x ^ 2 - 1
y = 24
> -(x + y) / 2
-14.5
> 10 / (5 - 5)
Error: division by zero
> 3 + * 4
Error: unexpected '*' at position 5
```

## How it works: two stages

**1. Tokenizer (lexer):** turns text into tokens.
`"x = 3.5 * (y+1)"` → `[NAME x] [=] [NUMBER 3.5] [*] [(] [NAME y] [+] [NUMBER 1] [)]`

**2. Recursive-descent parser:** each precedence level is one function, and they call each other. The **grammar**:
```
statement  := NAME '=' expression | expression
expression := term   (('+' | '-') term)*          ← lowest precedence
term       := factor (('*' | '/' | '%') factor)*
factor     := unary  ('^' factor)?                ← right-associative: 2^3^2 = 2^9
unary      := '-' unary | primary
primary    := NUMBER | NAME | NAME '(' expression ')' | '(' expression ')'
```
Because `expression` calls `term` which calls `factor`, `*` naturally binds tighter than `+`. The structure of the
code *is* the precedence table.

## Milestones
1. Tokenizer: numbers (including decimals), `+ - * / % ^ ( ) =`, names; errors for unknown characters.
2. Parser for `+ - * /` and brackets. Test: `2+3*4 = 14`, `(2+3)*4 = 20`, `10-4-3 = 3` (left-associative!).
3. Unary minus and `^` (right-associative).
4. Variables stored in `std::map<std::string, double>`; assignment; error for unknown variables.
5. Functions: `sqrt(x)`, `abs(x)`, `sin(x)`… via a map of name → `std::function<double(double)>`.
6. Error messages with the **position** of the problem.

## Definition of done
- [ ] All examples above work, and errors never crash the program.
- [ ] Automated tests for at least 15 expressions (including errors).
- [ ] Tokenizer and parser are in separate files.

## Stretch goals
- Build an **AST** (tree of nodes, `std::unique_ptr` children) instead of evaluating directly, then evaluate/print the tree.
- Multi-argument functions: `max(1, 2, 3)`.
- Constants `pi`, `e`; `ans` = last result.

Starter: [main.cpp](main.cpp) · Reference: [solution/](solution/main.cpp)
