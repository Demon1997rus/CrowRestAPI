#include "calculatescheme.h"

#include "helpers/date.h"
#include "schemes/base/numberfield.h"

void CalculateScheme::validate(const crow::json::rvalue &data) const
{
    // Создаем объекты NumberField для валидации
    NumberField<double> currentMoneyField("current_money", true, 0.0);
    NumberField<double> expensesPerMonthField("expenses_per_month", true, 0.0);
    NumberField<double> salaryOn5thField("salary_on_5th", true, 0.0);
    NumberField<double> salaryOn20thField("salary_on_20th", true, 0.0);
    NumberField<int> targetYearField("target_year", true);
    NumberField<int> targetMonthField("target_month", true);
    NumberField<int> targetDayField("target_day", true);

    // Выполнение валидации полей
    currentMoneyField.validate(data);
    expensesPerMonthField.validate(data);
    salaryOn5thField.validate(data);
    salaryOn20thField.validate(data);
    targetYearField.validate(data);
    targetMonthField.validate(data);
    targetDayField.validate(data);

    // Валидация даты
    const int year = data["target_year"].i();
    const int month = data["target_month"].i();
    const int day = data["target_day"].i();
    if (auto errorDate = helpers::date::isValidFutureDate(year, month, day)) {
        throw ErrorScheme(*errorDate);
    }
}

void CalculateScheme::fromJson(const crow::json::rvalue &data)
{
    this->current_money = data["current_money"].d();
    this->expenses_per_month = data["expenses_per_month"].d();
    this->salary_on_5th = data["salary_on_5th"].d();
    this->salary_on_20th = data["salary_on_20th"].d();
    this->target_year = data["target_year"].i();
    this->target_month = data["target_month"].i();
    this->target_day = data["target_day"].i();
}
