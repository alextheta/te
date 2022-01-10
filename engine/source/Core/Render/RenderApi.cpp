#include <Core/Render/RenderApi.h>

namespace TE
{
    RenderApiType RenderApi::GetApiType()
    {
        return _backend->GetApiType();
    }

    void RenderApi::Clear()
    {
        _backend->Clear();
    }

    void RenderApi::ProcessSwapChain()
    {
        _backend->ProcessSwapChain();
    }

    void RenderApi::StartFrame()
    {

    }

    void RenderApi::Render(Material &material, VertexArray &vertexArray)
    {
        material.Bind();
        vertexArray.Bind();
        DrawIndexed(vertexArray);
    }

    void RenderApi::Render(std::shared_ptr<Material> &material, std::shared_ptr<VertexArray> &vertexArray)
    {
        Render(*material, *vertexArray);
    }

    void RenderApi::EndFrame()
    {

    }

    void RenderApi::DrawIndexed(VertexArray &vertexArray)
    {
        _backend->DrawIndexed(vertexArray);
    }
}