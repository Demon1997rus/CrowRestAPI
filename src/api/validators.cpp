#include "validators.h"

#include <iostream>

std::vector<std::string>
Validators::validateCalculateSchema(const crow::json::rvalue &json_data)
{
    std::vector<std::string> errors;
    std::vector<std::pair<std::string, crow::json::type>> fields = {
        {"current_money", crow::json::type::Number},
        {"expenses_per_month", crow::json::type::Number},
        {"salary_on_5th", crow::json::type::Number},
        {"salary_on_20th", crow::json::type::Number},
        {"target_year", crow::json::type::Number},
        {"target_month", crow::json::type::Number},
        {"target_day", crow::json::type::Number}};

    // check key and type
    for (const auto &field : fields) {
        if (auto error = checkMemberType(json_data, field.first, field.second)) {
            errors.emplace_back(std::move(*error));
        }
    }

    // Value checks
    if (errors.empty()) {
        const double current_money = json_data["current_money"].d();
        const double expenses_per_month = json_data["expenses_per_month"].d();
        const double salary_on_5th = json_data["salary_on_5th"].d();
        const double salary_on_20th = json_data["salary_on_20th"].d();
        const int target_year = json_data["target_year"].i();
        const int target_month = json_data["target_month"].i();
        const int target_day = json_data["target_day"].i();

        // Check that current_money is non-negative
        if (current_money < 0) {
            errors.emplace_back("current_money must be non-negative");
        }

        // Check that expenses_per_month is non-negative
        if (expenses_per_month < 0) {
            errors.emplace_back("expenses_per_month must be non-negative");
        }

        // Check that salary_on_5th is non-negative
        if (salary_on_5th < 0) {
            errors.emplace_back("salary_on_5th must be non-negative");
        }

        // Check that salary_on_20th is non-negative
        if (salary_on_20th < 0) {
            errors.emplace_back("salary_on_20th must be non-negative");
        }

        if (auto error = isValidFutureDate(target_year, target_month, target_day)) {
            errors.emplace_back(*error);
        }
    }
    return errors;
}

std::optional<std::string> Validators::checkMemberType(const crow::json::rvalue &json_data,
                                                       const std::string &key,
                                                       const crow::json::type expected_type)
{
    if (!json_data.has(key)) {
        return "Missing field: " + key;
    } else if (json_data[key].t() != expected_type) {
        return "Invalid type for field: " + key;
    }
    return std::nullopt;
}

std::optional<std::string> Validators::isValidFutureDate(int year, int month, int day)
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
    static std::vector<int> days_in_month = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

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
