#include "Renderer.h"

#include <iostream>

Renderer::~Renderer()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Renderer::Init()
{
	if (!glfwInit())
	{
		std::cout << "[ERROR] Failed to init GLFW" << std::endl;
		exit(-1);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, m_WindowResiable);

	m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_WindowName, NULL, NULL);

	if (!m_Window)
	{
		glfwTerminate();
		std::cout << "[ERROR] Window is NULL" << std::endl;
		exit(-1);
	}

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		std::cout << "[ERROR] Failed to init GLEW" << std::endl;
		exit(-1);
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void Renderer::Clear(const glm::vec4 color) const
{
	glClearColor(color.r, color.g, color.b, color.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::Render()
{
	glfwGetWindowSize(m_Window, &m_WindowWidth, &m_WindowHeight);
	glViewport(0, 0, m_WindowWidth, m_WindowHeight);

	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}
