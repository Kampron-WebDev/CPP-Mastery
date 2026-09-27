#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace texttools {

std::string toUpper(std::string_view s);
std::vector<std::string> split(std::string_view s, char sep);
std::string join(const std::vector<std::string>& parts, std::string_view sep);

}  // namespace texttools
