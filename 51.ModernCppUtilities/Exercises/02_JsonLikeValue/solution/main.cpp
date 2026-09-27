#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <type_traits>
#include <variant>

using Value = std::variant<bool, int, double, std::string>;

std::string toText(const Value& v)
{
    return std::visit(
        [](const auto& x) -> std::string {
            using T = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<T, bool>) return x ? "true" : "false";
            else if constexpr (std::is_same_v<T, std::string>) return "\"" + x + "\"";
            else {
                std::string s = std::to_string(x);
                if constexpr (std::is_same_v<T, double>) {   // trim trailing zeros: 1.500000 -> 1.5
                    s.erase(s.find_last_not_of('0') + 1);
                    if (s.back() == '.') s.pop_back();
                }
                return s;
            }
        },
        v);
}

std::optional<int> getInt(const std::map<std::string, Value>& m, const std::string& key)
{
    const auto it = m.find(key);
    if (it == m.end()) return std::nullopt;
    if (const int* p = std::get_if<int>(&it->second)) return *p;
    return std::nullopt;   // exists, but isn't an int
}

int main()
{
    const std::map<std::string, Value> settings{
        {"fullscreen", true}, {"width", 1920}, {"scale", 1.5}, {"title", std::string{"My Game"}}};

    std::cout << "{ ";
    bool first = true;
    for (const auto& [key, value] : settings) {
        std::cout << (first ? "" : ", ") << '"' << key << "\": " << toText(value);
        first = false;
    }
    std::cout << " }\n";

    std::cout << "width: " << getInt(settings, "width").value_or(-1) << '\n';
    std::cout << "scale as int: " << getInt(settings, "scale").value_or(-1) << " (not an int)\n";
    std::cout << "missing: " << getInt(settings, "height").value_or(-1) << '\n';
}
