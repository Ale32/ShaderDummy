#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


// __debugbreak is platfrom specific here
#define ASSERT(x) if (!(x)) __debugbreak();

// Legacy OpenGL error handling
// This macro is for getting a proper error from OpenGL in an old style way
// #x gives you the string of the function called
#ifdef _DEBUG
    #define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
    #define GLCall(x) x
#endif

void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const Shader& shader) const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};