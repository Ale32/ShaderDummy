#include "Renderer.h"

#include <iostream>


void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ") " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const Shader& shader) const
{
    va.Bind();
    shader.Bind();

    GLCall(glDrawArrays(GL_TRIANGLES, 0, va.GetVertexCount()));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();

    // Draw call - passing nullptr because we are already selecting the index buffer
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr)); // Assuming here that the ib is of type GL_UNSIGNED_INT
}