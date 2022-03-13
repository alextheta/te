#pragma once

#include <memory>

#include <Core/Render/IndexBuffer.h>
#include <Core/Render/VertexBuffer.h>
#include <Core/Render/VertexArray.h>
#include <Engine/Component.h>

namespace TE
{
    class Renderer final : public Component
    {
    public:
        Renderer();
        virtual ~Renderer();

        void Render(Transform &transform);

        void SetMaterial(std::shared_ptr<Material> material);

    private:
        std::shared_ptr<Material> _material;
        std::shared_ptr<IndexBuffer> _indexBuffer;
        std::shared_ptr<VertexBuffer> _vertexBuffer;
        std::shared_ptr<VertexArray> _vertexArray;
    };
}
