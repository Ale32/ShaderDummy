#pragma once

#include <vector>
#include "Renderer.h"


struct VertexBufferElement
{
    unsigned int type;
    unsigned int count; // Must be 1,2,3 or 4 - it is the count of elements this attribute is made of
    unsigned char normalized; // Make sense for BYTE type, because the GPU needs a float

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        ASSERT(false);
        return 0;
    }
};


class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;  // The amount of bytes between each vertex
    unsigned int m_VertexAttributesCount;

public:
    VertexBufferLayout()
        : m_Stride(0), m_VertexAttributesCount(0)
    {
    }

    template<typename T>
    void Push(unsigned int count)
    {
        static_assert(false);
    }

    template<>
    void Push<float>(unsigned int count)
    {
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
        m_VertexAttributesCount += count;
    }

    template<>
    void Push<unsigned int>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
        m_VertexAttributesCount += count;
    }

    template<>
    void Push<unsigned char>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
        m_VertexAttributesCount += count;
    }

    inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
    inline unsigned int GetVertexAttributesCount() const { return m_VertexAttributesCount; }
};
