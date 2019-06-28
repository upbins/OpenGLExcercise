#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <vector>

enum MyCamera_Movement {
	MOVEFORWARD,
	MOVEBACKWARD,
	MOVELEFT,
	MOVERIGHT
};
class MyCamera
{
private:
	void UpdateCameraVectors();
public:
	MyCamera(glm::vec3 position, glm::vec3 traget, glm::vec3 worldup);
	MyCamera(glm::vec3 position, float pitch,float yaw,glm::vec3 worldup);
	~MyCamera();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 Worldup;
	float MouseSensitivityX = 0.001f;
	float MouseSensitivityY = 0.001f;
	float Yaw;
	float Pitch;
	float SpeedZ = 0.0f;
	float SpeedX = 0.0f;
	float SpeedY = 0.0f;
	float MovementSpeed = 2.0f;
	float Zoom = 45.0f;
	glm::mat4 GetViewMatrix();
	void ProcessMouseMovement(float offsetX,float offsetY,GLboolean constrainPitch = true);
	void UpdateCameraPos();
	void ProcessKeyboard(MyCamera_Movement direction, float deltaTime);
	void ProcessMouseScroll(float yoffset);
};

