#pragma once

#include <stdexcept>

class ErrorScheme : public std::runtime_error {
public:
    explicit ErrorScheme(const std::string &message);
};
