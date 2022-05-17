#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vec/vec.h"
#include <iostream>

class Window
{
public:
	int m_WindowWidth = 640, m_WindowHeight = 480;
	const char* m_WindowName = "Title";
	bool m_WindowResiable = true;
	GLFWwindow* m_Window;
public:
	Window(int W, int H, const char* name, bool Resizeable) 
		: m_WindowWidth(W), m_WindowHeight(H), m_WindowName(name), m_Window(NULL), m_WindowResiable(Resizeable) { }

	~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Init()
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
	}

	void Clear(colorRGBA color)
	{
		glClearColor(color.r(), color.g(), color.b(), color.a());
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Render()
	{
		glfwGetWindowSize(m_Window, &m_WindowWidth, &m_WindowHeight);
		glViewport(0, 0, m_WindowWidth, m_WindowHeight);
		
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
};