#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"


struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};


static ShaderProgramSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}


static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);

        // alloca will allocate on the stack dynamically
        // Can't really do char message[lenght] because it's not const
        char* message = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);

        // TODO: Consolidate this print because it's assuming we only pass vertex OR fragment shaders
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader." << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}


int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Setting OpenGL version to 3.3 and set the OpenGL profile to CORE
    // This is to set manually the Vertex Array Object (VAO)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Limit the framerate - to have a smooth reasonable animation
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error in the glewInit()" << std::endl;

    // Printing the OpenGL version
    std::cout << "Using OpenGL version " << glGetString(GL_VERSION) << std::endl;

    // Creating a scope to delete the vb and ib automatically without creating any pointer to them
    {
        // Vertex positions
        float positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f,  0.5f,
        };

        // Vertex indices
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        // Create the vertex array object
        VertexArray va;

        // Create the vertex buffer
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        // Create and bind the index buffer
        IndexBuffer ib(indices, 6);

        // Creating shaders
        ShaderProgramSource shaderSource = ParseShader("res/shaders/Basic.shader");
        unsigned int shader = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
        glUseProgram(shader);

        // Pass a uniform to the shader
        int uLocation = glGetUniformLocation(shader, "u_color");
        ASSERT(uLocation != -1);
        glUniform4f(uLocation, 0.8f, 0.3f, 0.8f, 1.0f);

        // Clearing GL states (i.e. unbinding everything)
        // TODO: Is this really necessary?
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        float r = 0.0f;
        float increment = 0.05f;

        // Loop until the user closes the window
        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT);

            // Bind all every frame
            //     1 - shader
            //     2 - vertex array object (that contains vertex buffer and vertex layout)
            //     3 - index buffer
            glUseProgram(shader);
            glUniform4f(uLocation, r, 0.3f, 0.8f, 1.0f);

            va.Bind();
            ib.Bind();

            // Draw call - passing nullptr because we are already selecting the index buffer
            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            // Swap front and back buffers
            glfwSwapBuffers(window);

            // Poll for and process events
            glfwPollEvents();
        }

        glDeleteProgram(shader);
    }

    glfwTerminate();
    return 0;
}