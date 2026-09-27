#pragma once
#include <optional>
#include <span>

namespace stats {

// Returns nothing for an empty input.
std::optional<double> mean(std::span<const double> values);
std::optional<double> minimum(std::span<const double> values);
std::optional<double> maximum(std::span<const double> values);

}  // namespace stats
