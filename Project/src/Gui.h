#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class Gui
{
private:
	GLFWwindow* m_Window;
	Log* logger;
public:
	Gui(GLFWwindow* Window, Log* log) : m_Window(Window), logger(log) { }

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
		logger->Info("ImGui context created");
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

	bool Button(const char* lable, const vec2 size, const colorRGB buttonColor)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(buttonColor.r(), buttonColor.g(), buttonColor.b())));
		if (ImGui::Button(lable, ImVec2(size.x(), size.y())))
		{
			ImGui::PopStyleColor(1);
			return true;
		}
		ImGui::PopStyleColor(1);
		return false;
	}

	void ProgressBar(float progress, const vec2 size)
	{
		ImGui::ProgressBar(progress, ImVec2(size.x(), size.y()));
	}

};