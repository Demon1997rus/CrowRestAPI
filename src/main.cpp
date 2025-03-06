#include "api/routes.h"

int main()
{
    crow::SimpleApp app;
    Routes routes(app);
    app.port(18080).multithreaded().run();
}
