#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

template <typename T>
class Stack {
public:
    void push(const T& value) { items.push_back(value); }

    T pop()
    {
        if (items.empty()) throw std::underflow_error{"pop on empty stack"};
        T value = items.back();
        items.pop_back();
        return value;
    }

    const T& top() const
    {
        if (items.empty()) throw std::underflow_error{"top on empty stack"};
        return items.back();
    }

    bool empty() const { return items.empty(); }
    std::size_t size() const { return items.size(); }

    friend std::ostream& operator<<(std::ostream& os, const Stack& s)
    {
        os << "[bottom] ";
        for (const auto& item : s.items) os << item << ' ';
        return os << "[top]";
    }

private:
    std::vector<T> items;
};

std::string reversed(std::string_view word)
{
    Stack<char> s;
    for (char c : word) s.push(c);
    std::string out;
    while (!s.empty()) out += s.pop();
    return out;
}

bool balanced(std::string_view text)
{
    Stack<char> open;
    for (char c : text) {
        if (c == '(' || c == '[' || c == '{') {
            open.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (open.empty()) return false;
            const char expected = (c == ')') ? '(' : (c == ']') ? '[' : '{';
            if (open.pop() != expected) return false;
        }
    }
    return open.empty();   // leftovers like "((" are unbalanced
}

int main()
{
    Stack<int> numbers;
    for (int i = 1; i <= 4; ++i) numbers.push(i * 10);
    std::cout << numbers << '\n';

    std::cout << reversed("stressed") << '\n';
    std::cout << std::boolalpha;
    for (std::string_view t : {"{[()]}", "([)]", "(("}) std::cout << t << " balanced? " << balanced(t) << '\n';

    try {
        Stack<std::string> empty;
        empty.pop();
    } catch (const std::underflow_error& e) {
        std::cout << "caught: " << e.what() << '\n';
    }
}
