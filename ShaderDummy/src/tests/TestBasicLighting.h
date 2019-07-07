#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>


namespace test {

    class TestBasicLighting : public Test
    {
    private:
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;

        glm::vec3 m_ObjectColor;

        glm::vec3 m_LightPosition;
        glm::vec3 m_LightColor;

    public:
        TestBasicLighting();
        ~TestBasicLighting();

        void OnUpdate(float deltaTime) override;
        void OnRender(const glm::mat4& view, const glm::mat4& projection) override;
        void OnImGuiRender() override;
    };
}