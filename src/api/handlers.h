#pragma once

#include "crow.h"

class Handlers {
public:
    static crow::response calculateHandler(const crow::request &req);
};
