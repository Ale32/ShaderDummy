#pragma once

#include "VertexBuffer.h"


class VertexBufferLayout;


class VertexArray
{
private:
    unsigned int m_RendererID;
    unsigned int m_vertexCount;

public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetVertexCount() const { return m_vertexCount; }
};
