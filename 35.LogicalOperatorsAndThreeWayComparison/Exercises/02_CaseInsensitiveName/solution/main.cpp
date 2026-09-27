#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <compare>
#include <cctype>
#include <utility>

class Name {
public:
    explicit Name(std::string v) : value{std::move(v)} {}

    std::weak_ordering operator<=>(const Name& other) const
    {
        const std::size_t n = std::min(value.size(), other.value.size());
        for (std::size_t i = 0; i < n; ++i) {
            const int a = std::tolower(static_cast<unsigned char>(value[i]));
            const int b = std::tolower(static_cast<unsigned char>(other.value[i]));
            if (a != b) return a < b ? std::weak_ordering::less : std::weak_ordering::greater;
        }
        return value.size() <=> other.value.size();   // shorter first; converts strong -> weak
    }

    bool operator==(const Name& other) const { return (*this <=> other) == 0; }

    const std::string& str() const { return value; }

private:
    std::string value;
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << (Name{"alice"} == Name{"ALICE"}) << ' ' << (Name{"Bob"} < Name{"alice"}) << '\n';

    std::vector<Name> names{Name{"bob"}, Name{"Alice"}, Name{"carol"}, Name{"ALICE"}, Name{"Bob"}};
    std::stable_sort(names.begin(), names.end());   // stable: equivalent names keep their order
    for (const auto& n : names) std::cout << n.str() << ' ';
    std::cout << '\n';
}
