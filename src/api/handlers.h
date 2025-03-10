#pragma once

#include <optional>

#include "crow.h"

class Handlers {
public:
    static crow::response calculateHandler(const crow::request &req);

private:
    template <typename Scheme>
    static std::optional<std::string> processJsonToScheme(Scheme &scheme,
                                                          const crow::request &req)
    {
        auto json_data = crow::json::load(req.body);
        if (!json_data) {
            return "Invalid JSON";
        }

        try {
            scheme.validate(json_data);
            scheme.fromJson(json_data);
        } catch (const std::exception &e) {
            return e.what();
        }

        return std::nullopt;
    }
};
