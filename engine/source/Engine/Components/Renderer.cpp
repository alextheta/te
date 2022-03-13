#include <Core/Render/RenderApi.h>
#include <Engine/Components/Transform.h>
#include <Engine/Components/Renderer.h>

#include <glm/gtc/matrix_transform.hpp>

namespace TE
{
    Renderer::Renderer()
    {
        glm::vec3 vertices[] = {
                glm::vec3(-1.0f, -1.0f, 1.0f),
                glm::vec3(1.0f, -1.0f, 1.0f),
                glm::vec3(-1.0f, 1.0f, 1.0f),
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(-1.0f, -1.0f, -1.0f),
                glm::vec3(1.0f, -1.0f, -1.0f),
                glm::vec3(-1.0f, 1.0f, -1.0),
                glm::vec3(1.0f, 1.0f, -1.0f),
        };

        int indices[] = {
                0, 2, 3, 0, 3, 1,
                2, 6, 7, 2, 7, 3,
                6, 4, 5, 6, 5, 7,
                4, 0, 1, 4, 1, 5,
                0, 4, 6, 0, 6, 2,
                1, 5, 7, 1, 7, 3,
        };

        _indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(int));


        _vertexBuffer = VertexBuffer::Create(
                vertices,
                sizeof(vertices),
                {
                        {ShaderDataType::Float3, "a_Position"}
                });

        _vertexArray = VertexArray::Create();
        _vertexArray->AddVertexBuffer(_vertexBuffer);
        _vertexArray->SetIndexBuffer(_indexBuffer);
    }

    Renderer::~Renderer()
    {

    }

    void Renderer::Render(Transform &transform)
    {
        if (_material != nullptr && _material->IsValid())
        {
            auto modelMatrix = glm::lookAt(glm::vec3(0, 12, 27), glm::vec3(0, 0, 0), glm::vec3(0.0f, 1.0f, 0.0f));
            modelMatrix = glm::translate(modelMatrix, transform.position);
            modelMatrix = glm::scale(modelMatrix, transform.scale);
            modelMatrix = glm::rotate(modelMatrix, 0.0f, transform.scale); // TODO
            _material->SetProperty("u_ModelMatrix", modelMatrix);

            RenderApi::Render(*_material, *_vertexArray);
        }
    }

    void Renderer::SetMaterial(std::shared_ptr<Material> material)
    {
        _material = material;
    }
}
