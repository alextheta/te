#include <Engine/Application.h>

int main()
{
    auto app = std::make_unique<TE::Application>();

    app->Run();

    return 0;
}