#pragma once

#include <optional>
#include <string>

namespace helpers { namespace date {
std::optional<std::string> isValidFutureDate(const int year, const int month, const int day);
}}
