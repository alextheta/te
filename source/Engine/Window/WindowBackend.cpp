#include <Engine/Window/WindowBackend.h>

namespace TE
{
    WindowBackend::~WindowBackend()
    {

    }

    WindowHandle *WindowBackend::GetWindowHandle()
    {
        return _windowHandle.get();
    }
}