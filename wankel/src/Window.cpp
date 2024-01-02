#include "Window.h"

#include <iostream>

#include "Camera.h"

Window::Window(int width, int height, std::string title)
	: m_Window(nullptr), m_Title(std::move(title)), m_Width(width), m_Height(height)
{
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

bool Window::Initialise()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << '\n';
		return false;
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), nullptr, nullptr);
	if (!m_Window)
	{
		std::cerr << "Failed to create GLFW window" << '\n';
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_Window);

	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialise GLEW" << '\n';
		return NULL;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);

	return true;
}

void Window::WindowSizeCallback(GLFWwindow* window, const int width, const int height)
{
	Camera::SetProjectionMatrix(static_cast<float>(width) / static_cast<float>(height));

	glViewport(0, 0, width, height);
}
