#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 orientation, Window* window)
	: m_FirstClick(true), m_Speed(0.1f), m_Sensitivity(100.0f),
	  m_Position(position), m_Orientation(glm::vec3(0.0f, 0.0f, -1.0f)),
	  m_Up(glm::vec3(0.0f, 1.0f, 0.0f)), m_View(glm::lookAt(m_Position, m_Position + m_Orientation, m_Up)),
	  m_Window(window)
{
	SetProjectionMatrix((float)window->GetWidth() / (float)window->GetHeight());
}

void Camera::SetProjectionMatrix(float aspectRatio)
{
	m_Projection = glm::perspective(glm::radians(s_FovDeg), aspectRatio, s_NearPlane, s_FarPlane);
}

void Camera::Inputs()
{
	GLFWwindow* window = m_Window->GetGLWindow();
	int width = m_Window->GetWidth();
	int height = m_Window->GetHeight();


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_Position += m_Speed * m_Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_Position += m_Speed * -glm::normalize(glm::cross(m_Orientation, m_Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_Position += m_Speed * -m_Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_Position += m_Speed * glm::normalize(glm::cross(m_Orientation, m_Up));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_Speed = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		m_Speed = 0.1f;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_Position += m_Speed * m_Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_Position += m_Speed * -m_Up;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		if (m_FirstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			m_FirstClick = false;
		}

		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		float rotX = m_Sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = m_Sensitivity * (float)(mouseX - (width / 2)) / width;

		glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-rotX),
		                                       glm::normalize(glm::cross(m_Orientation, m_Up)));

		if (!(glm::angle(newOrientation, m_Up) <= glm::radians(5.0f) or (glm::angle(newOrientation, -m_Up) <=
			glm::radians(5.0f))))
		{
			m_Orientation = newOrientation;
		}

		m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY), m_Up);

		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		m_FirstClick = true;
	}

	m_View = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
}
