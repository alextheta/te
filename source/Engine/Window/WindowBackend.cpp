#include <Engine/Window/WindowBackend.h>

namespace TE
{
    WindowHandle *WindowBackend::GetWindowHandle()
    {
        return _windowHandle.get();
    }
}