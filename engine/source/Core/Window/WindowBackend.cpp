#include <Core/Window/WindowBackend.h>

namespace TE
{
    const WindowHandle * const WindowBackend::GetWindowHandle() const
    {
        return _windowHandle.get();
    }
}