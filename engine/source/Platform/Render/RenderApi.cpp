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

    void RenderApi::Render(ShaderProgram &shaderProgram, VertexArray &vertexArray)
    {
        shaderProgram.Bind();
        vertexArray.Bind();
        DrawIndexed(vertexArray);
    }

    void RenderApi::Render(std::shared_ptr<ShaderProgram> &shaderProgram, std::shared_ptr<VertexArray> &vertexArray)
    {
        Render(*shaderProgram, *vertexArray);
    }

    void RenderApi::EndFrame()
    {

    }

    void RenderApi::DrawIndexed(VertexArray &vertexArray)
    {
        _backend->DrawIndexed(vertexArray);
    }
}