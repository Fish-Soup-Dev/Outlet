#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

class Renderer
{
public:
	int m_WindowWidth = 640, m_WindowHeight = 480;
	const char* m_WindowName = "Title";
	bool m_WindowResiable = true;
	GLFWwindow* m_Window;
public:
	Renderer(int W, int H, const char* name, bool Resizeable)
		: m_WindowWidth(W), m_WindowHeight(H), m_WindowName(name), m_Window(NULL), m_WindowResiable(Resizeable) { }

	~Renderer();

	void Init();
	void Clear(const glm::vec4 color) const;
	void Render();
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};