#include "date.h"

#include <array>
#include <chrono>

namespace helpers { namespace date {
std::optional<std::string> isValidFutureDate(const int year, const int month, const int day)
{
    // Check if year is valid
    if (year < 0) {
        return "target_year must be a positive number";
    }

    // Check if month is valid
    if (month < 1 || month > 12) {
        return "target_month must be between 1 and 12";
    }

    // Check validity of day considering leap years
    static const std::array<int, 12> days_in_month = {31, 28, 31, 30, 31, 30,
                                                      31, 31, 30, 31, 30, 31};

    // Leap year check
    bool is_leap_year = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (is_leap_year && month == 2) {
        if (day < 1 || day > 29) {
            return "target_day must be between 1 and 29 for February in a leap year";
        }
    } else {
        if (day < 1 || day > days_in_month[month - 1]) {
            return "target_day must be within the valid range for the given month";
        }
    }

    // Get the current date
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time_t);

    // Create a tm structure for the target date
    std::tm target_tm = {};
    target_tm.tm_year = year - 1900; // tm_year is years since 1900
    target_tm.tm_mon = month - 1;    // tm_mon is 0-11
    target_tm.tm_mday = day;
    target_tm.tm_hour = 0;
    target_tm.tm_min = 0;
    target_tm.tm_sec = 0;
    std::time_t target_time_t = std::mktime(&target_tm);

    // Compare with current date
    if (target_time_t <= now_time_t) {
        return "The target date must be in the future";
    }

    return std::nullopt;
}
}}
