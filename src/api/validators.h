#pragma once

#include <optional>

#include <crow/json.h>

class Validators {
    // Schemes
public:
    static std::vector<std::string>
    validateCalculateSchema(const crow::json::rvalue &json_data);

    // helpers
public:
    static std::optional<std::string> checkMemberType(const crow::json::rvalue &json_data,
                                                      const std::string &key,
                                                      const crow::json::type type);
    static std::optional<std::string> isValidFutureDate(int year, int month, int day);
};
