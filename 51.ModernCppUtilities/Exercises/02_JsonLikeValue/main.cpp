// ⭐⭐⭐ Exercise 02: JsonLikeValue
// Model a simple config value that can be ONE of: bool, int, double, std::string.
//   using Value = std::variant<bool, int, double, std::string>;
// 1. Write  std::string toText(const Value&)  using std::visit, producing JSON-style text:
//      true / 42 / 3.5 / "hello"   (strings in quotes!)
// 2. Store settings in a std::map<std::string, Value> and print them as  { "key": value, ... }
// 3. Write  std::optional<int> getInt(const std::map<...>&, const std::string& key)
//    that returns the int ONLY if the key exists AND holds an int (std::get_if).
#include <iostream>
#include <map>
#include <string>
#include <variant>

int main()
{
    // TODO: settings: "fullscreen" true, "width" 1920, "scale" 1.5, "title" "My Game"
}
