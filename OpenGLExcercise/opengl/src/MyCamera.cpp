#include "MyCamera.h"

MyCamera::MyCamera(glm::vec3 position, glm::vec3 traget, glm::vec3 worldup)
{
	Position = position;
	Worldup = worldup;
	Forward = glm::normalize(traget - position);
	Right = glm::normalize(glm::cross(Forward, Worldup));
	Up = glm::normalize(glm::cross(Forward, Right));
}

MyCamera::MyCamera(glm::vec3 position, float pitch,float yaw,glm::vec3 worldup){
	Position = position;
	Worldup = worldup;
	Pitch = pitch;
	Yaw = yaw;
	this->UpdateCameraVectors();
}
MyCamera::~MyCamera()
{

}

glm::mat4 MyCamera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, Worldup);
}

void MyCamera::UpdateCameraVectors()
{
	Forward.x = glm::cos(Pitch) * glm::sin(Yaw);
	Forward.y = glm::sin(Pitch);
	Forward.z = glm::cos(Pitch) * glm::cos(Yaw);
	Right = glm::normalize(glm::cross(Forward, Worldup));
	Up = glm::normalize(glm::cross(Right,Forward));
	// glm::vec3 front;
	// front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	// front.y = sin(glm::radians(Pitch));
	// front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	// Forward = glm::normalize(front);
	// // Also re-calculate the Right and Up vecto
	// Right = glm::normalize(glm::cross(Forward,Worldup));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	// Up    = glm::normalize(glm::cross(Right,Forward));
}

void MyCamera::ProcessMouseMovement(float offsetX,float offsetY,GLboolean constrainPitch)
{
	Pitch += offsetY * MouseSensitivityY;
	Yaw += offsetX * MouseSensitivityX;
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	UpdateCameraVectors();
}

void MyCamera::UpdateCameraPos()
{
	Position += (Forward * SpeedZ * 0.05f + Right * SpeedX * 0.05f + Up * SpeedY * 0.05f);
}

void MyCamera::ProcessKeyboard(MyCamera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == MOVEFORWARD)
		Position += Forward * velocity;
	if (direction == MOVEBACKWARD)
		Position -= Forward * velocity;
	if (direction == MOVELEFT)
		Position -= Right * velocity;
	if (direction == MOVERIGHT)
		Position += Right * velocity;
}


void MyCamera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}