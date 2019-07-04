#include "TestCube.h"

#include "Renderer.h"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test {

    TestCube::TestCube()
        : m_Translation(0.0f, 0.0f, 0.0f), m_Rotation(0.0f, 0.0f, 0.0f)
    {
        // Vertex data
        float vertexData[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // first three are position, next two are uv
             0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        // Create the vertex buffer
        m_VertexBuffer = std::make_unique<VertexBuffer>(vertexData, 5 * 36 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);

        // Create the vertex array object
        m_VAO = std::make_unique<VertexArray>();
        m_VAO->AddBuffer(*m_VertexBuffer, layout);

        // Creating shader
        m_Shader = std::make_unique<Shader>("res/shaders/Cube.vertex", "res/shaders/Cube.fragment");
        m_Shader->Bind();

        // Create a texture
        m_Texture = std::make_unique<Texture>("res/textures/SampleImage.png");
        m_Shader->SetUniform1i("u_texture", 0);
    }

    TestCube::~TestCube()
    {
    }

    void TestCube::OnUpdate(float deltaTime)
    {
    }

    void TestCube::OnRender(const glm::mat4& view, const glm::mat4& projection)
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
            model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_model", model);
            m_Shader->SetUniformMat4f("u_view", view);
            m_Shader->SetUniformMat4f("u_projection", projection);
            
            renderer.Draw(*m_VAO, *m_Shader);
        }
    }

    void TestCube::OnImGuiRender()
    {
        ImGui::SliderFloat3("Translation", &m_Translation.x, -1.0f, 1.0f);
        ImGui::SliderFloat("Translation Z", &m_Translation.z, -10.0f, 0.0f);

        ImGui::SliderFloat("Rotation X", &m_Rotation.x, -90, 90);
        ImGui::SliderFloat("Rotation Y", &m_Rotation.y, -90, 90);
        ImGui::SliderFloat("Rotation Z", &m_Rotation.z, -90, 90);
    }

}