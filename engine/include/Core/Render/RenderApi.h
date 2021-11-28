#pragma once

#include <Core/Render/RenderBackend.h>
#include <Core/Render/VertexArray.h>
#include <Core/Render/Material.h>

namespace TE
{
    class RenderApi
    {
    public:
        static RenderApiType GetApiType();

        static void Clear();
        static void ProcessSwapChain();

        static void StartFrame();
        static void Render(Material &material, VertexArray &vertexArray);
        static void Render(std::shared_ptr<Material> &material, std::shared_ptr<VertexArray> &vertexArray);
        static void EndFrame();

        static void DrawIndexed(VertexArray &vertexArray);

    private:
        friend class Render;
        inline static std::shared_ptr<RenderBackend> _backend;
    };
}