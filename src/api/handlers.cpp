#include "handlers.h"

#include "schemes/custom/calculatescheme.h"

crow::response Handlers::calculateHandler(const crow::request &req)
{
    CalculateScheme scheme;
    if (const auto errorScheme = processJsonToScheme(scheme, req)) {
        return crow::response(400, *errorScheme);
    }

    // TODO - реализовать функционал расчета
    return crow::response(400, "No release\n");
}
