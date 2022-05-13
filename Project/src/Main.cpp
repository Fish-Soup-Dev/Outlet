#include "Window.h"
#include "Gui.h"
#include "log.h"
#include "vec/vec.h"

int main()
{
	Log* log = new Log();
	log->SetLevel(Log::LevelInfo);

	Window* window = new Window(1280, 720, "Program Window", false, log);
	window->Init();

	Gui* gui = new Gui(window->m_Window, log);
	gui->Init();

	vec4 BackgroundColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	float progress = 0.69f;

	while (!glfwWindowShouldClose(window->m_Window))
	{
		window->Clear(BackgroundColor);
		gui->StartFrame();

		ImGui::SetNextWindowPos(ImVec2(10, 10));
		ImGui::SetNextWindowSize(ImVec2(500, 700));
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");

		ImGui::ColorEdit4("Background Color", (float*)&BackgroundColor);
		
		ImGui::SliderFloat("Progress Bar", &progress, 0.0f, 1.0f);

		gui->ProgressBar(progress, vec2(400, 20));

		if (gui->Button("test1", vec2(100, 20), colorRGB(0.0f, 0.5f, 0.0f)))
			log->Info("1");

		ImGui::End();

		gui->Render();
		window->Render();
	}
	log->Info("Program closed");
}