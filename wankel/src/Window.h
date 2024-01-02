#pragma once

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <string>
class Camera;

class Window
{
public:
	Window(int width, int height, std::string title);
	~Window();

	bool Initialise();

	bool ShouldClose() const { return glfwWindowShouldClose(m_Window); }
	void SwapBuffers() const { glfwSwapBuffers(m_Window); }
	static void PollEvents() { glfwPollEvents(); }
	static void WindowSizeCallback(GLFWwindow* window, int width, int height);

	GLFWwindow* GetGLWindow() const { return m_Window; }
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

private:
	GLFWwindow* m_Window;
	std::string m_Title;

	int m_Width;
	int m_Height;
};
