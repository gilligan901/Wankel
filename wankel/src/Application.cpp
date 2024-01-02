#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Primatives/ShapeMaker.h"
#include "Camera.h"
#include "Shader.h"
#include "Window.h"

GLuint numIndices;
GLuint programId;
float z = -3.0f;
double frameTime = 0;
double fps = 0;

void sendDataToOpenGL()
{
	ShapeData triangle = ShapeMaker::makeCube();

	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, triangle.vertexBufferSize(), triangle.vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(3 * sizeof(float)));

	GLuint indexBufferId;
	glGenBuffers(1, &indexBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangle.indexBufferSize(), triangle.indices, GL_STATIC_DRAW);
	numIndices = triangle.numIndices;
	triangle.cleanup();
}

void drawImGui()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// ImGui calls...
	ImGui::Begin("Hello, world!");
	ImGui::Text("Frame Time: %.4f ms", frameTime * 1000.0);
	ImGui::Text("FPS: %.2f", fps);
	ImGui::SliderFloat("z", &z, 0.0f, -10.0f);
	ImGui::End();

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main(void)
{
	Window window(800, 600, "Wankel");
	if (!window.Initialise())
	{
		return -1;
	}

	Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), &window);

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window.GetGLWindow(), true); // 'window' is your GLFWwindow*
	ImGui_ImplOpenGL3_Init("#version 430"); // 'glsl_version' is a char* to your GLSL version, e.g., "#version 150"

	glEnable(GL_DEPTH_TEST);
	sendDataToOpenGL();
	Shader shader("./res/shaders/Vertex.glsl", "./res/shaders/Fragment.glsl");
	shader.Bind();

	double lastFrameTime = glfwGetTime();
	/* Loop until the user closes the window */
	while (!window.ShouldClose())
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs();

		/*	glm::vec3 dominatingColour(1.0f, 0.0f, 0.0f);
			GLint dominatingColourUniformLocation = glGetUniformLocation(programId, "dominatingColour");
			glUniform3fv(dominatingColourUniformLocation, 1, &dominatingColour[0]);*/

		glm::mat4 worldToViewMatrix = camera.GetProjectionViewMatrix();
		glm::mat4 translateMatrix = glm::translate(worldToViewMatrix, glm::vec3(0.0f, 0.0f, z));
		glm::mat4 fullTransformMatrix = glm::rotate(translateMatrix, (float)glfwGetTime(), glm::vec3(5.0f, 1.0f, 1.0f));

		shader.SetUniformMat4f("fullTransformMatrix", fullTransformMatrix);

		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);

		worldToViewMatrix = camera.GetProjectionViewMatrix();
		translateMatrix = glm::translate(worldToViewMatrix, glm::vec3(5.0f, 0.0f, z));
		fullTransformMatrix = glm::rotate(translateMatrix, (float)glfwGetTime(), glm::vec3(1.0f, 8.0f, 2.0f));

		shader.SetUniformMat4f("fullTransformMatrix", fullTransformMatrix);

		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);


		double currentFrameTime = glfwGetTime();
		frameTime = currentFrameTime - lastFrameTime;
		lastFrameTime = currentFrameTime;
		fps = 1.0 / frameTime;

		drawImGui();

		/* Swap front and back buffers */
		window.SwapBuffers();

		/* Poll for and process events */
		window.PollEvents();
	}

	glfwTerminate();
	return 0;
}
