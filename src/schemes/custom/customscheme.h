#pragma once

#include "schemes/base/basescheme.h"

class CustomScheme : public BaseScheme {
public:
    virtual ~CustomScheme() = default;
    virtual void fromJson(const crow::json::rvalue &data) = 0;
};
