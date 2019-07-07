#include "TestBasicLighting.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <iostream>


namespace test {

    TestBasicLighting::TestBasicLighting()
        : m_ObjectColor(0.7f, 0.3f, 0.1f), m_LightPosition(0.0f, 3.0f, 0.0f), m_LightColor(1.0f, 1.0f, 1.0f)
    {
        // Vertex data
        float vertexData[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  // position and normal
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Create the vertex buffer
        m_VertexBuffer = std::make_unique<VertexBuffer>(vertexData, 6 * 36 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);

        // Create the vertex array object
        m_VAO = std::make_unique<VertexArray>();
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        // Creating shader
        m_Shader = std::make_unique<Shader>(
            "res/shaders/BasicLighting.vertex",
            "res/shaders/BasicLighting.fragment"
        );
        m_Shader->Bind();
        m_Shader->SetUniform3f("u_Color", m_ObjectColor);
    }

    TestBasicLighting::~TestBasicLighting()
    {
    }

    void TestBasicLighting::OnUpdate(float deltaTime)
    {
    }

    void TestBasicLighting::OnRender(const glm::mat4& view, const glm::mat4& projection)
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
            
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_model", model);
            m_Shader->SetUniformMat4f("u_view", view);
            m_Shader->SetUniformMat4f("u_projection", projection);

            m_Shader->SetUniform3f("u_LightPos", m_LightPosition);
            m_Shader->SetUniform3f("u_LightColor", m_LightColor);

            glm::mat4 viewInverse = glm::inverse(view);
            glm::vec3 cameraPosition = glm::vec3(viewInverse[3][0], viewInverse[3][1], viewInverse[3][2]);
            std::cout << "Camera position (" 
                << cameraPosition.x << ", "
                << cameraPosition.y << ", "
                << cameraPosition.z << ")\n";
            
            m_Shader->SetUniform3f("u_ViewPos", cameraPosition);

            renderer.Draw(*m_VAO, *m_Shader);
        }
    }

    void TestBasicLighting::OnImGuiRender()
    {
        ImGui::SliderFloat3("Light Position", &m_LightPosition.x, -5.0f, 5.0f);
        ImGui::SliderFloat3("Light Color", &m_LightColor.x, 0.0f, 1.0f);
    }

}