#include <EditorApp.h>
#include <Engine/Logger.h>

namespace TE
{
    void EditorApp::Init()
    {
        Logger::Message("App init");
    }

    void EditorApp::Update()
    {

    }

    void EditorApp::Dispose()
    {
        Logger::Message("App dispose");
    }
}