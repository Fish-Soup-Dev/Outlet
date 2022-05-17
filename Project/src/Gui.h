#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "glm/glm.hpp"

class Gui
{
private:
	GLFWwindow* m_Window;
public:
	Gui(GLFWwindow* Window) : m_Window(Window) { }

	~Gui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Init()
	{
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
		ImGui::StyleColorsDark();
	}

	void StartFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void WindowBegin(const char* title, glm::vec2 WindowSize, glm::vec2 WindowPos)
	{
		ImGui::SetNextWindowPos(ImVec2(WindowPos.x, WindowPos.y));
		ImGui::SetNextWindowSize(ImVec2(WindowSize.x, WindowSize.y));
		ImGui::Begin(title, NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
	}

	void WindowBegin(const char* title, glm::vec2 WindowSize)
	{
		ImGui::SetNextWindowSize(ImVec2(WindowSize.x, WindowSize.y));
		ImGui::Begin(title, NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	}

	void WindowBegin(const char* title)
	{
		ImGui::Begin(title, NULL, ImGuiWindowFlags_NoCollapse);
	}

	void WindowEnd()
	{
		ImGui::End();
	}

	void Text(const char* text)
	{
		ImGui::Text(text);
	}

	bool Button(const char* lable, const glm::vec2 size, const glm::vec3 buttonColor)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(buttonColor.r, buttonColor.g, buttonColor.b)));
		if (ImGui::Button(lable, ImVec2(size.x, size.y)))
		{
			ImGui::PopStyleColor(1);
			return true;
		}
		ImGui::PopStyleColor(1);
		return false;
	}

	void ProgressBar(float progress, const glm::vec2 size)
	{
		ImGui::ProgressBar(progress, ImVec2(size.x, size.y));
	}
};