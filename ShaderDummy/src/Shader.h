#pragma once

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"


class Shader
{
private:
    std::string m_VertexFilePath;
    std::string m_FragmentFilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    
    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    const std::string ParseShader(const std::string& filepath);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    int GetUniformLocation(const std::string& name);
};