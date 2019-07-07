#include "Sphere.h"


Sphere::Sphere()
{
    init(48);
}

Sphere::Sphere(int precision)
{
    init(precision);
}

void Sphere::init(int precision)
{
    m_NumVertices = (precision + 1) * (precision + 1);  // Because the uv need an extra vertex to close the wrap
    m_NumIndices = precision * precision * 6;

    // Fill the vectors
    for (int i = 0; i < m_NumVertices; i++)
    {
        m_Vertices.push_back(glm::vec3());
        m_TexCoords.push_back(glm::vec2());
        m_Normals.push_back(glm::vec3());
    }

    for (int i = 0; i < m_NumIndices; i++)
        m_Indices.push_back(0);

    // Calculating triangle vertices
    for (int i = 0; i <= precision; i++)
    {
        for (int j = 0; j <= precision; j++)
        {
            float y =  (float)cos(glm::radians(180.0f - i * 180.0f / precision));
            float x = -(float)cos(glm::radians(j * 360.0f / precision)) * (float)abs(cos(asin(y)));
            float z =  (float)sin(glm::radians(j * 360.0f / precision)) * (float)abs(cos(asin(y)));

            m_Vertices[i * (precision + 1) + j] = glm::vec3(x, y, z);
            m_TexCoords[i * (precision + 1) + j] = glm::vec2(((float)j / precision), ((float)i / precision));
            m_Normals[i * (precision + 1) + j] = glm::vec3(x, y, z);
        }
    }

    // Calculating triangle indices
    for (int i = 0; i < precision; i++)
    {
        for (int j = 0; j < precision; j++)
        {
            m_Indices[6 * (i * precision + j) + 0] = i * (precision + 1) + j;
            m_Indices[6 * (i * precision + j) + 1] = i * (precision + 1) + j + 1;
            m_Indices[6 * (i * precision + j) + 2] = (i + 1) * (precision + 1) + j;
            m_Indices[6 * (i * precision + j) + 3] = i * (precision + 1) + j + 1;
            m_Indices[6 * (i * precision + j) + 4] = (i + 1) * (precision + 1) + j + 1;
            m_Indices[6 * (i * precision + j) + 5] = (i + 1) * (precision + 1) + j;
        }
    }
}