#pragma once

#include <unordered_map>
#include <GL/gl3w.h>

#include <Core/Render/ShaderProgram.h>

namespace TE
{
    class GLShaderProgram final : public ShaderProgram
    {
    public:
        GLShaderProgram(const std::string &name, const std::initializer_list<std::shared_ptr<Shader>> &shaders);
        virtual ~GLShaderProgram() override;

        virtual void Bind() const override;
        virtual void Unbind() const override;
        virtual bool IsValid() const override;

        virtual void SetProperty(const std::string &propertyName, bool &data) override;
        virtual void SetProperty(const std::string &propertyName, int32_t &data) override;
        virtual void SetProperty(const std::string &propertyName, float &data) override;
        virtual void SetProperty(const std::string &propertyName, glm::vec2 &data) override;
        virtual void SetProperty(const std::string &propertyName, glm::vec3 &data) override;
        virtual void SetProperty(const std::string &propertyName, glm::vec4 &data) override;
        virtual void SetProperty(const std::string &propertyName, glm::mat3 &data) override;
        virtual void SetProperty(const std::string &propertyName, glm::mat4 &data) override;
        virtual bool ContainsProperty(const std::string &propertyName) const override;

    private:
        GLuint _id;
        std::unordered_map<std::string, GLint> _uniformCache;

        GLint GetUniformLocation(const std::string &name);
    };
}