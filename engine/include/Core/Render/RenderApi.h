#pragma once

#include <Core/Render/RenderBackend.h>
#include <Core/Render/VertexArray.h>
#include <Core/Render/ShaderProgram.h>

namespace TE
{
    class RenderApi
    {
    public:
        static RenderApiType GetApiType();

        static void Clear();
        static void ProcessSwapChain();

        static void StartFrame();
        static void Render(ShaderProgram &shaderProgram, VertexArray &vertexArray);
        static void Render(std::shared_ptr<ShaderProgram> &shaderProgram, std::shared_ptr<VertexArray> &vertexArray);
        static void EndFrame();

        static void DrawIndexed(VertexArray &vertexArray);

    private:
        friend class Render;
        inline static std::shared_ptr<RenderBackend> _backend;
    };
}