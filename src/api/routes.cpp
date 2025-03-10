#include "routes.h"

Routes::Routes(crow::SimpleApp &app)
{
    CROW_ROUTE(app, "/calculate").methods(crow::HTTPMethod::POST)(Handlers::calculateHandler);
}
