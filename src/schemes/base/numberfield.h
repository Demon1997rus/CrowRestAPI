#pragma once

#include "basefield.h"
#include "errorscheme.h"

template <class T>
class NumberField : public BaseField {
    static_assert(std::is_arithmetic<T>::value, "NumberField requires an arithmetic type");

public:
    using range_validator = std::function<bool(T)>;
    using limit_type = std::numeric_limits<T>;

    NumberField(std::string fieldName, bool required = true, T minVal = limit_type::lowest(),
                T maxVal = limit_type::max(), range_validator validator = nullptr) :
        BaseField(std::move(fieldName), crow::json::type::Number, required),
        m_min(minVal), m_max(maxVal), m_validator(std::move(validator))
    {
    }

    virtual ~NumberField() = default;

    // BaseScheme interface
public:
    void validate(const crow::json::rvalue &data) const override
    {
        BaseField::validate(data);
        if (m_hasField) {
            const double temp_value = data[m_fieldName].d();
            if (temp_value > limit_type::max() || temp_value < limit_type::lowest()) {
                throw ErrorScheme("Value for field " + m_fieldName +
                                  " is outside the range of the type");
            }

            const T value = static_cast<T>(temp_value);

            if (value < m_min || value > m_max) {
                throw ErrorScheme("Value for field " + m_fieldName + " is out of range");
            }

            if (m_validator && !m_validator(value)) {
                throw ErrorScheme("Value for field " + m_fieldName +
                                  " failed custom validation");
            }
        }
    }

private:
    T m_min;
    T m_max;
    range_validator m_validator;
};
