#include <texttools/texttools.h>

#include <cctype>

namespace texttools {

std::string toUpper(std::string_view s)
{
    std::string out;
    out.reserve(s.size());
    for (char c : s) out += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return out;
}

std::vector<std::string> split(std::string_view s, char sep)
{
    std::vector<std::string> parts;
    std::size_t start = 0;
    while (true) {
        const auto pos = s.find(sep, start);
        parts.emplace_back(s.substr(start, pos - start));
        if (pos == std::string_view::npos) break;
        start = pos + 1;
    }
    return parts;
}

std::string join(const std::vector<std::string>& parts, std::string_view sep)
{
    std::string out;
    for (std::size_t i = 0; i < parts.size(); ++i) {
        if (i) out += sep;
        out += parts[i];
    }
    return out;
}

}  // namespace texttools
