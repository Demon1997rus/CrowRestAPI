#pragma once

#include "schemes/custom/customscheme.h"

class CalculateScheme : public CustomScheme {
    // BaseScheme interface
public:
    void validate(const crow::json::rvalue &data) const override;

    // CustomScheme interface
public:
    void fromJson(const crow::json::rvalue &data) override;

public:
    double current_money = 0.0;
    double expenses_per_month = 0.0;
    double salary_on_5th = 0.0;
    double salary_on_20th = 0.0;
    int target_year = 0;
    int target_month = 0;
    int target_day = 0;
};
