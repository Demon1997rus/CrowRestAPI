#include "api/routes.h"
#include "schemes/base/numberfield.h"

int main()
{
    crow::SimpleApp app;
    Routes routes(app);
    app.port(18080).multithreaded().run();
}
