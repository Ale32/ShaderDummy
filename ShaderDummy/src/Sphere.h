#pragma once

#include <cmath>
#include <vector>

#include "glm/glm.hpp"


class Sphere
{
private:
    int m_NumVertices;
    int m_NumIndices;

    std::vector<int> m_Indices;
    std::vector<glm::vec3> m_Vertices;
    std::vector<glm::vec2> m_TexCoords;
    std::vector<glm::vec3> m_Normals;

    void init(int);

public:
    Sphere();
    Sphere(int precision);

    inline int GetNumVertices() const { return m_NumVertices; }
    inline int GetNumIndices() const { return m_NumIndices; }

    inline std::vector<int> GetIndices()         const { return m_Indices; }
    inline std::vector<glm::vec3> GetVertices()  const { return m_Vertices; }
    inline std::vector<glm::vec2> GetTexCoords() const { return m_TexCoords; }
    inline std::vector<glm::vec3> GetNormals()   const { return m_Normals; }
};
