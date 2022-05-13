#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "log.h"
#include "vec/vec.h"

class Window
{
public:
	int m_WindowWidth = 640, m_WindowHeight = 480;
	const char* m_WindowName = "Title";
	bool m_WindowResiable = true;
	GLFWwindow* m_Window;
private:
	Log* logger;
public:
	Window(int W, int H, const char* name, bool Resizeable, Log* log) 
		: m_WindowWidth(W), m_WindowHeight(H), m_WindowName(name), m_Window(NULL), m_WindowResiable(Resizeable), logger(log) { }

	~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Init()
	{
		if (!glfwInit())
		{
			logger->Error("Failed to init GLFW");
			exit(-1);
		}

		logger->Info("GLFW initialized.");

		glfwWindowHint(GLFW_RESIZABLE, m_WindowResiable);

		m_Window = glfwCreateWindow(m_WindowWidth, m_WindowHeight, m_WindowName, NULL, NULL);

		if (!m_Window)
		{
			glfwTerminate();
			logger->Error("Window is NULL");
			exit(-1);
		}

		logger->Info("Window created.");

		glfwMakeContextCurrent(m_Window);
		glfwSwapInterval(1);

		if (glewInit() != GLEW_OK)
		{
			glfwTerminate();
			logger->Error("Failed to init GLEW");
			exit(-1);
		}

		logger->Info("GLEW initialized.");
	}

	void Clear(colorRGBA color)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(color.r(), color.g(), color.b(), color.a());
	}

	void Render()
	{
		glfwGetWindowSize(m_Window, &m_WindowWidth, &m_WindowHeight);
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	} 
};