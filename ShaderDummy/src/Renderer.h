#pragma once

#include <GL/glew.h>
#include <iostream>

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