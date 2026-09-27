#include "task.h"

#include <cctype>

std::string_view toString(Priority p)
{
    switch (p) {
        case Priority::Low:    return "low";
        case Priority::Medium: return "medium";
        case Priority::High:   return "HIGH";
    }
    return "?";
}

std::optional<Priority> parsePriority(std::string_view text)
{
    std::string lower;
    for (char c : text) lower += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    if (lower == "low") return Priority::Low;
    if (lower == "medium" || lower == "med") return Priority::Medium;
    if (lower == "high") return Priority::High;
    return std::nullopt;
}
