#include <EditorApp.h>

int main()
{
    auto app = std::make_unique<TE::EditorApp>();

    app->Run();

    return 0;
}