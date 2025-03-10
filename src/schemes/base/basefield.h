#pragma once

#include "basescheme.h"

class BaseField : public BaseScheme {
public:
    BaseField(std::string fieldName, crow::json::type fieldType, bool required = true);
    virtual ~BaseField() = default;

    // BaseScheme interface
public:
    void validate(const crow::json::rvalue &data) const override;

protected:
    std::string m_fieldName;
    crow::json::type m_fieldType;
    bool m_required;
    mutable bool m_hasField = false;
};
