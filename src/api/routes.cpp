#include "routes.h"

Routes::Routes(crow::SimpleApp &app)
{
    CROW_ROUTE(app, "/calculate").methods("POST"_method)(Handlers::calculateHandler);
}
