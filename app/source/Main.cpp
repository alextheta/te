#include <App.h>

int main()
{
    auto app = std::make_unique<App>();

    app->Run();

    return 0;
}