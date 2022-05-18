#pragma once

#include "VertexBuffer.h"
#include <cstdint>

class VertexBufferLayout;

class VertexArray
{
private:
	uint32_t m_RendererID;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
};