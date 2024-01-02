#pragma once

#include "Window.h"
#include "glm/glm.hpp"

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 orientation, Window* window);
	static void SetProjectionMatrix(float aspectRatio);
	void Inputs();

	glm::mat4 GetProjectionViewMatrix() const { return m_Projection * m_View; }

private:
	bool m_FirstClick;

	float m_Speed;
	float m_Sensitivity;

	glm::vec3 m_Position;
	glm::vec3 m_Orientation;
	glm::vec3 m_Up;
	static float s_AspectRatio;

	inline static float s_FovDeg = 45.0f;
	inline static float s_NearPlane = 0.1f;
	inline static float s_FarPlane = 1000.0f;

	inline static glm::mat4 m_Projection = glm::mat4();
	glm::mat4 m_View;

	Window* m_Window;
};
