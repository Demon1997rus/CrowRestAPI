#pragma once

#include <crow.h>

class BaseScheme {
public:
    BaseScheme() = default;
    virtual ~BaseScheme() = default;
    virtual void validate(const crow::json::rvalue &data) const = 0;
};
