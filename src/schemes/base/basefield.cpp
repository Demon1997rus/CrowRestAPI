#include "basefield.h"

#include "errorscheme.h"

BaseField::BaseField(std::string fieldName, crow::json::type fieldType, bool required) :
    m_fieldName(std::move(fieldName)), m_fieldType(fieldType), m_required(required)
{
}

void BaseField::validate(const crow::json::rvalue &data) const
{
    m_hasField = data.has(m_fieldName);
    if (m_required && !m_hasField) {
        throw ErrorScheme("Missing required field: " + m_fieldName);
    }

    if (m_hasField) {
        if (data[m_fieldName].t() != m_fieldType) {
            throw ErrorScheme("Field " + m_fieldName + " must be of type " +
                              crow::json::get_type_str(m_fieldType));
        }
    }
}
