#include "errorscheme.h"

ErrorScheme::ErrorScheme(const std::string &message) : std::runtime_error(message) {}
