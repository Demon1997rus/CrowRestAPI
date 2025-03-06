#include "handlers.h"

#include <boost/algorithm/string/join.hpp>

#include "validators.h"

crow::response Handlers::calculateHandler(const crow::request &req)
{
    auto json_data = crow::json::load(req.body);
    if (!json_data) {
        return crow::response(400, "Invalid JSON\n");
    }

    auto errors = Validators::validateCalculateSchema(json_data);
    if (!errors.empty()) {
        return crow::response(400, boost::algorithm::join(errors, "; "));
    }

    // TODO - реализовать функционал расчета
    return crow::response(400, "No release\n");
}
