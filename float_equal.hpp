#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <limits>

template<std::floating_point T> [[nodiscard]] auto float_equal(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()) -> bool
{
    return std::abs(a - b) <= epsilon * std::max(std::abs(a), std::abs(b));
}