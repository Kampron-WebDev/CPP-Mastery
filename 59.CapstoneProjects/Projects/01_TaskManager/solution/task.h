#pragma once
#include <optional>
#include <string>
#include <string_view>

enum class Priority { Low, Medium, High };

std::string_view toString(Priority p);
std::optional<Priority> parsePriority(std::string_view text);   // "low"/"medium"/"high" (any case)

struct Task {
    int id{};
    std::string title;
    Priority priority{Priority::Medium};
    std::string due;   // "YYYY-MM-DD" or empty
    bool done{false};
};
