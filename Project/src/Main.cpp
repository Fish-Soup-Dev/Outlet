#include "engine/Renderer.h"
#include "Gui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct Vertex
{
	std::vector <glm::vec3> positions;
	std::vector <glm::vec3> normals;
};

int main()
{
	// Init Window and gui
	Renderer* renderer = new Renderer(800, 600, "Program Window", true);
	renderer->Init();
	Gui* gui = new Gui(renderer->m_Window);
	gui->Init();

	// Load obj into to groups of vec3s


	// Opengl STUFF



	// Opengl STUFF

	// camera and model transform
	glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)renderer->m_WindowWidth / (float)renderer->m_WindowHeight, 0.1f, 100.0f);
	glm::mat4 veiw = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -5.0f));
	glm::mat4 model = glm::rotate(glm::mat4(1.0f), 0.4f, glm::vec3(1, 0, 0));
	glm::mat4 mvp = proj * veiw * model;

	// bind shader and set MVP
	Shader shader("res/shaders/BasicVertex.glsl", "res/shaders/BasicFragment.glsl");
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	
	// animate and controls
	float roateAngle = 0.0f;
	bool wireframe = false;
	bool wave = false;

	// unbind things
	shader.UnBind();

	// Main render loop
	while (!glfwWindowShouldClose(renderer->m_Window))
	{
		// Clear Screen
		renderer->Clear(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		// Enable or Disabe wireframe veiw
		if (wireframe == true)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		
		// Bind shader and set MVP
		shader.Bind();
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), 0.4f, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), roateAngle, glm::vec3(0, 1, 0));
		glm::mat4 mvp = proj * veiw * model;
		shader.SetUniformMat4f("u_MVP", mvp);

		// RENDER OBJECT HERE



		// RENDER OBJECT HERE

		roateAngle += 0.001f;
		
		// Show FPS
		gui->StartFrame();

		gui->WindowBegin("Info", glm::vec2(250, 130));
		gui->ShowFps();
		ImGui::Checkbox("Wireframe enable", &wireframe);
		gui->WindowEnd();

		gui->Render();
		
		renderer->Render();
	}

	delete renderer;
}