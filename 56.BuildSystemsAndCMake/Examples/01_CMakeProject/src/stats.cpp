#include <stats/stats.h>

#include <algorithm>
#include <numeric>

namespace stats {

std::optional<double> mean(std::span<const double> values)
{
    if (values.empty()) return std::nullopt;
    return std::accumulate(values.begin(), values.end(), 0.0) / static_cast<double>(values.size());
}

std::optional<double> minimum(std::span<const double> values)
{
    if (values.empty()) return std::nullopt;
    return *std::min_element(values.begin(), values.end());
}

std::optional<double> maximum(std::span<const double> values)
{
    if (values.empty()) return std::nullopt;
    return *std::max_element(values.begin(), values.end());
}

}  // namespace stats
